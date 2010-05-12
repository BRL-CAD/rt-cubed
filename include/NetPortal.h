/*                     N E T P O R T A L . H
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
/** @file NetPortal.h
 *
 * Brief description
 *
 */

#ifndef __NETPORTAL_H__
#define __NETPORTAL_H__

#include "libutility.h"
#include "NetMsg.h"
#include "NetMsgFactory.h"
#include "RemoteGSHostnameSetMsg.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QString>

class INetMsgHandler;
class NetPortalManager;

class NetPortal: public QObject
{
Q_OBJECT

public:
	NetPortal(NetPortalManager* parent, INetMsgHandler* handler);
	NetPortal(NetPortalManager* parent, INetMsgHandler* handler, int socketDescriptor);
	virtual ~NetPortal();

	void connectToNetHost(QString netHostname, quint16 port);
	void connectToNetHost(QHostAddress address, quint16 port);
	void disconnectFromNetHost(quint8 reason = LOCAL_DISCONNECT_REQ);

	void attemptToBuildMsg();

	bool hasMsg();
	NetMsg* getNextMsg(bool peek = false);

	void send(NetMsg& msg);
	void quickSend(quint32 opcode);

	QString getRemoteGSHostname();

	bool isOpen();

	enum HandshakeStatus
	{
		NotConnected = 0, Handshaking = 5, Ready = 10, Failed = 15,
	};

signals:
	void msgReady();
	void handshakeStatusUpdate(quint32 current, quint32 old);
	void portalHandshakeComplete(NetPortal* portal);

	void portalConnected();
	void portalDisconnected();
	void socketError(QAbstractSocket::SocketError err);

public slots:
	void sendLocalGSHostnameToRemoteGSHost();

protected slots:
	void moveDataFromSocketBuffer();
	void relaySockConnected();
	void relaySockDisconnected();
	void relaySockError(QAbstractSocket::SocketError err);

private:
	QTcpSocket* sock;
	NetPortalManager* nspm;
	QString remGSHostname;
	NetMsgFactory* factory;
	HandshakeStatus handshakeStatus;
	Logger* log;
	INetMsgHandler* handler;

	void constructorCommon(NetPortalManager* nspm, INetMsgHandler* handler);
	void updateHandshakeStatus(HandshakeStatus newStatus);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

