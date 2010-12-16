/*                      G S C L I E N T . H
 * BRLCAD
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
/** @file GSClient.h
 * GSClient.h
 *
 */

#ifndef __GSCLIENT_H__
#define __GSCLIENT_H__

#include "ClientCmdRegistry.h"
#include "libutility.h"
#include "libnet.h"

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <string>
#include <iostream>
#include <stdlib.h>

class LoginCmd;
class GSClient: public INetMsgHandler {
	friend class LoginCmd;

public:
	GSClient();
	virtual ~GSClient();

	int run();
	void stopRun();

    bool handleNetMsg(NetMsg* msg);
	bool execCmd(QString cmd, QStringList args);

	PortalManager* getPortMan();
	Portal* getCurrentPortal();

protected:

private:
	void registerClientCmds();
	void registerMsgRoutes();

	ClientCmdRegistry* ccReg;
	Logger* log;
	JobManager* jobMan;

	PortalManager* portMan;
	Portal* currentPortal;

	bool stayRun;
	std::string prompt;
	const static std::string defaultPrompt;
};

#endif /* __GSCLIENT_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
