/*            G E D C O M M A N D . H
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

/** @file GedCommand.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Command for invoking libged functions.
 */

#ifndef __G3D_GEDCOMMAND_H__
#define __G3D_GEDCOMMAND_H__


#include "Command.h"


/**
 * @brief Command for invoking libged functions
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Derived class for commands invoking libged functions, to contain
 * specific functionality and factor code out needed for all this kind
 * of commands.
 */

#include <QString>

#include "GedData.h"

typedef int (*GedFunc)(ged *, int, const char **);

class GedCommand : public Command
{
public:
  /** Constructor with some basics needed when creating any
   * command. */
  GedCommand(const QString& name,
	     const QString& shortDescr,
	     const QString& extraDescr);
  /** Default destructor */
  virtual ~GedCommand() { }

protected:
  static void callGed(GedFunc func, const QStringList& args);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
