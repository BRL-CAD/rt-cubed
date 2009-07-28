/*                  G E D C O M M A N D S . H
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
    GedCommand("ged_dump",
	       "Dump a full copy of the database",
	       "Argument is filename ('.g' not added automatically)")
    {
      _argNames.push_back("filename");
    }

  virtual QString execute(std::vector<QString>& args) {
    ged* g = GedData::instance().getGED();
    int result = 0;

    if (args.size() != 1) {
      return CommandMessages::ONE_ARGUMENT;
    } else {
      const char* argv[] = { _name.toStdString().c_str(), args[1].toStdString().c_str() };
      int argc = sizeof(argv)/sizeof(const char*);
      result = ged_dump(g, argc, argv);

      return treatGEDResult(result, bu_vls_addr(&g->ged_result_str));
    }
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
    GedCommand("ged_solids_on_ray",
	       "Solids on ray",
	       "")
    {
    }

  virtual QString execute(std::vector<QString>& args) {
    ged* g = GedData::instance().getGED();
    int result = 0;

    if (args.size() != 0) {
      return CommandMessages::NO_ARGUMENTS;
    } else {
      const char* argv[] = { _name.toStdString().c_str() };
      int argc = sizeof(argv)/sizeof(const char*);
      result = ged_solids_on_ray(g, argc, argv);

      return treatGEDResult(result, bu_vls_addr(&g->ged_result_str));
    }
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
    GedCommand("ged_summary",
	       "Get libged database file summary",
	       "Argument is either empty, or one of [primitives|regions|groups] (initial chars are enough)")
    {
      _argNames.push_back("type");
    }

  virtual QString execute(std::vector<QString>& args) {
    ged* g = GedData::instance().getGED();
    int result = 0;

    if (args.size() > 1) {
      return CommandMessages::ZERO_OR_ONE_ARGUMENTS;
    } else {
      if (args.size() == 1) {
	QString type;
	if (args[0][0] == 'p') {
	  type = "p";
	} else if (args[0][0] == 'r') {
	  type = "r";
	} else if (args[0][0] == 'g') {
	  type = "g";
	} else {
	  return "Summary type not recognized";
	}

	const char* argv[] = { _name.toStdString().c_str(), type.toStdString().c_str() };
	int argc = sizeof(argv)/sizeof(const char*);
	result = ged_summary(g, argc, argv);
      } else {
	const char* argv[] = { _name.toStdString().c_str() };
	int argc = sizeof(argv)/sizeof(const char*);
	result = ged_summary(g, argc, argv);
      }

      return treatGEDResult(result, bu_vls_addr(&g->ged_result_str));
    }
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
    GedCommand("ged_title",
	       "Get/Set libged database title",
	       "Argument is title (empty to get)")
    {
      _argNames.push_back("title");
    }

  virtual QString execute(std::vector<QString>& args) {
    ged* g = GedData::instance().getGED();
    int result = 0;

    if (args.size() > 1) {
      return CommandMessages::ZERO_OR_ONE_ARGUMENTS;
    } else {
      if (args.size() == 1) {
	const char* argv[] = { _name.toStdString().c_str(), args[1].toStdString().c_str() };
	int argc = sizeof(argv)/sizeof(const char*);
	result = ged_title(g, argc, argv);
      } else {
	const char* argv[] = { _name.toStdString().c_str() };
	int argc = sizeof(argv)/sizeof(const char*);
	result = ged_title(g, argc, argv);
      }

      return treatGEDResult(result, bu_vls_addr(&g->ged_result_str));
    }
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
    GedCommand("ged_version",
	       "Get libged database file version",
	       "")
    {
    }

  virtual QString execute(std::vector<QString>& args) {
    if (args.size() != 0) {
      return CommandMessages::NO_ARGUMENTS;
    } else {
      ged* g = GedData::instance().getGED();
      const char* argv[] = { _name.toStdString().c_str() };
      int argc = sizeof(argv)/sizeof(const char*);
      int result = ged_version(g, argc, argv);

      return treatGEDResult(result, bu_vls_addr(&g->ged_result_str));
    }
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
    GedCommand("ged_zap",
	       "Erase all currently displayed geometry",
	       "")
    {
    }

  virtual QString execute(std::vector<QString>& args) {
    ged* g = GedData::instance().getGED();
    int result = 0;

    if (args.size() != 0) {
      return CommandMessages::NO_ARGUMENTS;
    } else {
      return treatGEDResult(result, bu_vls_addr(&g->ged_result_str));
    }
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

