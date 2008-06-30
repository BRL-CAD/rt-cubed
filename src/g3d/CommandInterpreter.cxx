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

#include "Logger.h"

#include "CommandInterpreter.h"


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
Command::Command(const std::string& name, const std::string& descr) :
  _name(name), _description(descr)
{
}

const std::string& Command::getName() const
{
  return _name;
}

const std::string& Command::getDescription() const
{
  return _description;
}

void Command::getArgNames(std::vector<std::string>& argNames) const
{
  argNames = _argNames;
}

const std::vector<std::string>& Command::getArgNames() const
{
  return _argNames;
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
    // /help meta command
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
      output.appendLine("No such command '" + commandName + "', type '/help' for a list.");
    } else {
      // execute the command
      command->execute(args, output);
    }
  }
}

void CommandInterpreter::showHelp(CommandOutput& output)
{
  // header
  output.appendLine("Available commands:");
  // short description of the existing commands (for the given
  // level) in the middle
  for (std::map<std::string, Command*>::iterator it = _commands.begin();
       it != _commands.end(); ++it) {
    showHelp((*it).first, output);
  }
  // footer
  output.appendLine(std::string("Use /help <command> for specific info."));
}

void CommandInterpreter::showHelp(const std::string& commandName, CommandOutput& output)
{
  // get the command
  Command* command = findCommand(commandName);
  if (!command) {
    output.appendLine("No help on '" + commandName + "'. Type '/help' for a list.");
    return;
  }

  // add to output name and arguments
  std::string line = "  " + command->getName();
  const std::vector<std::string>& argNames = command->getArgNames();
  for (size_t i = 0; i < argNames.size(); ++i) {
    line += " <" + argNames[i] + ">";
  }

  // "tab" to column 40 in a line
  while (line.size() < 40) {
    line += " ";
  }

  // add short description
  line += command->getDescription();
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
