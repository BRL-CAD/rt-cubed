/*            C O M M A N D I N T E R P R E T E R . H
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

/** @file CommandInterpreter.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Command Interpreter functionality for Console-like windows.
 */

#ifndef __G3D_COMMANDINTERPRETER_H__
#define __G3D_COMMANDINTERPRETER_H__


#include <string>
#include <vector>
#include <map>


/**
 * @brief Output for a command
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandOutput
{
public:
  /** Append given string to the output of a command */
  void appendLine(const std::string& line);
  /** Get the output of a command */
  const std::string& getOutput() const;

private:
  /** The complete output */
  std::string _output;
};


/**
 * @brief Command abstract class
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * A base class of a command, derived classes need to define the
 * execute() method, and also create a constructor to call the
 * constructor of the base class with the appropriate parameters
 * (constructors themselves cannot be virtual).
 */
class Command
{
public:
  /** Constructor with some basics needed when creating any
   * command. */
  Command(const std::string& name, const std::string& descr);
  /** Default destructor */
  virtual ~Command() { }

  /** The name of the command */
  const std::string& getName() const;
  /** Get a one-line description of the command */
  const std::string& getDescription() const;
  /** Get the name of the arguments */
  void getArgNames(std::vector<std::string>& argNames) const;
  /** Get the name of the arguments */
  const std::vector<std::string>& getArgNames() const;
  /** Execute the command */
  virtual void execute(std::vector<std::string>& args, CommandOutput& output) = 0;

protected:
  /** The name of the command */
  std::string _name;
  /** Description, one line only if possible */
  std::string _description;
  /** The names of the arguments */
  std::vector<std::string> _argNames;
};


/**
 * @brief Command Interpreter class
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * A command interpreter, meant to be link console-like windows inputs
 * with the outputs.
 */
class CommandInterpreter
{
public:
  /** Singleton, access to the manager */
  static CommandInterpreter& instance();

  /** Execute the given command line, and add the result to the given
   * output. */
  void execute(const std::string& commandLine, CommandOutput& output);

private:
  /** Singleton instance */
  static CommandInterpreter* INSTANCE;

  /** The set of commands registered */
  std::map<std::string, Command*> _commands;


  /** Default constructor */
  CommandInterpreter();

  /** Add a command (accesed by the registerCommands method) */
  void addCommand(Command* command);

  /** Show global help */
  void showHelp(CommandOutput& output);
  /** Show help about the given command */
  void showHelp(const std::string& commandName, CommandOutput& output);

  /** Find a command by name
   *
   * \returns 0 if not found */
  Command* findCommand(const std::string& commandName) const;
  /** Parse command line, putting each piece into the list of
   * arguments */
  void parseCommandLine(const std::string& cL, std::vector<std::string>& args);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
