/*                     E X I T C M D . C X X
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
/** @file ExitCmd.cxx
 * ExitCmd.cxx
 *
 *  Created on: Dec 16, 2010
 */

#include "ExitCmd.h"

ExitCmd::ExitCmd() : AbstractClientCmd("shutdown"){}
ExitCmd::~ExitCmd() {}

QString
ExitCmd::getUsage(){
	return "Usage: shutdown";
}

QString
ExitCmd::getHelp(){
	return "Sends a remote shutdown command to the GS server currently attached.";
}

bool
ExitCmd::_exec(GSClient* client, QStringList args){


}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */

