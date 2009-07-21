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

#include "GS/AbstractPortalManager.h"
#include "GS/NetSockPortal.h"

#include <QTcpServer>
#include <QHostAddress>
#include <QMap>
#include <QUuid>

class NetSockPortalManager : public AbstractPortalManager
{
    Q_OBJECT

public:
    NetSockPortalManager();
    ~NetSockPortalManager();

    bool listen(quint16 port);
    bool listen(QHostAddress& host, quint16 port);
    void stopListening();

protected:

private slots:
    void handleNewConnection();

private:

    QMap<QString, NetSockPortal* > portalList;
    QTcpServer* listenServer;

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
