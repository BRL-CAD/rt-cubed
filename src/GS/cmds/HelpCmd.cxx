/*                     H E L P C M D . C X X
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
/** @file HelpCmd.cxx
 * HelpCmd.cxx
 *
 *  Created on: Dec 16, 2010
 */

#include "HelpCmd.h"
#include "ClientCmdRegistry.h"

HelpCmd::HelpCmd() : AbstractClientCmd("help") {}

HelpCmd::~HelpCmd() {}

QString
HelpCmd::getUsage() {
	return "Usage: help [cmdname]";
}

QString
HelpCmd::getHelp() {
	return "If envoked without any arguments, help diplays a list of available commands.  If a command name is provided as an argument, the help for that command is displayed.";
}

bool
HelpCmd::_exec(GSClient* client, QStringList args){

	int argn = args.length();

	if (argn < 0 || argn > 1) {
		this->log->logERROR("HelpCmd", this->getUsage());
		return false;
	}

	ClientCmdRegistry* ccReg = ClientCmdRegistry::getInstance();

	if (argn == 0) {
		/* display list of cmds */
		QList<QString>* cmds = ccReg->getListOfCmds();



		delete cmds;
		return true;
	}




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

