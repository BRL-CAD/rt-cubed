/*            G E D C O M M A N D . C X X
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

/** @file GedCommand.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of GedCommand class.
 */

#include <brlcad/ged.h>
/** \note mafm: Undefining too-common names to not clash with names
 * elsewhere (in example, Ogre uses some of them) */
#undef X
#undef Y

#include "GedCommand.h"

#include "Logger.h"


/*******************************************************************************
 * GedCommand
 ******************************************************************************/
GedCommand::GedCommand(const std::string& name,
		       const std::string& shortDescr,
		       const std::string& extraDescr) :
  Command(name, shortDescr, extraDescr)
{
}

void GedCommand::treatGEDResult(int resultCode,
				CommandOutput& output,
				const std::string& text) const
{
  if (resultCode == BRLCAD_OK) {
    output.appendLine(text);
  } else {
    Logger::logERROR(text.c_str());
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
