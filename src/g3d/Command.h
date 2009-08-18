/*            C O M M A N D . H
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

/** @file Command.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Command base class.
 */

#ifndef __G3D_COMMAND_H__
#define __G3D_COMMAND_H__


#include <QStringList>


/**
 * @brief Messages related with command processing
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Class (could be another "block" like namespace or so, too) acting
 * only as a container for strings repeated throughout the code when
 * processing commands, like in example error messages related with
 * number of arguments needed.  It's more efficient this way than
 * repeating the string over and over, and more maintainable if the
 * strings start to have slightly different variations (typos fixed in
 * some but not in others, etc).
 */
class CommandMessages
{
public:
  /** Message (name+content should be self-explanatory) */
  static const char* NO_ARGUMENTS;
  /** Message (name+content should be self-explanatory) */
  static const char* ZERO_OR_ONE_ARGUMENTS;
  /** Message (name+content should be self-explanatory) */
  static const char* ONE_ARGUMENT;
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
  Command(const QString& name,
	  const QString& shortDescr,
	  const QString& extraDescr);
  /** Default destructor */
  virtual ~Command() { }

  /** Execute the command (to be implemented by the real commands) */
  virtual QString execute(const QStringList& args) = 0;

  /** The name of the command */
  const QString& getName() const;
  /** Get a one-line description of the command */
  const QString& getShortDescription() const;
  /** Get a extra description of the command */
  const QString& getExtraDescription() const;
  /** Get the name of the arguments */
  const QStringList getArgumentNames() const;
  /** Get the syntax */
  QString getSyntax() const;

protected:
  /** The name of the command */
  QString _name;
  /** Description, one line only if possible */
  QString _shortDescription;
  /** Extra description */
  QString _extraDescription;
  /** The names of the arguments */
  QStringList _argNames;
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
