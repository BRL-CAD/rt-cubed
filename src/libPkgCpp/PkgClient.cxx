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


PkgClient::PkgClient()
{
  this->conn = PKC_NULL;
}

PkgClient::PkgClient(pkg_conn* conn)
{
  this->conn = conn;
}

PkgClient::~PkgClient()
{
  if (this->conn != NULL)
    {
      this->_close();
      delete this->conn;
    }
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
  else
    {
      /* validate magic header that client should have sent */
      if (strcmp(buffer, PKG_HEADER_MAGIC) != 0)
        {
          bu_log(
              "Bizarre corruption, received a MSG without at matching PKG_HEADER_MAGIC!\n");
          pkg_close(this->conn);
          this->conn = PKC_NULL;
        }
    }
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
