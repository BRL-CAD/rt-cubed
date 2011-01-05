/*             G E O M E T R Y S E R V I C E . C X X
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
/** @file GeometryService.cxx
 *
 * Brief description
 *
 */

#include "GeometryService.h"
#include "SessionManager.h"
#include "FileDataSource.h"
#include "PingMsg.h"
#include "PongMsg.h"


GeometryService::GeometryService(const QString localNodeName, const quint16 listenPort, const QHostAddress listenAddy) :
localNodeName(localNodeName), listenPort(listenPort), listenAddy(listenAddy)
{
    this->log = Logger::getInstance();
    this->log->logINFO("GeometryService", localNodeName + " is starting up...");

    this->portalMan = new PortalManager(localNodeName, listenPort);
    this->registerMsgRoutes();

    this->dataMan = DataManager::getInstance();
}

GeometryService::~GeometryService()
{
	delete portalMan;
}

DataManager*
GeometryService::getDataManager()
{
	return this->dataMan;
}

void
GeometryService::registerMsgRoutes()
{
	NetMsgRouter* router = NetMsgRouter::getInstance();

	router->registerType(PING, this);
	router->registerType(PONG, this);

	router->registerType(NEWSESSIONREQ, SessionManager::getInstance());
	//router->registerType(SESSIONINFO, SessionManager::getInstance());
	router->registerType(DISCONNECTREQ, SessionManager::getInstance());

	router->registerType(DISCONNECTREQ, this->portalMan);

	router->registerType(CMD_SHUTDOWN, this);

	router->registerType(GEOMETRYREQ, this->dataMan);
	router->registerType(GEOMETRYCHUNK, this->dataMan);
}

bool
GeometryService::preRunHook() {
	//Do initi stuff here
	this->log->logINFO("GeometryService", "Running");

	return true;
}

void
GeometryService::_run() {
	this->log->logINFO("GeometryService", "Starting PortalManager");
	this->portalMan->start();

	while (this->runCmd) {
		GSThread::msleep(100);
	}

	this->portalMan->shutdown();
}

bool
GeometryService::postRunHook() {
	//Do teardown stuff here
	this->log->logINFO("GeometryService", "Shutdown");

	return true;
}

bool
GeometryService::handleNetMsg(NetMsg* msg)
{
	quint16 type = msg->getMsgType();
	switch(type) {
	case CMD_SHUTDOWN:
		log->logINFO("GeometryService", "Remote Shutdown Initiated.");
		this->portalMan->terminate(false);
		this->terminate(false);
		return true;
	case FAILURE:
		{
			FailureMsg* fMsg = (FailureMsg*)msg;
			quint8 fc = fMsg->getFailureCode();

			QUuid re = fMsg->getReUUID();

			log->logINFO("GeometryService", "Recv'ed A FailureMsg with code: " +QString::number( fc) + " (" + QString::number(fc, 16)+ ")");
			return true;
		}
	case PING:
		{
			Portal* p = msg->getOrigin();

			if (p != NULL) {
				QString remNodeName = p->getRemoteNodeName();
				log->logINFO("GeometryService", "PING from: '" + remNodeName + "'");
				PongMsg pongMsg((PingMsg*)msg);
				p->send(&pongMsg);
			} else {
				log->logINFO("GeometryService", "Can't return ping.  NULL Portal*");
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

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
