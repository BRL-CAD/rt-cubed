/*            C O M M A N D . C X X
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

/** @file Command.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of Command base class.
 */

#include <vector>

#include "Command.h"


/*******************************************************************************
 * CommandMessages
 ******************************************************************************/
const char* CommandMessages::NO_ARGUMENTS = "Command doesn't accept arguments";
const char* CommandMessages::ZERO_OR_ONE_ARGUMENTS = "This command needs exactly zero or one argument";
const char* CommandMessages::ONE_ARGUMENT = "This command needs exactly one argument";


/*******************************************************************************
 * Command
 ******************************************************************************/
Command::Command(const QString& name,
		 const QString& shortDescr,
		 const QString& extraDescr) :
  _name(name), _shortDescription(shortDescr), _extraDescription(extraDescr)
{
}

const QString& Command::getName() const
{
  return _name;
}

const QString& Command::getShortDescription() const
{
  return _shortDescription;
}

const QString& Command::getExtraDescription() const
{
  return _extraDescription;
}

const std::vector<QString>& Command::getArgumentNames() const
{
  return _argNames;
}

QString Command::getSyntax() const
{
  QString line = _name;
  for (size_t i = 0; i < _argNames.size(); ++i) {
    line += " <" + _argNames[i] + ">";
  }
  return line;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
