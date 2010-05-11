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

#include "NetPortalManager.h"

#include <QThread>

class Gateway: public QThread
{
public:
    Gateway(QString gsHostname);
    virtual ~Gateway();

    void run();
    void stop();

    void listen(QHostAddress address, ushort port, INetMsgHandler* handler);
    void stopListening(QHostAddress address, ushort port);

    void connectToNetHost(QString netHostname, quint16 port);
    void connectToNetHost(QHostAddress address, quint16 port);
    void disconnectFromNetHost(quint8 reason = LOCAL_DISCONNECT_REQ);



private:
    NetPortalManager* portMan;
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
