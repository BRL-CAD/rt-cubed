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

#include "PortalManager.h"
#include "NetMsgFactory.h"
#include "PkgTcpClient.h"

PortalManager::PortalManager(quint32 port) : ControlledThread("PortalManager")
{
  this->port = port;


  this->tcpServer = new PkgTcpServer();

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

}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// End:
// ex: shiftwidth=4 tabstop=8
