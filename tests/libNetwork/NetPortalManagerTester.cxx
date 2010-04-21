/*        N E T P O R T A L M A N A G E R T E S T E R . C X X
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
/** @file NetPortalManagerTester.cxx
 *
 * Brief description
 *
 */

#include "NetPortalManagerTester.h"

NetPortalManagerTester::NetPortalManagerTester(NetPortalManager* portMan)
{
    this->log = Logger::getInstance();
    this->portMan = portMan;
}

NetPortal* NetPortalManagerTester::getNewPortal()
{
    NetPortal* pPortal = this->portMan->getNewPortal();

    QObject::connect(pPortal, SIGNAL(msgReady()), this, SLOT(handleMsgReady()));
    QObject::connect(pPortal, SIGNAL(handshakeStatusUpdate(quint32, quint32)),
	    this, SLOT(handleHandshakeStatusUpdate(quint32, quint32)));
    QObject::connect(pPortal, SIGNAL(portalHandshakeComplete(NetPortal*)), this, SLOT(
		    handleHandshakeComplete(NetPortal* )));

    QObject::connect(pPortal, SIGNAL(portalConnected()), this, SLOT(
	    handlePortalConnected()));
    QObject::connect(pPortal, SIGNAL(portalDisconnected()), this, SLOT(
	    handlePortalDisonnected()));
    QObject::connect(pPortal,
	    SIGNAL(socketError(QAbstractSocket::SocketError)), this, SLOT(
		    handleSocketError(QAbstractSocket::SocketError)));

    return pPortal;
}

void NetPortalManagerTester::handleMsgReady()
{
    this->portMan->localLog("handleMsgReady");
}
void NetPortalManagerTester::handleHandshakeStatusUpdate(quint32 current,
	quint32 old)
{
    this->portMan->localLog("Handshake status update: " + QString::number(old)
	    + "->" + QString::number(current));

}
void NetPortalManagerTester::handleHandshakeComplete(NetPortal* portal)
{
    this->portMan->localLog("handleHandshakeComplete");
}

void NetPortalManagerTester::handlePortalConnected()
{
    this->portMan->localLog("handlePortalConnected");
}
void NetPortalManagerTester::handlePortalDisonnected()
{
    this->portMan->localLog("handlePortalDisonnected");
}
void NetPortalManagerTester::handleSocketError(QAbstractSocket::SocketError err)
{
    this->portMan->localLog("handleSocketError: " + QString::number(err));
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
