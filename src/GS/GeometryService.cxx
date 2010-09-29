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

GeometryService::GeometryService(const QString localNodeName, quint16 listenPort) :
localNodeName(localNodeName), listenPort(listenPort)
{
    this->log = Logger::getInstance();
    this->log->logINFO("GeometryService", localNodeName + " is starting up...");

    this->pm = new PortalManager(listenPort);

    this->registerMsgRoutes();

}

GeometryService::~GeometryService()
{
	delete pm;
}

void
GeometryService::registerMsgRoutes()
{
	NetMsgRouter* router = NetMsgRouter::getInstance();

	router->registerType(NEWSESSIONREQ, SessionManager::getInstance());
	router->registerType(SESSIONINFO, SessionManager::getInstance());
	router->registerType(DISCONNECTREQ, SessionManager::getInstance());

	router->registerType(DISCONNECTREQ, this->pm);

	router->registerType(CMD_SHUTDOWN, this);

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
	this->pm->start();

	while (this->runCmd) {
		GSThread::sleep(100);
	}

	this->pm->shutdown();
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
		this->shutdown();
		return true;
	}
	return false;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
