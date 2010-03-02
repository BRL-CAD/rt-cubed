/*        N E T S O C K P O R T A L M A N A G E R . C X X
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

#include "GS/libNetwork/NetPortalManager.h"
#include "GS/libNetwork/RemHostNameSetMsg.h"
#include <QTcpSocket>
#include <iostream>

NetPortalManager::NetPortalManager(QString hostName, QObject* parent) :
	QTcpServer(parent), localHostName(hostName)
{
	this->log = Logger::getInstance();
	this->hostnameToPortalMap = new QMap<QString, NetPortal*> ();
	this->portalList = new QList<NetPortal*> ();
}

NetPortalManager::~NetPortalManager()
{
	//TODO delete map and list?
}

NetPortal* NetPortalManager::getNewPortal(int socketDescriptor)
{
	NetPortal* portal;
	//Create new NSP
	if (socketDescriptor == 0)
	{
		portal = new NetPortal(this);
	}
	else
	{
		portal = new NetPortal(this, socketDescriptor);
	}

	this->registerPortal(portal);

	QObject::connect(portal, SIGNAL(disconnect()), this, SLOT(
			handlePortalDisconnect()));

QObject::connect(portal, SIGNAL(portalHandshakeComplete(QString, NetPortal*)), this, SLOT(mapPortalToHostname(QString, NetPortal*)));
}

void NetPortalManager::registerPortal(NetPortal* portal)
{
	this->portalList->append(portal);
}

void NetPortalManager::mapPortalToHostname(QString hostname, NetPortal* portal)
{
	this->hostnameToPortalMap->insert(hostname, portal);
}

void NetPortalManager::incomingConnection(int socketDescriptor)
{
	NetPortal* nsp = this->getNewPortal();

	//	nsp->setSocketDescriptor(socketDescriptor);
	//	nsp->handshakeStatus = NetPortal::HandshakeStatus::Handshaking;

	//Send the localhostName to the Remote machine.
	this->sendLocalHostName(nsp);

	emit newIncomingConnection(nsp);
}

void NetPortalManager::handlePortalDisconnect()
{
	NetPortal* nsp = (NetPortal*) sender();

	//Map the NSP
	NetPortalManager::hostnameToPortalMap->remove(nsp->getRemoteHostName());
}

void NetPortalManager::sendLocalHostName(NetPortal* nsp)
{
	RemHostNameSetMsg msg(this->localHostName);
	nsp->send(msg);
}

NetPortal* NetPortalManager::getPortalByRemHostname(QString remHostName)
{
	return NetPortalManager::hostnameToPortalMap->value(remHostName, NULL);
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// ex: shiftwidth=4 tabstop=8
