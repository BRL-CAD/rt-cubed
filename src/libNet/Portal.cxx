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


int
Portal::readWrite(){

}

int
Portal::write(){

}

int
Portal::read(){

  int retval = 0;

  //recv first
  retval = this->pkgClient->processData();
  if (retval < 0){
      bu_log("Unable to process packets? Weird.\n");
      return retval;
  }//TODO do we need to check for ==0 ?


  retval = this->pkgClient->pullDataFromSocket();
  if (retval < 0) {
    bu_log("Seemed to have trouble pulling the data from the socket.\n");
    return retval;

  } else if (retval == 0) {
    bu_log("Client closed the connection.\n");
    return retval;
  }

  retval = this->pkgClient->processData();
  if (retval < 0){
      bu_log("Unable to process packets? Weird.\n");
      return retval;
  }//TODO do we need to check for ==0 ?

  return 1;
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
    return;
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
