/*            C O M M A N D I N T E R P R E T E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/** @file CommandInterpreter.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of Command Interpreter functionality for
 *	Console-like windows.
 */

#include "CommandInterpreter.h"

#include "Logger.h"
#include "Commands.h"

#include <vector>


/*******************************************************************************
 * CommandOutput
 ******************************************************************************/
void CommandOutput::appendLine(const std::string& line)
{
  if (!_output.empty())
    _output.append("\n");
  _output.append(line);
}

const std::string& CommandOutput::getOutput() const
{
  return _output;
}


/*******************************************************************************
 * Command
 ******************************************************************************/
Command::Command(const std::string& name, const std::string& shortDescr, const std::string& extraDescr) :
  _name(name), _shortDescription(shortDescr), _extraDescription(extraDescr)
{
}

const std::string& Command::getName() const
{
  return _name;
}

const std::string& Command::getShortDescription() const
{
  return _shortDescription;
}

const std::string& Command::getExtraDescription() const
{
  return _extraDescription;
}

const std::vector<std::string>& Command::getArgNames() const
{
  return _argNames;
}

std::string Command::getSyntax() const
{
  std::string line = _name;
  for (size_t i = 0; i < _argNames.size(); ++i) {
    line += " <" + _argNames[i] + ">";
  }
  return line;
}


/*******************************************************************************
 * CommandInterpreter
 ******************************************************************************/
CommandInterpreter* CommandInterpreter::INSTANCE = 0;

CommandInterpreter& CommandInterpreter::instance()
{
  if (!INSTANCE)
    INSTANCE = new CommandInterpreter();
  return *INSTANCE;
}

CommandInterpreter::CommandInterpreter()
{
  addCommand(new CommandQuit());
  addCommand(new CommandSetLogLevel());
  addCommand(new CommandSetPolygonMode());
  addCommand(new CommandSetCameraProjectionType());
  addCommand(new CommandCycleCameraMode());
  addCommand(new CommandCreateSampleGeometry());
}

/*
void CommandInterpreter::finalize()
{
  while (!_commands.empty()) {
    delete (*(_commands.begin())).second;
    _commands.erase(_commands.begin());
  }
}
*/

std::string CommandInterpreter::getAutocompleteString(const std::string& input)
{
  // collect candidates
  std::vector<std::string> candidates;
  for (std::map<std::string, Command*>::iterator it = _commands.begin();
       it != _commands.end();
       ++it) {
    const std::string& commandName = it->first;
    // push back all commands which match the input
    int comparison = commandName.compare(0, input.length(), input);
    if (comparison == 0) {
      // Logger::logDEBUG(" - matches '%s'", input.c_str());
      candidates.push_back(commandName);
    } else {
      // Logger::logDEBUG(" - doesn't match, comparison result '%d'", comparison);
    }
  }

  std::string r;
  if (candidates.size() == 0) {
    //Logger::logDEBUG("Autocompletion: no candidates");
    r = input;
  } else if (candidates.size() == 1) {
    //Logger::logDEBUG("Autocompletion: only one candidate: '%s'", r.c_str());
    r = candidates[0];
  } else {
    //Logger::logDEBUG("Autocompletion: several candidates for '%s'", input.c_str());
    r = input;

    // add letters while they match in all candidates in same position
    while (true) {
      // check that matches in all candidates
      size_t pos = r.length();
      char charMatch = candidates[0][pos];
      bool allOfThemMatch = true;
      for (std::vector<std::string>::iterator it = candidates.begin();
	   it != candidates.end();
	   ++it) {
	const std::string& commandName = (*it);
	//Logger::logDEBUG(" - '%s' at %u", commandName.c_str(), pos);
	if (commandName[pos] != charMatch) {
	  /* Logger::logDEBUG("    - char '%c' of '%s'[%u] doesn't match with previous candidates",
	     commandName[pos], commandName.c_str(), pos); */
	  allOfThemMatch = false;
	  break;
	}
      }

      // add character if matches, finish if not
      if (allOfThemMatch) {
	//Logger::logDEBUG(" - adding '%c'", charMatch);
	r.append(1, charMatch);
	++pos;
      } else {
	//Logger::logDEBUG(" - not all of them match, stopping");
	break;
      }
    }
  }

  //Logger::logDEBUG(" - returning completion '%s'", r.c_str());
  return r;
}

void CommandInterpreter::execute(const std::string& commandLine, CommandOutput& output)
{
  // try to parse the command line into arguments
  std::vector<std::string> args;
  parseCommandLine(commandLine, args);
  if (args.size() == 0) {
    output.appendLine("Error: Cannot parse command line (too long?)");
    return;
  }

  // extract the command name
  std::string commandName = args[0];
  args.erase(args.begin());

  if (commandName == "help") {
    // help meta command
    if (args.size() == 0) {
      // general help
      showHelp(output);
    } else {
      // specific command help
      showHelp(args[0], output);
    }
  } else {
    // search for a "real" command
    Command* command = findCommand(commandName);
    if (!command) {
      output.appendLine("No such command '" + commandName + "', type 'help' for a list.");
    } else {
      // execute the command
      command->execute(args, output);
    }
  }
}

void CommandInterpreter::addCommand(Command* command)
{
  const std::string& commandName = command->getName();
  if (findCommand(commandName)) {
    Logger::logWARNING("CommandInterpreter: '%s' command already exists",
		       commandName.c_str());
  } else {
    _commands[commandName] = command;
  }
}

void CommandInterpreter::showHelp(CommandOutput& output)
{
  // header
  output.appendLine("Available commands:");

  // list of commands with short description
  for (std::map<std::string, Command*>::iterator it = _commands.begin();
       it != _commands.end(); ++it) {
    // alias
    Command* command = (*it).second;
    // add syntax to output (name and arguments)
    std::string line = "  " + command->getSyntax();
    // "tab" to column 40 in a line
    while (line.length() < 40) {
      line += " ";
    }
    // add short description
    line += command->getShortDescription();
    output.appendLine(line);
  }

  // footer
  output.appendLine(std::string("Use 'help <command>' for specific info."));
}

void CommandInterpreter::showHelp(const std::string& commandName, CommandOutput& output)
{
  // get the command
  Command* command = findCommand(commandName);
  if (!command) {
    output.appendLine("No such command '" + commandName + "', type 'help' for a list.");
    return;
  }

  // add syntax to output (name and arguments)
  std::string line = "  " + command->getShortDescription();
  line += "\n  Syntax: " + command->getSyntax();
  line += "\n  Extra description: " + command->getExtraDescription();
  output.appendLine(line);
}

Command* CommandInterpreter::findCommand(const std::string& commandName) const
{
  std::map<std::string, Command*>::const_iterator it = _commands.find(commandName);
  if (it == _commands.end()) {
    return 0;
  } else {
    return (*it).second;
  }
}

void CommandInterpreter::parseCommandLine(const std::string& cL, std::vector<std::string>& args)
{
  std::string commandLine(cL);
  // trim tail
  {
    std::string::size_type pos = commandLine.find_last_not_of(' ');
    if (pos != std::string::npos) {
      // Logger::logDEBUG("trimming tail of: '%s'", commandLine.c_str());
      commandLine = commandLine.substr(0, pos+1);
      // Logger::logDEBUG("  - result: '%s'", commandLine.c_str());
    }
  }

  // tokenize the string into arguments
  while (commandLine.length() > 0) {
    // trim front
    if (commandLine[0] == ' ') {
      std::string::size_type pos = commandLine.find_first_not_of(' ');
      if (pos != std::string::npos) {
	// Logger::logDEBUG("trimming front of: '%s'", commandLine.c_str());
	commandLine = commandLine.substr(pos);
	// Logger::logDEBUG("  - result: '%s'", commandLine.c_str());
      }
    }
    // Logger::logDEBUG("commandLine: '%s'", commandLine.c_str());

    std::string::size_type pos = commandLine.find_first_of(' ');
    if (pos != std::string::npos) {
      const std::string& newArg = commandLine.substr(0, pos);
      args.push_back(newArg);
      commandLine = commandLine.substr(pos+1, commandLine.length()-pos);
      // Logger::logDEBUG(" -arg recognized: '%s'", newArg.c_str());
      // Logger::logDEBUG(" -rest : '%s'", commandLine.c_str());
    } else {
      // no spaces left, last argument
      args.push_back(commandLine);
      // Logger::logDEBUG(" -LAST arg recognized: '%s'", commandLine.c_str());
      commandLine.clear();
    }
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
