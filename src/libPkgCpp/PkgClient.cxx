/*                    P K G C L I E N T . C X X
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
/** @file PkgClient.cxx
 *
 *
 */
#include "PkgClient.h"
#include "brlcad/bu.h"
#include <string.h>

//TODO Need a path for a callback table to get to this
PkgClient::PkgClient(std::string ipOrHostname, int port)
{
  char portCString[7] = { 0 };
  snprintf(portCString, 6, "%d", port);

  //TODO Make this more robust.  TCP being hardcoded is bad.
  this->conn = pkg_open(ipOrHostname.c_str(), portCString, "tcp", NULL, NULL, NULL, NULL);
}

PkgClient::PkgClient(pkg_conn* conn)
{
  this->conn = conn;
}

PkgClient::~PkgClient()
{
  if (this->conn != NULL)
    {
      this->close();
      delete this->conn;
    }
}

bool
PkgClient::hasGoodConnection()
{
  return (this->conn != PKC_ERROR);
}

int
PkgClient::send(int opcode, const char* buffer, size_t bufferLen)
{
  //call the c function
  return pkg_send(opcode, buffer, bufferLen, this->conn);
}

void
PkgClient::close()
{
  //call the c function
  pkg_close(this->conn);
}

char*
PkgClient::waitForMsg(int opcode)
{
  char* buffer = pkg_bwaitfor(opcode, this->conn);
  if (buffer == NULL)
    {
      bu_log("Failed to process the client connection, still waiting\n");
      pkg_close(this->conn);
      this->conn = PKC_NULL;
    }

  return buffer;
}

int
PkgClient::processData()
{
  return pkg_process(this->conn);
}

int
PkgClient::pullDataFromSocket()
{
  return pkg_suckin(this->conn);
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
