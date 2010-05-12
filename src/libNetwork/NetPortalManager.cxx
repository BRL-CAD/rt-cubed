/*        N E T P O R T A L M A N A G E R . C X X
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
/** @file NetPortalManager.cxx
 *
 * Brief description
 *
 */

#include "NetPortalManager.h"
#include "NetPortal.h"
#include "RemoteGSHostnameSetMsg.h"
#include <QTcpSocket>
#include <iostream>

NetPortalManager::NetPortalManager(QString localGSHostame,
	INetMsgHandler* handler, QObject* parent) :
    localGSHostname(localGSHostame), handler(handler), QTcpServer(parent)
{
    this->log = Logger::getInstance();
    this->gsHostnameToPortalMap = new QMap<QString, NetPortal*> ();
    this->portalList = new QList<NetPortal*> ();
}

NetPortalManager::~NetPortalManager()
{
    //TODO delete map and list?
}

NetPortal* NetPortalManager::getNewPortal(int socketDescriptor)
{
    //Create new NSP
    NetPortal* portal;
    if (socketDescriptor == 0) {
	portal = new NetPortal(this, handler);
    }
    else {
	portal = new NetPortal(this, handler, socketDescriptor);
    }

    this->registerPortal(portal);

    EventManager::getInstance()->subscribe(this,
	    EVENTTYPE_PORTAL_DISCONNECT, portal);

    EventManager::getInstance()->subscribe(this,
 	    EVENTTYPE_PORTAL_HANDSHAKE_COMPLETE, portal);

    return portal;
}

void NetPortalManager::registerPortal(NetPortal* portal)
{
    this->portalList->append(portal);
}

void NetPortalManager::mapPortalToGSHostname(NetPortal* portal)
{
    this->gsHostnameToPortalMap->insert(portal->getRemoteGSHostname(), portal);
}

void NetPortalManager::unregisterPortal(NetPortal* portal)
{
    this->portalList->removeAll(portal);
}

void NetPortalManager::unmapPortalToGSHostname(NetPortal* portal)
{
    this->gsHostnameToPortalMap->remove(portal->getRemoteGSHostname());
}

void NetPortalManager::incomingConnection(int socketDescriptor)
{
    NetPortal* nsp = this->getNewPortal(socketDescriptor);

    //Send the localhostName to the Remote machine.
    nsp->sendLocalGSHostnameToRemoteGSHost();

}


NetPortal* NetPortalManager::getPortalByRemoteGSHostname(QString remGSHostname)
{
    return NetPortalManager::gsHostnameToPortalMap->value(remGSHostname, NULL);
}

QString NetPortalManager::getLocalGSHostname()
{
    return this->localGSHostname;
}

void NetPortalManager::localLog(QString str)
{
    QString nStr = "[" + this->localGSHostname + "] " + str;
    this->log->logINFO("NetPortalManager", nStr);
}

void NetPortalManager::handleEvent(Event* e)
{
    quint32 type = e->getEventType();

    switch (type) {
    case EVENTTYPE_PORTAL_HANDSHAKE_COMPLETE:
 	{
 	    NetPortal* np = (NetPortal*) e->getPublisher();
 	    this->mapPortalToGSHostname(np);
 	}
 	break;
    case EVENTTYPE_PORTAL_DISCONNECT:
 	{
 	    NetPortal* np = (NetPortal*) e->getPublisher();
 	    this->unregisterPortal(np);
 	    this->unmapPortalToGSHostname(np);

 	}
 	break;
     default:
	//unhandled Event type;
	return;
    }
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// ex: shiftwidth=4 tabstop=8
