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
#include "Logger.h"
#include "brlcad/bu.h"
#include "NetMsgFactory.h"
#include "NetMsgTypes.h"
#include "RemoteGSHostnameSetMsg.h"

Portal::Portal(PkgTcpClient* client)
{
  this->remoteNodeName = "NotSetYet-" + QUuid::createUuid().toString();
  this->pkgClient = client;

  struct pkg_switch table[] = {
      {PKG_MAGIC2, &(Portal::callbackSpringboard), "SpringBoard", this},
      {0,0, (char*)0,0}
  };

  this->pkgClient->setCallBackTable(table);
  this->log = Logger::getInstance();
  this->handshakeComplete = false;
}

Portal::~Portal()
{
}


int
Portal::send(NetMsg* msg){
	QByteArray* ba = msg->serialize();
	int retval = this->pkgClient->send(PKG_MAGIC2, ba->data(), ba->size());
	delete ba;
	return retval;
}
void
Portal::sendGSNodeName()
{
	QString localNodeName = Config::getInstance()->getConfigValue("LocalGSNodeName");
	if (localNodeName.length() == 0) {
		localNodeName = QUuid::createUuid().toString();
	}

	RemoteGSHostnameSetMsg* msg = new RemoteGSHostnameSetMsg(localNodeName);
	this->send(msg);
}

int
Portal::read(){

  int retval = 0;

  //recv first
  retval = this->pkgClient->processData();
  if (retval < 0){
	  this->log->logERROR("Portal", "Unable to process packets? Weird.\n");
      return retval;
  }//TODO do we need to check for ==0 ?


  retval = this->pkgClient->pullDataFromSocket();
  if (retval < 0) {
	  this->log->logERROR("Portal", "Seemed to have trouble pulling the data from the socket.\n");
    return retval;

  } else if (retval == 0) {
	  this->log->logERROR("Portal", "Client closed the connection.\n");
    return retval;
  }

  retval = this->pkgClient->processData();
  if (retval < 0){
	  this->log->logERROR("Portal", "Unable to process packets? Weird.\n");
      return retval;
  }//TODO do we need to check for ==0 ?

  return 1;
}

QString
Portal::getRemoteNodeName(){
  return this->remoteNodeName + "";
}

bool
Portal::handleNetMsg(NetMsg* msg)
{
	quint16 type = msg->getMsgType();

	if (type == REMGSHOSTNAMESET) {
		RemoteGSHostnameSetMsg* t = (RemoteGSHostnameSetMsg*)msg;
		this->remoteNodeName = t->getRemoteGSHostname();
		this->handshakeComplete = true;
		delete msg;
		return true;
	}

	return false;
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

  //TODO Split the code here?  Fire off a Job?


  /* Build a NetMsg */
  NetMsg* msg  = NetMsgFactory::getInstance()->deserializeNetMsg(ba, p);

  /* check to see if we deserialized the msg properly */
  if (msg == 0) {
    bu_log("WARNING!  NetMsg failed to deserialize properly.\n");
    return;
  }

  /* Route */

  //give the Portal first dibs on the netmsg
  if (p->handleNetMsg(msg)){
	  return;
  }

  //TODO add in routing code.
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
