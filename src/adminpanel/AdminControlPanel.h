/*             A D M I N C O N T R O L P A N E L . H
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
/** @file AdminControlPanel.h
 *
 * All the functionality for the Admin Control Panel app.
 *
 */

#ifndef __ADMINCONTROLPANEL_H__
#define __ADMINCONTROLPANEL_H__

#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QCoreApplication>

#include <iostream>

#include "CommandParser.h"
#include "ICommandable.h"

class AdminControlPanel : public QCoreApplication, public ICommandable
{
  Q_OBJECT

public:
  AdminControlPanel(int& argc, char* argv[]);

  virtual ~AdminControlPanel();

  void connectToHost(const char* hostName, char* port);
  void connectToHost(const QString strHostName, const QString strPort);
  void connectToHost(const QString& hostName, quint16 port);

  int exec();

  void printSplash();

  bool handleCommand(QStringList* cmdStack);

public slots:
  void shutdown();

  void handleSockConnected();
  void handleSockDisconnected();
  void handleSockError(QAbstractSocket::SocketError socketError );
  void handleSockHostFound();
  void handleSockStateChanged(QAbstractSocket::SocketState socketState );

private:
  QTcpSocket* sock;
};

#endif

// Local Variables:
// mode: C++ 
// tab-width: 8
// c-basic-offset: 2
// indent-tabs-mode: t
// End:
// ex: shiftwidth=2 tabstop=8
