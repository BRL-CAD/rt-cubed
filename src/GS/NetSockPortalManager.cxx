/*        N E T S O C K P O R T A L M A N A G E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file NetSockPortalManager.cxx
 *
 * Brief description
 *
 */

#include "GS/NetSockPortalManager.h"
#include <QTcpSocket>

NetSockPortalManager::NetSockPortalManager()
{
    this->listenServer = new QTcpServer();
}

NetSockPortalManager::~NetSockPortalManager()
{
    delete this->listenServer;
}


/******************************
 * DELEGATES - QTcpServer
 ******************************/

/*
 * Listen on 'port' using ALL network interfaces.
 */
bool NetSockPortalManager::listen(quint16 port)
{
    bool retVal = this->listenServer->listen(QHostAddress::Any, port);

    QObject::connect(listenServer, SIGNAL( newConnection() ), this, SLOT( handleNewConnection() ));

    return retVal;
}

/*
 * Listen on 'port' using 'host' network interface.
 */
bool NetSockPortalManager::listen(QHostAddress& host, quint16 port)
{
    bool retVal = this->listenServer->listen(host,port);

    QObject::connect(listenServer, SIGNAL( newConnection() ), this, SLOT( handleNewConnection() ));

    return retVal;
}

/*
 * Stop listening on all interfaces and all ports..
 */
void NetSockPortalManager::stopListening()
{
    this->listenServer->close();

    QObject::disconnect(listenServer, SIGNAL( newConnection() ), this, SLOT( handleNewConnection() ));

}


/******************************
 * SLOTS
 ******************************/

void NetSockPortalManager::handleNewConnection()
{
    if ( ! this->listenServer->hasPendingConnections()) {
	return;
    }

    QTcpSocket* newSock = this->listenServer->nextPendingConnection();
    NetSockPortal* nsp = new NetSockPortal(newSock);

   //Initially, use the UUID to map the portal.
   //Ultimately, the RemoteHost name will be used.

    this->portalList.insert(nsp->getPortalId(), nsp);
}




// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
