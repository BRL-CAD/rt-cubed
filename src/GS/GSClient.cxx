/*                    G S C L I E N T . C X X
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
/** @file GSClient.cxx
 * GSClient.cxx
 *
 */

#include "GSClient.h"
#include "NetMsgRouter.h"

#include "AbstractClientCmd.h"
#include "ExitCmd.h"
#include "HelpCmd.h"
#include "LoginCmd.h"
#include "LogoutCmd.h"
#include "ShutdownCmd.h"
#include "PingCmd.h"

const std::string GSClient::defaultPrompt ="geoclient> ";

GSClient::GSClient(QString localNodeName) {
	this->ccReg = ClientCmdRegistry::getInstance();
	this->log = Logger::getInstance();
	this->jobMan = JobManager::getInstance();
	this->jobMan->startup();

	this->portMan = new PortalManager(localNodeName);
	this->portMan->start();
	GSThread::msleep(100);

	this->currentPortal = NULL;

	this->stayRun = true;
	this->prompt = defaultPrompt;

	this->registerClientCmds();
	this->registerMsgRoutes();
}

GSClient::~GSClient() {
	delete this->portMan;
}

void
GSClient::registerClientCmds()
{
	/* Command Registrations */
	this->ccReg->registerCmd(new HelpCmd());
	this->ccReg->registerCmd(new ExitCmd());
	this->ccReg->registerCmd(new LoginCmd());
	this->ccReg->registerCmd(new LogoutCmd());
	this->ccReg->registerCmd(new ShutdownCmd());
	this->ccReg->registerCmd(new PingCmd());
}

void
GSClient::registerMsgRoutes()
{
	NetMsgRouter* router = NetMsgRouter::getInstance();

	router->registerType(DISCONNECTREQ, this->portMan);
	router->registerType(SESSIONINFO, this);
	router->registerType(FAILURE, this);
	router->registerType(PING, this);
	router->registerType(PONG, this);
}

bool
GSClient::handleNetMsg(NetMsg* msg)
{
	quint16 type = msg->getMsgType();
	switch(type) {
	case SESSIONINFO:
		{
			QString data =((SessionInfoMsg*)msg)->toString();
			log->logINFO("GSClient", "Recv'ed SessionInfo: " + data);
			return true;
		}
	case FAILURE:
		{
			FailureMsg* fMsg = (FailureMsg*)msg;
			quint8 fc = fMsg->getFailureCode();

			QUuid re = fMsg->getReUUID();

			log->logINFO("GSClient", "Recv'ed A FailureMsg with code: " +QString::number( fc) + " (" + QString::number(fc, 16)+ ")");
			return true;
		}
	case PING:
		{
			Portal* p = msg->getOrigin();

			if (p != NULL) {
				QString remNodeName = p->getRemoteNodeName();
				log->logINFO("GSClient", "PING from: '" + remNodeName + "'");
				PongMsg pongMsg((PingMsg*)msg);
				p->send(&pongMsg);
			} else {
				log->logINFO("GSClient", "Can't return ping.  NULL Portal*");
			}
			return true;
		}
	case PONG:
		{
			Portal* p = msg->getOrigin();
			PongMsg* pongMsg = (PongMsg*)msg;

			/* calc current and differential times */
			quint64 start = pongMsg->getStartTime();
			quint64 now = Logger::getCurrentTime();
			quint64 diff = now -start;

			QString time = "roundtrip time: " + QString::number(diff) + "ms.";
			QString remNodeName = "unknown";

			if (p != NULL) {
				remNodeName = p->getRemoteNodeName();
			}

			log->logINFO("GSClient", "Pong from: '" + remNodeName + "', " + time);
			return true;
		}
	}
	return false;
}


int
GSClient::run()
{
	this->log->logBANNER("geoclient","==================================");
	this->log->logBANNER("geoclient","GeometryService Test/Stress Client");
	this->log->logBANNER("geoclient","==================================");

	std::string in;
	while (this->stayRun) {
		in == "";
		std::cout << prompt;
		getline (std::cin, in);

		/* make a qstring */
		QString qin(in.c_str());

		/* cathc zero length strings here */
		if (qin.length() == 0)
			continue;

	    /* split string */
		QStringList list = qin.split(" ");

		/* check to see if there is at least one element */
		if (list.length() <= 0) {
			continue;
		}

		/* convert to lowercase */
		QString cmd = list.takeFirst().toLower();

		this->execCmd(cmd, list);
	}

	if (this->currentPortal != NULL)
		this->currentPortal->disconnect();

	if (this->portMan != NULL)
		this->portMan->shutdown();

	if (this->jobMan != NULL)
		this->jobMan->shutdown();

	this->log->logINFO("geoclient","Exiting.");
	return 0;
}

bool
GSClient::execCmd(QString cmd, QStringList args)
{
	AbstractClientCmd* acc = this->ccReg->getCmd(cmd);

	if (acc == NULL) {
		this->log->logINFO("GSClient", "Unknown Command: '" + cmd + "'.");
		return false;
	}

	return acc->exec(this, args);
}

PortalManager*
GSClient::getPortMan()
{
	return this->portMan;
}

Portal*
GSClient::getCurrentPortal()
{
	return this->currentPortal;
}

void
GSClient::stopRun()
{
	this->stayRun = false;
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
