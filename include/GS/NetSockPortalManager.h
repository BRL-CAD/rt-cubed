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
	NetSockPortalManager(QString hostName, QObject* parent = 0);
	~NetSockPortalManager();

	NetSockPortal* connectTo(QHostAddress addy, quint16 port);
	NetSockPortal* getPortalByRemHostname(QString remHostName);

protected:
	void incomingConnection(int socketDescriptor);

protected slots:
	void handleOutgoingConnect();
	void handlePortalHandshakeCompleted();
	void handlePortalDisconnect();

signals:
void newIncomingConnection(NetSockPortal* nsp);
void newOutgoingConnection(NetSockPortal* nsp);

private:
	QString localHostName;

	QMap<QString, NetSockPortal*>* portalList;

	void sendLocalHostName(NetSockPortal* nsp);
	NetSockPortal* preparePortal();
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
