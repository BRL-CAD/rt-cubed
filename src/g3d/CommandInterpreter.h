/*            C O M M A N D I N T E R P R E T E R . H
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

/** @file CommandInterpreter.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Command Interpreter functionality for Console-like windows.
 */

#ifndef __G3D_COMMANDINTERPRETER_H__
#define __G3D_COMMANDINTERPRETER_H__

#include <vector>
#include <map>

#include <QObject>
#include <QString>

#include "../../include/Utility/Singleton.h"


class Command;
class CommandOutput;


/**
 * @brief Command Interpreter class
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * A command interpreter, meant to be link console-like windows inputs
 * with the outputs.
 *
 * The procedure is quite simple, for each command that we want to
 * support we have to create an instance and add it to the manager,
 * the base class takes care of the rest (including the deletion of
 * the instances in the destructor).  The data for each command is
 * especified in the constructor, and the argument names are a
 * convenience way to show some understandable info in the help (such
 * as "pm target ...", indicating that you have to especify the target
 * player and then whatever you want to tell her/him).
 */
class CommandInterpreter : public QObject
{
  Q_OBJECT
  
public:
  /** Default constructor */
  CommandInterpreter();
  /** Destructor */
  ~CommandInterpreter();
  
  /** Get Autocomplete string
   *
   * @param input The input to use as base for completion (the content
   * of the typed command so far)
   *
   * \returns String with text to be used instead, advancing so much
   * in the autocompletion as possible
   */
  QString getAutocompleteString(const QString& input);

public slots:
  /** Execute the given command line, and add the result to the given
   * output. */
  void execute(QString commandLine);

signals:
  void commandDone(QString output);

private:
  /** The set of commands registered */
  std::map<QString, Command*> _commands;

  /** Add a command (accesed by the registerCommands method) */
  void addCommand(Command* command);

  /** Show global help */
  QString help();
  /** Show help about the given command */
  QString help(const QString &command);

  /** Find a command by name
   *
   * \returns 0 if not found */
  Command* findCommand(const QString& commandName) const;
  /** Parse command line, putting each piece into the list of
   * arguments */
  QStringList parseCommandLine(const QString& cL);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
