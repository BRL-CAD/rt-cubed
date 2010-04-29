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
#include "utility.h"

GeometryService::GeometryService(int& argc, char* argv[], QString gsHostname) :
    BaseApp(argc, argv), localGSHostname(gsHostname)
{
    this->log->logINFO("GeometryService ", gsHostname + " is starting up...");
    this->portalMan = new NetPortalManager(gsHostname);

    QObject::connect(portalMan, SIGNAL(newIncomingConnection(NetPortal*)), this, SLOT(handleNewPortal(NetPortal*) ) );
}

GeometryService::~GeometryService()
{
    delete this->portalMan;
}

void GeometryService::startListening(const QHostAddress& addy, quint16 port)
{
    this->portalMan->listen(addy, port);
}

void GeometryService::handleNewPortal(NetPortal* nsp)
{
    this->log->logINFO("GeometryService",
	    "New portal received from NetPortalManager");

    QObject::connect(nsp, SIGNAL(msgReady()), this, SLOT(handleMsgReady()));
}

void GeometryService::handleMsgReady()
{
    NetPortal* np = (NetPortal*) QObject::sender();
    NetMsg* msg = np->getNextMsg();

    if (msg != NULL) {
	this->handleNetMsg(msg, np);
    }
}

void GeometryService::handleNetMsg(NetMsg* msg, NetPortal* origin)
{
    quint32 msgType = msg->getMsgType();

    switch (msgType) {

    case (NEWSESSIONREQ):
	{
	    //Route to SessionManager
	    SessionManager::getInstance()->handleNetMsg(msg, origin);

	    break;
	}
    default:
	{
	    throw new GSException("Does not handle this MsgType");
	    break;
	}
    };

}

int GeometryService::exec()
{
    //Startup prior to exec()


    return QCoreApplication::exec();
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
