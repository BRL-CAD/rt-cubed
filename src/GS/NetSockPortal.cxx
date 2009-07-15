/*               N E T S O C K P O R T A L . C X X
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
/** @file NetSockPortal.cxx
 *
 * Brief description
 *
 */

#include "GS/NetSockPortal.h"

NetSockPortal::NetSockPortal(QTcpSocket* socket)
{
  this->sock = socket;
    QObject::connect(sock, SIGNAL( connected() ), this, SLOT( handleConnect() ));
    QObject::connect(sock, SIGNAL( disconnected() ), this, SLOT( handleDisconnect() ));
    QObject::connect(sock, SIGNAL( readRead() ), this, SLOT( handleReadyRead() ));


}



NetSockPortal::~NetSockPortal()
{
  //QUESTION:  Do we really want to destroy the socket here?
  delete this->sock;
}


void NetSockPortal::handleReadyRead()
{

}
void NetSockPortal::handleConnected()
{

}
void NetSockPortal::handleDisconnected()
{

}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
