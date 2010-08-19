/*                  P K G S E R V E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2004-2010 United States Government as represented by
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
/** @file PkgServer.cxx
 *
 *
 */

#include "PkgServer.h"
#include "brlcad/bu.h"
#include "brlcad/pkg.h"
#include <stdio.h>
#include <unistd.h>

PkgServer::PkgServer(std::string proto, struct pkg_switch* callBackTableIn)
{
  this->proto = proto;
  this->callBackTable = callBackTableIn;
}

PkgServer::~PkgServer()
{
}

bool
PkgServer::listen(unsigned short port)
{
  //Convert port -> char* to make libpkg happy.
  char portCString[7] = { 0 };
  int fd;
  snprintf(portCString, 6, "%d", port);

  fd = pkg_permserver(portCString, this->proto.c_str(), 0, 0);

  if (fd < 0)
    return false;

  this->listenFD = fd;

  bu_log("Listening on port '%d'.\n", port);

  return true;
}

PkgClient*
PkgServer::waitForClient()
{
  pkg_conn* clientStruct = pkg_getclient(this->listenFD, this->callBackTable,
      NULL, 0);
  if (clientStruct == PKC_NULL)
    {
      bu_log("Connection seems to be busy, waiting...\n");
      sleep(1);
      return NULL;
    }
  else if (clientStruct == PKC_ERROR)
    {
      //Fatal error accepting client connection
      bu_log("Fatal error accepting client connection.\n");
      pkg_close(clientStruct);
      return NULL;
    }

  PkgClient* pkgClientObj = this->getNewClient(clientStruct);
  return pkgClientObj;
}


/*
 * Local Variables:
 * mode: C
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
