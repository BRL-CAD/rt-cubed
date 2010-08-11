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

PkgClient::PkgClient()
{
  // TODO Auto-generated constructor stub

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
PkgClient::_close()
{
  //call the c function
  pkg_close(this->conn);
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
