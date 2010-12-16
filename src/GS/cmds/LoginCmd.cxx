/*                    L O G I N C M D . C X X
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
/** @file LoginCmd.cxx
 * LoginCmd.cxx
 *
 *  Created on: Dec 16, 2010
 *      
 */

#include "LoginCmd.h"
#include "PortalManager.h"

LoginCmd::LoginCmd() : AbstractClientCmd("login"){}
LoginCmd::~LoginCmd() {}

QString
LoginCmd::getUsage() {
	return "Usage: login ip port uname passwd";
}

QString
LoginCmd::getHelp() {
	return "Attempts to make a connection and login to a GeometryService.";
}

bool
LoginCmd::_exec(GSClient* client, QStringList args){
	PortalManager* pm = client->getPortMan();

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

