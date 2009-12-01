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
#include <iostream>

NetSockPortalManager::NetSockPortalManager(QString hostName, QString version,
		QObject* parent) :
	QTcpServer(parent), localHostName(hostName), localVersion(version)
{

}

NetSockPortalManager::~NetSockPortalManager()
{
}

bool NetSockPortalManager::hasPendingPortal()
{
	return !this->pendingConns.empty();
}

NetSockPortal* NetSockPortalManager::connectTo(QHostAddress addy, quint16 port)
{
	QTcpSocket* sock = new QTcpSocket(this);
	NetSockPortal* nsp = this->prepareNewPortal(sock);

	//Wire up a signal to send the handshake info on connect
	QObject::connect(sock, SIGNAL(connected()), this, SLOT(
			sendHostVersionOnConnect()));

	sock->connectToHost(addy, port);

	return nsp;
}

void NetSockPortalManager::incomingConnection(int socketDescriptor)
{
	QTcpSocket* sock = new QTcpSocket();
	sock->setSocketDescriptor(socketDescriptor);

	this->prepareNewPortal(sock);
}

NetSockPortal* NetSockPortalManager::prepareNewPortal(QTcpSocket* sock)
{
	NetSockPortal* nsp = new NetSockPortal(sock);
	nsp->portStatus = NetSockPortal::Handshaking_HostNameLen;

	//Add to handshaking list
	this->handshakingConns.append(nsp);

	QObject::connect(nsp, SIGNAL(readyRead()), this, SLOT(
			handlePortalHandshake()));

	return nsp;
}

void NetSockPortalManager::handlePortalHandshake()
{
	NetSockPortal* nsp = (NetSockPortal*) sender();

	// Do some ID-10-T checks.
	if (nsp == 0)
	{
		return;
	}
	if (nsp->bytesAvailable() == 0)
	{
		return;
	}

	//HostNameLen
	if (nsp->portStatus == NetSockPortal::Handshaking_HostNameLen
			&& nsp->bytesAvailable() >= 4)
	{

		QByteArray ba = nsp->read(4);
		bool ok;
		quint32 len = ba.toUInt(&ok);

		if (len > NetSockPortalManager::MaxRemoteHostNameLen)
		{
			std::cerr << "RemoteHostName's Len exceeded Maximum.\n";
			nsp->disconnectFromHost();
			return;
		}

		if (ok)
		{
			nsp->remHostNameLen = len;
			nsp->portStatus = NetSockPortal::Handshaking_HostName;
		}
		else
		{
			std::cerr << "Bytes to uint conversion failure.\n";
			nsp->disconnectFromHost();
			return;
		}
	}

	//HostName
	if (nsp->portStatus == NetSockPortal::Handshaking_HostName
			&& nsp->bytesAvailable() >= nsp->remHostNameLen)
	{

		QByteArray ba = nsp->read(nsp->remHostNameLen);
		nsp->remHostName = "";
		nsp->remHostName.append(ba);
		nsp->portStatus = NetSockPortal::Handshaking_VersionLen;
	}

	//VersionLen
	if (nsp->portStatus == NetSockPortal::Handshaking_VersionLen
			&& nsp->bytesAvailable() >= 4)
	{

		QByteArray ba = nsp->read(4);
		bool ok;
		quint32 len = ba.toUInt(&ok);

		if (len != this->localVersion.length())
		{
			std::cerr << "RemoteVersion's Len is not the same as local's.\n";
			nsp->disconnectFromHost();
			return;
		}

		if (ok)
		{
			nsp->remVersionLen = len;
			nsp->portStatus = NetSockPortal::Handshaking_Version;
		}
		else
		{
			std::cerr << "Bytes to uint conversion failure.\n";
			nsp->disconnectFromHost();
			return;
		}
	}

	//Version
	if (nsp->portStatus == NetSockPortal::Handshaking_Version
			&& nsp->bytesAvailable() >= nsp->remVersionLen)
	{

		QByteArray ba = nsp->read(nsp->remVersionLen);
		nsp->remVersion = "";
		nsp->remVersion.append(ba);

		if (nsp->remVersion != this->localVersion)
		{
			std::cerr << "RemoteVersion is not the same as local's.\n";
			nsp->disconnectFromHost();
			return;
		}

		nsp->portStatus = NetSockPortal::Ready;

		this->handshakingConns.removeAll(nsp);
		this->pendingConns.append(nsp);

		//No longer need to recieve this signal
		QObject::disconnect(nsp, SIGNAL(readyRead()), this, SLOT(
				handlePortalHandshake()));
		emit newConnection();
	}

}

void NetSockPortalManager::sendHostVersionOnConnect()
{
	QTcpSocket* sock = (QTcpSocket*) sender();

	if (sock == 0)
	{
		return;
	}

	QByteArray toSend;

	toSend.append(QByteArray::number(this->localHostName.length()));
	toSend.append(this->localHostName.toAscii());

	toSend.append(QByteArray::number(this->localVersion.length()));
	toSend.append(this->localVersion.toAscii());

	sock->write(toSend);

	QObject::disconnect(sock, SIGNAL(connected()), this, SLOT(
			sendHostVersionOnConnect()));

}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// ex: shiftwidth=4 tabstop=8
