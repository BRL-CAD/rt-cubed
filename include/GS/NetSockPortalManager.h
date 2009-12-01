/*          N E T S O C K P O R T A L M A N A G E R . H
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
/** @file NetSockPortalManager.h
 *
 * Brief description
 *
 */
#ifndef __NETSOCKPORTALMANAGER_H__
#define __NETSOCKPORTALMANAGER_H__

#include "GS/NetSockPortal.h"

#include <QTcpServer>
#include <QHostAddress>
#include <QMap>
#include <QUuid>
#include <QList>
#include <QByteArray>

class NetSockPortalManager: public QTcpServer
{
Q_OBJECT

public:
			NetSockPortalManager(QString hostName, QString version,
					QObject* parent = 0);
	~NetSockPortalManager();

	NetSockPortal nextPendingPortal();
	bool hasPendingPortal();

	NetSockPortal* connectTo(QHostAddress addy, quint16 port);

protected:
	void incomingConnection(int socketDescriptor);
	NetSockPortal* prepareNewPortal(QTcpSocket* sock);

protected slots:
	void handlePortalHandshake();
	void sendHostVersionOnConnect();

private:
	static const quint16 MaxRemoteHostNameLen = 512;

	QString localHostName;
	QString localVersion;

	QMap<QString, NetSockPortal*> portalList;

	/*
	 * A Pending connection is a Portal that hasn't completed its Handshake with the other side yet.
	 */
	QList<NetSockPortal*> pendingConns;
	QList<NetSockPortal*> handshakingConns;

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
