/*           P O R T A L M A N A G E R . C X X
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
/** @file PortalManager.cxx
 *
 * Brief description
 *
 */

#include "Portal.h"
#include "PortalManager.h"
#include "NetMsgFactory.h"
#include "PkgTcpClient.h"

PortalManager::PortalManager(quint32 port) : ControlledThread("PortalManager")
{
  this->port = port;
  this->tcpServer = new PkgTcpServer();
  this->portals = new QList<Portal*>();
  this->portalsLock = new QMutex();
}

PortalManager::~PortalManager()
{
}

void
ControlledThread::_run()
{

  while (this->runCmd)
    {
      this->_runLoopPass();
    }
}

void
PortalManager::_runLoopPass()
{
  PkgTcpClient* client = (PkgTcpClient*) this->tcpServer->waitForClient(123);

  if (client != 0) {
    //Handle new client here.
    Portal* newPortal = new Portal(client);
    this->portalsLock->lock();
    this->portals->append(newPortal);
    this->portalsLock->unlock();
  }

  //regardless of new client or not, process existing portals
  QMutexLocker locker(this->portalsLock);

  for (int i = 0; i < this->portals->size(); ++i) {
    Portal* p = this->portals->at(i);

    int retval = p->sendRecv();

    if (retval <= 0) {
      //disconnect this portal
      continue;
    }

  }
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// ex: shiftwidth=4 tabstop=8
