/*                  P O R T A L . C X X
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
/** @file Portal.cxx
 *
 * Brief description
 *
 */

#include "Portal.h"
#include "brlcad/bu.h"
#include "NetMsgFactory.h"

Portal::Portal(PkgTcpClient* client)
{
  this->remoteNodeName = "NotSetYet-" + QUuid::createUuid().toString();
  this->pkgClient = client;

  struct pkg_switch table[] = {
      {PKG_MAGIC2, &(Portal::callbackSpringboard), "SpringBoard", this},
      {0,0, (char*)0,0}
  };

  this->pkgClient->setCallBackTable(table);
}

Portal::~Portal()
{
}

QString
Portal::getRemoteNodeName(){
  return this->remoteNodeName + "";
}

void
Portal::callbackSpringboard(struct pkg_conn* conn, char* buf)
{
  /* Check to see if we got a good Buffer and Portal Object */
  if (buf == 0) {
    bu_bomb("pkg callback returned a NULL buffer!\n");
  }

  QByteArray ba(buf);

  if (conn->pkc_user_data == 0) {
     bu_bomb("pkg callback returned a NULL user_data pointer!\n");
   }
  Portal* p = (Portal*)conn->pkc_user_data;

  /* Construct String */
  QString origin(p->getRemoteNodeName());

  /* Build a NetMsg */
  NetMsg* msg  = NetMsgFactory::getInstance()->deserializeNetMsg(ba, origin);

  /* check to see if we deserialized the msg properly */
  if (msg == 0) {
    bu_log("WARNING!  NetMsg failed to deserialize properly.\n");
  }

  /* Route */
  //TODO add in routing code.
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
