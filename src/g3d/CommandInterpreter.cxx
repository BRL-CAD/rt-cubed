/*            C O M M A N D I N T E R P R E T E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by
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

#include <vector>
#include <string>

#include "CommandInterpreter.h"

#include "Logger.h"
#include "Command.h"
#include "Commands.h"
#include "GedCommand.h"
#include "GedCommands.h"


/*******************************************************************************
 * CommandInterpreter
 ******************************************************************************/
template <> CommandInterpreter* Singleton<CommandInterpreter>::_instance = 0;

CommandInterpreter::CommandInterpreter()
{
//  addCommand(new CommandQuit());
  addCommand(new CommandSetLogLevel());
//  addCommand(new CommandSetPolygonMode());
//  addCommand(new CommandSetCameraProjectionType());
//  addCommand(new CommandCycleCameraMode());
  addCommand(new CommandGedDump());
  addCommand(new CommandGedSolidsOnRay());
  addCommand(new CommandGedSummary());
  addCommand(new CommandGedTitle());
  addCommand(new CommandGedVersion());
  addCommand(new CommandGedZap());
}

CommandInterpreter::~CommandInterpreter()
{
  while (!_commands.empty()) {
    delete (*(_commands.begin())).second;
    _commands.erase(_commands.begin());
  }
}

QString CommandInterpreter::getAutocompleteString(const QString& input)
{
  // collect candidates
  std::vector<QString> candidates;
  for (std::map<QString, Command*>::iterator it = _commands.begin();
       it != _commands.end();
       ++it) {
    const QString& commandName = it->first;
    // push back all commands which match the input
    int comparison = commandName.toStdString().compare(0, input.length(), input.toStdString());
    if (comparison == 0) {
      // Logger::logDEBUG(" - matches '%s'", input.c_str());
      candidates.push_back(commandName);
    } else {
      // Logger::logDEBUG(" - doesn't match, comparison result '%d'", comparison);
    }
  }

  QString r;
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
      QCharRef charMatch = candidates[0][pos];
      bool allOfThemMatch = true;
      for (std::vector<QString>::iterator it = candidates.begin();
	   it != candidates.end();
	   ++it) {
	const QString& commandName = (*it);
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
	r.append(charMatch);
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

void CommandInterpreter::execute(QString commandLine)
{
  // try to parse the command line into arguments
  std::vector<QString> args;
  parseCommandLine(commandLine, args);
  QString output;
  if (args.size() == 0) {
    output.append("Error: Cannot parse command line (too long?)");
    return;
  }

  // extract the command name
  QString commandName = args[0];
  args.erase(args.begin());

  if (commandName == "help") {
    // help meta command
    if (args.size() == 0) {
      // general help
      emit commandDone(help());
    } else {
      // specific command help
      emit commandDone(help(commandName));
    }
  } else {
    // search for a "real" command
    Command* command = findCommand(commandName);
    if (!command) {
      output.append("No such command '" + commandName + "', type 'help' for a list.");
    } else {
      // execute the command
      emit commandDone(command->execute(args));
    }
  }
}

void CommandInterpreter::addCommand(Command* command)
{
  const QString& commandName = command->getName();
  if (findCommand(commandName)) {
    Logger::logWARNING("CommandInterpreter: '%s' command already exists",
		       commandName.toStdString().c_str());
  } else {
    _commands[commandName] = command;
  }
}

QString CommandInterpreter::help()
{
  QString output;
  // header
  output.append("Available commands:\n");

  // list of commands with short description
  for (std::map<QString, Command*>::iterator it = _commands.begin();
       it != _commands.end(); ++it) {
    // alias
    Command* command = (*it).second;
    // add syntax to output (name and arguments)
    QString line = "  " + command->getSyntax();
    // "tab" to column 40 in a line
    while (line.length() < 40) {
      line += " ";
    }
    // add short description
    line += command->getShortDescription();
    output.append(line).append("\n");
  }

  // footer
  output.append("Use 'help <command>' for specific info.");
  return output;
}

QString CommandInterpreter::help(const QString& commandName)
{
  QString output;
  // get the command
  Command* command = findCommand(commandName);
  if (!command) {
    output.append("No such command '" + commandName + "', type 'help' for a list.");
    return output;
  }

  // add syntax to output (name and arguments)
  output = "  " + command->getShortDescription();
  output += "\n  Syntax: " + command->getSyntax();
  output += "\n  Extra description: " + command->getExtraDescription();
  return output;
}

Command* CommandInterpreter::findCommand(const QString& commandName) const
{
  std::map<QString, Command*>::const_iterator it = _commands.find(commandName);
  if (it == _commands.end()) {
    return 0;
  } else {
    return (*it).second;
  }
}

// TODO: Rewrite to not use std::string
void CommandInterpreter::parseCommandLine(const QString& cL, std::vector<QString>& args)
{
  std::string commandLine(cL.toStdString());
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
      const QString& newArg = QString(commandLine.substr(0, pos).c_str());
      args.push_back(newArg);
      commandLine = commandLine.substr(pos+1, commandLine.length()-pos);
      // Logger::logDEBUG(" -arg recognized: '%s'", newArg.c_str());
      // Logger::logDEBUG(" -rest : '%s'", commandLine.c_str());
    } else {
      // no spaces left, last argument
      args.push_back(QString(commandLine.c_str()));
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
