/*                        P O R T A L . H
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
/** @file Portal.h
 *
 * Brief description
 *
 */

#ifndef __PORTAL_H__
#define __PORTAL_H__

#define PKG_MAGIC2      5309

#include "PkgTcpClient.h"
#include "NetMsg.h"
#include "brlcad/pkg.h"

#include <QtCore/QString>

class Portal
{
public:
  friend class PortalManager;
  virtual ~Portal();
  int send(NetMsg* msg);

  QString getRemoteNodeName();

protected:
  Portal(PkgTcpClient* client);

   /*
      * Returns:
      *          <0 on error
      *          0 on EOF
      *          1 on success
      */
   int read();


private:
  PkgTcpClient* pkgClient;
  QString remoteNodeName;

  static void callbackSpringboard(struct pkg_conn* conn, char* buf);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
