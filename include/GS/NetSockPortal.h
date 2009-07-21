/*                 N E T S O C K P O R T A L . H
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
/** @file NetSockPortal.h
 *
 * Brief description
 *
 */

#ifndef __NETSOCKPORTAL_H__
#define __NETSOCKPORTAL_H__

#include "GS/AbstractPortal.h"
#include <QTcpSocket>
#include <QString>

class NetSockPortal : public AbstractPortal
{

  Q_OBJECT

public:
  NetSockPortal(QTcpSocket* socket);
  virtual ~NetSockPortal();

   enum PortalStatus
   {
      Handshaking,
      Ready,
      Failed,
   };


private slots:
  void handleReadyRead();
  void handleConnected();
  void handleDisconnected();

private:
  QString remoteHostName;
  QTcpSocket* sock;

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
