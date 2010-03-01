/*                 U N K N O W N C O M M A N D . H
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file UnknownCommand.h
 *
 * Brief description
 *
 */

#include "UnknownCommand.h"

UnknownCommand::UnknownCommand() :
	AbstractCommand()
{
}

UnknownCommand::~UnknownCommand()
{
}

JobResult UnknownCommand::_doJob()
{
//	this->box->addC2S("Error", this->cmd + " is an unknown command.");
}

// Local Variables:
// mode: C++
// tab-width: 8
// c-basic-offset: 2
// indent-tabs-mode: t
// End:
// ex: shiftwidth=2 tabstop=8
