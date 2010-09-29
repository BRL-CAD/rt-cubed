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
#include "libnet.h"

GeometryService::GeometryService(const QString localNodeName, quint16 listenPort) :
localNodeName(localNodeName), listenPort(listenPort)
{
    this->log = Logger::getInstance();
    this->log->logINFO("GeometryService", localNodeName + " is starting up...");

    this->registerMsgRoutes();

}

GeometryService::~GeometryService()
{

}

void
GeometryService::registerMsgRoutes()
{
	NetMsgRouter* router = NetMsgRouter::getInstance();

	router->registerType(NEWSESSIONREQ, SessionManager::getInstance());
	router->registerType(SESSIONINFO, SessionManager::getInstance());
	router->registerType(DISCONNECTREQ, SessionManager::getInstance());

	//TODO need to register the PortalManager so it can recv DISCONNECTREQ msg also.

}

bool
GeometryService::preRunHook() {
	//Do initi stuff here
	this->log->logINFO("GeometryService", "Running");

	return true;
}

void
GeometryService::_run() {

	GSThread::sleep(2);

}

bool
GeometryService::postRunHook() {
	//Do teardown stuff here
	this->log->logINFO("GeometryService", "Shutdown");

	return true;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
