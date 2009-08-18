/*            G E D C O M M A N D . C X X
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

/** @file GedCommand.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of GedCommand class.
 */

#include <brlcad/ged.h>

#include "GedCommand.h"

#include "Logger.h"


/*******************************************************************************
 * GedCommand
 ******************************************************************************/
GedCommand::GedCommand(const GedFunc func,
		       const QString& name,
		       const QString& shortDescr,
		       const QString& extraDescr) :
  Command(name, shortDescr, extraDescr), _gedFunc(func)
{
}


QString GedCommand::execute(const QStringList& args) 
{
  const char **argv = new const char*[args.size()];
  for(int i = 0; i < args.size(); ++i) {
    argv[i] = args[i].toLocal8Bit().data();
  }
  
  _gedFunc(GedData::instance().getGED(), args.size(), argv);

  delete argv;
  return QString(bu_vls_addr(&(GedData::instance().getGED())->ged_result_str));
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
