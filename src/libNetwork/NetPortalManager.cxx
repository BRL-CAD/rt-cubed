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

NetPortalManager::NetPortalManager(QString localGSHostame,  QObject* parent) :
    QTcpServer(parent), localGSHostname(localGSHostame)
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
	portal = new NetPortal(this);
    }
    else {
	portal = new NetPortal(this, socketDescriptor);
    }

    //If there is a default Handler defined, set the new portal's handler.
    if (this->handler) {
	portal->setNetMsgHandler(this->handler);
    }

    this->registerPortal(portal);

    QObject::connect(portal, SIGNAL(portalDisconnected()), this, SLOT(
	    handlePortalDisconnect()));

    QObject::connect(portal, SIGNAL(portalHandshakeComplete(NetPortal*)), this, SLOT(mapPortalToGSHostname(NetPortal*)));

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

void NetPortalManager::unmapPortalToGSHostname(QString hostname)
{
    this->gsHostnameToPortalMap->remove(hostname);
}

void NetPortalManager::incomingConnection(int socketDescriptor)
{
    NetPortal* nsp = this->getNewPortal(socketDescriptor);

    //Send the localhostName to the Remote machine.
    nsp->sendLocalGSHostnameToRemoteGSHost();

    emit newIncomingConnection(nsp);
}

void NetPortalManager::handlePortalDisconnect()
{
    NetPortal* nsp = (NetPortal*) sender();

    //UnMap the NSP
    this->unregisterPortal(nsp);
    this->unmapPortalToGSHostname(nsp->getRemoteGSHostname());

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
    QString nStr = "[" + this->localGSHostname + "] "+ str;
    this->log->logINFO("NetPortalManager", nStr);
}

INetMsgHandler* NetPortalManager::getNetMsgHandler()
{
    return this->handler;
}
void NetPortalManager::setNetMsgHandler(INetMsgHandler* handler)
{
    this->handler = handler;
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// ex: shiftwidth=4 tabstop=8
