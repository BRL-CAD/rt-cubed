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

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include "GE/Logger.h"
#include "GS/libNetwork/NetMsgFactory.h"

class NetPortalManager;

class NetPortal: public QObject
{
Q_OBJECT
//friend class NetPortalManager;
public:
	NetPortal(NetPortalManager* parent);
	NetPortal(NetPortalManager* parent, int socketDescriptor);
	virtual ~NetPortal();

	void connectToHost(QString hostname, quint16 port);
	void connectToHost(QHostAddress address, quint16 port);
	void disconnectFromHost(quint8 reason);

	void attemptToBuildMsg();

	bool hasMsg();
	NetMsg* getNextMsg();

	void send(NetMsg& msg);

	QString getRemoteHostName();

	enum HandshakeStatus
	{
		NotConnected = 0, Handshaking = 5, Ready = 10, Failed = 15,
	};

	signals:
	void msgReady();
	void handshakeStatusUpdate(HandshakeStatus current, HandshakeStatus old);
	void portalHandshakeComplete(NetPortal* portal);

	void portalConnected();
	void portalDisconnected();
	void socketError(QAbstractSocket::SocketError err);

public slots:
	void sendLocalHostnameToRemHost();

protected slots:
	void moveDataFromSocketBuffer();
	void relaySockConnected();
	void relaySockDisconnected();
	void relaySockError(QAbstractSocket::SocketError err);

private:
	QTcpSocket* sock;
	NetPortalManager* nspm;
	QString remHostName;
	NetMsgFactory* factory;
	HandshakeStatus handshakeStatus;
	Logger* log;

	void constructorCommon(NetPortalManager* nspm);
	void updateHandshakeStatus(HandshakeStatus newStatus);
};

#endif

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
