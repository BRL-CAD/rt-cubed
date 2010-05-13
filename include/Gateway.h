/*                       G A T E W A Y . H
 * BRLCAD
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
/** @file Gateway.h
 *
 * Wraps up a NetPortalManager, a QThread and all supporting code to make a simple to use, internally threaded Gateway.
 *
 */

#ifndef __GATEWAY_H__
#define __GATEWAY_H__

#include "INetMsgHandler.h"

#include "libutility.h"

#include <QThread>
#include <QString>
#include <QHostAddress>
#include <QList>

class NetPortalManager;

class Gateway: public QThread
{
public:
    Gateway(QString gsHostname, INetMsgHandler* handler);
    virtual ~Gateway();

    void run();
    void stop();

    void listen(QHostAddress address, ushort port);
    void stopListening();

    QList<QString>
    getConnectedHostList();
    void sendToHost(QString host, NetMsg* msg);


private:
    NetPortalManager* portMan;
    Logger* log;

};

#endif /* __GATEWAY_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
