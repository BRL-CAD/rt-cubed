/*             C O M M A N D F A C T O R Y . C X X
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file CommandFactory.cxx
 *
 *
 *
 */

#include "CommandFactory.h"

CommandFactory::CommandFactory()
{
}

CommandFactory::~CommandFactory()
{
}

AbstractJob* CommandFactory::parseCommand(QString cmdLine)
{
	QStringList cmdList = cmdLine.replace("  ", " ").split(" ", QString::SkipEmptyParts);
}

AbstractJob* CommandFactory::parseCommand(QStringList cmdList)
{
	if (cmdList.size() == 0) {
		return NULL;
	}



}

// Local Variables:
// mode: C++
// tab-width: 8
// c-basic-offset: 2
// indent-tabs-mode: t
// End:
// ex: shiftwidth=2 tabstop=8
