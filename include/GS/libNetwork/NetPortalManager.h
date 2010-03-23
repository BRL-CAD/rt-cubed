/*              N E T P O R T A L M A N A G E R . H
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
/** @file NetPortalManager.h
 *
 * Brief description
 *
 */

#ifndef __NETPORTALMANAGER_H__
#define __NETPORTALMANAGER_H__

#include "GE/Logger.h"

#include "GS/libNetwork/NetPortal.h"

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QMap>
#include <QUuid>
#include <QList>
#include <QByteArray>

class NetPortalManager: public QTcpServer
{
Q_OBJECT

public:
    NetPortalManager(QString hostName, QObject* parent = 0);
    ~NetPortalManager();

    QString getLocalHostName();
    NetPortal* getNewPortal(int socketDescriptor = 0);

    NetPortal* getPortalByRemHostname(QString remHostName);

    void localLog(QString str);
protected:
    void incomingConnection(int socketDescriptor);

protected slots:

    void handlePortalDisconnect();
    void mapPortalToHostname(NetPortal* portal);
    void unmapPortalToHostname(QString hostname);

signals:
void newIncomingConnection(NetPortal* nsp);

private:
    void registerPortal(NetPortal* portal);
    void unregisterPortal(NetPortal* portal);

    QString localHostName;
    Logger* log;

    QMap<QString, NetPortal*>* hostnameToPortalMap;
    QList<NetPortal*>* portalList;

    NetPortal* preparePortal();
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
