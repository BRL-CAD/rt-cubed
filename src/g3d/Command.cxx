/*            C O M M A N D . C X X
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
Command::Command(const std::string& name,
		 const std::string& shortDescr,
		 const std::string& extraDescr) :
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

const std::vector<std::string>& Command::getArgumentNames() const
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


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
