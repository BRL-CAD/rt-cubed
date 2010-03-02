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
	this->portalList = new QList<NetPortal*>();
}

NetPortalManager::~NetPortalManager()
{
	//TODO delete map and list?
}


NetPortal* NetPortalManager::getNewPortal()
{
	//Create new NSP and setup signals
	NetPortal* portal = new NetPortal(this);

	this->registerPortal(portal);

	//Set up signal prior to initializing the NSP with a socket Descriptor
	QObject::connect(portal, SIGNAL(portalHandshakeComplete()), this, SLOT(
			handlePortalHandshakeCompleted()));

	QObject::connect(portal, SIGNAL(disconnect()), this, SLOT(
			handlePortalDisconnect()));
}

void NetPortalManager::registerPortal(NetPortal* portal)
{
	this->portalList->append(portal);
}

void NetPortalManager::mapPortalToHostname(QString hostname, NetPortal* portal)
{
	this->hostnameToPortalMap->insert(hostname, portal);
}

NetPortal* NetPortalManager::preparePortal()
{
	//Create new NSP and setup signals
	NetPortal* nsp = new NetPortal(this);

	//Set up signal prior to initializing the NSP with a socket Descriptor
	QObject::connect(nsp, SIGNAL(portalHandshakeComplete()), this, SLOT(
			handlePortalHandshakeCompleted()));

	QObject::connect(nsp, SIGNAL(disconnect()), this, SLOT(
			handlePortalDisconnect()));
}

void NetPortalManager::incomingConnection(int socketDescriptor)
{
	NetPortal* nsp = this->preparePortal();

//	nsp->setSocketDescriptor(socketDescriptor);
//	nsp->handshakeStatus = NetPortal::HandshakeStatus::Handshaking;

	//Send the localhostName to the Remote machine.
	this->sendLocalHostName(nsp);

	emit newIncomingConnection(nsp);
}

void NetPortalManager::handleOutgoingConnect()
{
	NetPortal* nsp = (NetPortal*) sender();

//	QString msg;
//	msg += "Accepted new connection from: " + nsp->peerAddress().toString() + ":" + nsp->peerPort() + "\n";
//	this->log->log(Logger::INFO, msg);

	//Send the localhostName to the Remote machine.
	this->sendLocalHostName(nsp);

	QObject::disconnect(nsp, SIGNAL(connected()), this, SLOT(
			handleOutgoingConnect(nsp)));

	emit newOutgoingConnection(nsp);
}

void NetPortalManager::handlePortalHandshakeCompleted()
{
	NetPortal* nsp = (NetPortal*) sender();

	//Map the NSP
	NetPortalManager::hostnameToPortalMap->insert(nsp->getRemoteHostName(), nsp);

	QObject::disconnect(nsp, SIGNAL(portalHandshakeComplete()), this, SLOT(
			handlePortalHandshakeCompleted()));

	QString msg;
	msg += "Handshake with " + nsp->getRemoteHostName() + " completed.\n";
	this->log->log(Logger::INFO, msg);
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
