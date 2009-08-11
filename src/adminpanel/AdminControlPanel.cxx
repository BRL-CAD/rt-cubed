/*           A D M I N C O N T R O L P A N E L . C X X
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
/** @file AdminControlPanel.cxx
 *
 * Brief description
 *
 */

#include "AdminControlPanel.h"
#include <QHostAddress>


AdminControlPanel::AdminControlPanel(int& argc, char* argv[]) : QCoreApplication(argc, argv)
{
  this->sock = new QTcpSocket();
}

AdminControlPanel::~AdminControlPanel()
{
  this->sock->disconnectFromHost();
  delete this->sock;
}

int AdminControlPanel::exec() 
{
  CommandParser cp((ICommandable*)this); //I shouldn't have to cast this... what's going on?!?

  QObject::connect(&cp, SIGNAL(finished()), this, SLOT(shutdown()) );
  QObject::connect(&cp, SIGNAL(terminated()), this, SLOT(shutdown()) );

  cp.start();

  int retVal = QCoreApplication::exec();

  QObject::disconnect(&cp, SIGNAL(finished()), this, SLOT(shutdown()) );
  QObject::disconnect(&cp, SIGNAL(terminated()), this, SLOT(shutdown()) );

  return retVal;
}


bool AdminControlPanel::handleCommand(QStringList* cmdStack)
{
  bool retVal = true;
  QString cmd = cmdStack->first();
  QString cmdl = cmd.toLower();


  if (cmdl == "connect" || cmdl == "connectto" || cmdl == "con") {
    if (cmdStack->size() != 3) {
      std::cout << "\tUsage:  connect HostName|IP port" << std::endl;
      retVal = false;
    } else {
      this->connectToHost(cmdStack->at(1),  cmdStack->at(2));
    }

  } else if (cmdl == "disconnect" || cmdl == "dis") {
    if (cmdStack->size() != 1) {
      std::cout << "\tUsage:  disconnect (No arguments)" << std::endl;
      retVal = false;
    } else {
      this->sock->disconnectFromHost();
    }


  } else {
    std::cout << "\tUnknown Command: " << cmd.toStdString() << std::endl;
    retVal = false;
  }

  delete cmdStack;
  return retVal;
}

void AdminControlPanel::printSplash()
{
  std::cout << "\n";
  std::cout << "****************************************" << "\n";
  std::cout << "****************************************" << "\n";
  std::cout << "**   GeometryService Administration   **" << "\n";
  std::cout << "**        Control Panel  v 0.1        **" << "\n";
  std::cout << "****************************************" << "\n";
  std::cout << "****************************************" << "\n";
  std::cout << "\n";
}

void AdminControlPanel::shutdown()
{
  std::cout << "\tShutting down...\n" << std::endl;

  this->quit();
}

/*
 * Sock Delegates
 */


void AdminControlPanel::connectToHost(const char* hostName, char* strPort)
{
  QString qstrHostName(hostName);
  QString qstrPort(strPort);

  this->connectToHost(qstrHostName, qstrPort);
}

void AdminControlPanel::connectToHost(const QString strHostName, const QString strPort)
{
  quint16 port = strPort.toUShort(); 
  this->connectToHost(strHostName, port);
}

void AdminControlPanel::connectToHost(const QString& hostName, quint16 port)
{
  std::cout << "\tACP is attempting to connect to: " << hostName.toStdString(); 
  std::cout << ":" << port << std::endl;

  this->sock->connectToHost(hostName, port);
}


void AdminControlPanel::handleSockConnected ()
{
  std::cout << "\tACP has connected to: " << this->sock->peerAddress().toString().toStdString(); 
  std::cout << ":" << this->sock->peerPort() << "\n";
}

void AdminControlPanel::handleSockDisconnected ()
{
  std::cout << "\tACP has been disconnected from server.\n";
}

void AdminControlPanel::handleSockError ( QAbstractSocket::SocketError socketError )
{
  std::cout << "\tRecieved a SocketError with a value of: " << socketError << "\n";
  std::cout << "\t\tLookup value at: http://qt.nokia.com/doc/4.5/qabstractsocket.html#SocketError-enum\n";
}

void AdminControlPanel::handleSockHostFound ()
{
  std::cout << "\tHost lookup succeeded.\n";
}

void AdminControlPanel::handleSockStateChanged ( QAbstractSocket::SocketState socketState )
{
  std::cout << "\tDetected a SocketState Change. New value: " << socketState << "\n";
  std::cout << "\t\tLookup value at: http://qt.nokia.com/doc/4.5/qabstractsocket.html#SocketState-enum\n";
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
