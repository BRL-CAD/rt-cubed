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
#include <stdlib.h>
#include <sstream>

PkgServer::PkgServer(std::string proto)
{
  this->proto = proto;
  this->listenFD = -1;
}

PkgServer::~PkgServer()
{}

/**
 * Attempts to open a new connection to ipOrHostname:port.  Returns NULL if connection fails for any reason.
 */
PkgClient*
PkgServer::connectToHost(std::string ipOrHostname, short port)
{
	std::stringstream ss;
	ss << port;
	std::string s_port = ss.str();

	pkg_conn* conn = pkg_open(ipOrHostname.c_str(), s_port.c_str(), this->proto.c_str(), NULL, NULL, NULL, NULL);

	if (conn == PKC_ERROR) {
		bu_log("Connection to %s, port %d, failed.\n", ipOrHostname.c_str(), port);
		return NULL;
	}
	return this->getNewClient(conn);
}

int
PkgServer::listen(unsigned short port)
{
  //Convert port -> char* to make libpkg happy.
  char portCString[7] = { 0 };
  int fd;
  snprintf(portCString, 6, "%d", port);

  fd = pkg_permserver(portCString, this->proto.c_str(), 0, 0);

  if (fd < 0)
    return fd;

  this->listenFD = fd;

  bu_log("Listening on port '%d'.\n", port);

  return fd;
}
int
PkgServer::getListeningFD()
{
  return this->listenFD;
}

PkgClient*
PkgServer::waitForClient(int waitTime) {
	pkg_conn* clientStruct = pkg_getclient(this->listenFD, NULL, NULL, waitTime);
  if (clientStruct == PKC_NULL)
    {
      if (waitTime == 0)
        {
          bu_log("Connection seems to be busy, waiting...\n");
          usleep(100);
        }
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
