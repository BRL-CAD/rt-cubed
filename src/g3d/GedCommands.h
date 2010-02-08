/*                  G E D C O M M A N D S . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2010 United States Government as represented by
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

/** @file GedCommands.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of commands dealing with libged.
 */

#ifndef __G3D_GEDCOMMANDS_H__
#define __G3D_GEDCOMMANDS_H__


#include "GedCommand.h"

#include <QString>

#include "GedData.h"


/** @brief Dump a full copy of the database
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandGedDump : public GedCommand
{
public:
  CommandGedDump() :
    GedCommand(&ged_dump,
	       "dump",
	       "Dump a full copy of the database",
	       "Argument is filename ('.g' not added automatically)")
    {
      _argNames.push_back("filename");
    }
};


/** @brief Open a database for editing
 */
class CommandGedOpenDB : public GedCommand
{
public:
  CommandGedOpenDB() :
    GedCommand(&ged_reopen,
	       "opendb",
	       "Open a database for editing.",
	       "Takes the filename to open")
    {
      _argNames.push_back("filename");
    }
};


/** @brief Solids on ray
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandGedSolidsOnRay : public GedCommand
{
public:
  CommandGedSolidsOnRay() :
    GedCommand(&ged_solids_on_ray,
	       "solids_on_ray",
	       "Solids on ray",
	       "")
    {
    }
};


/** @brief Get libged database file summary.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandGedSummary : public GedCommand
{
public:
  CommandGedSummary() :
    GedCommand(&ged_summary,
	       "summary",
	       "Get libged database file summary",
	       "Argument is either empty, or one of [primitives|regions|groups] (initial chars are enough)")
    {
      _argNames.push_back("type");
    }
};


/** @brief Get/Set libged DB title.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandGedTitle : public GedCommand
{
public:
  CommandGedTitle() :
    GedCommand(&ged_title,
	       "title",
	       "Get/Set libged database title",
	       "Argument is title (empty to get)")
    {
      _argNames.push_back("title");
    }
};


/** @brief Get libged database file version.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandGedVersion : public GedCommand
{
public:
  CommandGedVersion() :
    GedCommand(&ged_version,
	       "version",
	       "Get libged database file version",
	       "")
    {
    }
};


/** @brief Erase all currently displayed geometry
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CommandGedZap : public GedCommand
{
public:
  CommandGedZap() :
    GedCommand(&ged_zap,
	       "zap",
	       "Erase all currently displayed geometry",
	       "")
    {
    }
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

