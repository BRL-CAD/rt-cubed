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
#include "RemoteNodenameSetMsg.h"
#include "TypeOnlyMsg.h"

Portal::Portal(PkgTcpClient* client, struct pkg_switch* table) {
	this->remoteNodeName = "NotSetYet-" + QUuid::createUuid().toString();
	this->pkgClient = client;
	this->callbackTable = table;
	//set the struct's userdata
	this->callbackTable[0].pks_user_data = this;

	this->log = Logger::getInstance();
	this->handshakeComplete = false;
}

Portal::~Portal() {
	delete callbackTable;
}

int Portal::send(NetMsg* msg) {
	QByteArray* ba = msg->serialize();

	QString s("Sending msg.  Type: ");
	s.append(QString::number(msg->getMsgType()));
	s.append(" len: ");
	s.append(QString::number(ba->size()));
	log->logDEBUG("Portal", s);

	int retval = this->pkgClient->send(PKG_MAGIC2, ba->data(), ba->size());

	s = "Sent ";
	s.append(QString::number(retval));
	s.append(" bytes.");
	log->logDEBUG("Portal", s);

	delete ba;
	return retval;
}
void Portal::sendGSNodeName() {
	QString localNodeName = Config::getInstance()->getConfigValue(
			"LocalGSNodeName");
	if (localNodeName.length() == 0) {
		localNodeName = QUuid::createUuid().toString();
	}

	QString s("Sending my localNodename: ");
	s.append(localNodeName);
	this->log->logDEBUG("Portal", s);

	RemoteNodenameSetMsg* msg = new RemoteNodenameSetMsg(localNodeName);
	this->send(msg);
}

int Portal::flush() {
	return this->pkgClient->flush();
}
int Portal::read() {
	int retval = 0;

	/*
	 const pkg_switch* table = this->pkgClient->getCallBackTable();
	 pkg_switch sw = table[0];
	 bu_log("P(1.1): Route[0] type: %d\n", sw.pks_type);
	 bu_log("P(1.1): Route[0] callback: %d\n", sw.pks_handler);
	 bu_log("P(1.1): Route[0] user_data: %d\n", sw.pks_user_data);
	 */

	//recv first
	retval = this->pkgClient->processData();
	if (retval < 0) {
		this->log->logERROR("Portal",
				"Unable to process packets? Weird. (1) ");
		return retval;
	}//TODO do we need to check for ==0 ?


	retval = this->pkgClient->pullDataFromSocket();
	if (retval < 0) {
		this->log->logERROR("Portal",
				"Seemed to have trouble pulling the data from the socket.");
		return retval;

	} else if (retval == 0) {
		this->log->logERROR("Portal", "Client closed the connection.");
		return retval;
	}

	retval = this->pkgClient->processData();
	if (retval < 0) {
		this->log->logERROR("Portal", "Unable to process packets? Weird. (2)");
		return retval;
	}//TODO do we need to check for ==0 ?

	return 1;
}

QString Portal::getRemoteNodeName() {
	return this->remoteNodeName + "";
}

bool Portal::handleNetMsg(NetMsg* msg) {
	quint16 type = msg->getMsgType();

	if (type == GS_REMOTE_NODENAME_SET) {
		if (this->handshakeComplete) {
			this->log->logDEBUG("Portal",
					"Recv-ed a RemoteNodename, but that is already set!");
		} else {
			RemoteNodenameSetMsg* t = (RemoteNodenameSetMsg*) msg;
			this->remoteNodeName = t->getRemoteNodename();
			this->handshakeComplete = true;

			QString s("Recv-ed a RemoteNodename: ");
			s.append(this->remoteNodeName);
			this->log->logDEBUG("Portal", s);

			//reply
			//this->sendGSNodeName();
		}
		delete msg;
		return true;
	} else if (type == RUALIVE) {
		TypeOnlyMsg tom(IMALIVE);
		this->send(&tom);
		delete msg;
		return true;
	}

	return false;
}

void Portal::callbackSpringboard(struct pkg_conn* conn, char* buf) {
	/* Check to see if we got a good Buffer and Portal Object */
	if (buf == 0) {
		bu_bomb("pkg callback returned a NULL buffer!\n");
	}

	int len = conn->pkc_inend - sizeof(pkg_header);

	QByteArray ba(buf, len);


	if (conn->pkc_user_data == 0) {
		bu_log("pkg callback returned a NULL user_data pointer!\n");

	}

	Portal* p = (Portal*) conn->pkc_user_data;

	if (p == 0) {
		bu_log("WARNING!  NULL Portal.\n");
	}

	//TODO Split the code here?  Fire off a Job?


	/* Build a NetMsg */
	NetMsg* msg = NetMsgFactory::getInstance()->deserializeNetMsg(ba, p);

	/* check to see if we deserialized the msg properly */
	if (msg == 0) {
		bu_log("WARNING!  NetMsg failed to deserialize properly.\n");
		return;
	}

	/* Route */

	//give the Portal first dibs on the netmsg
	if (p->handleNetMsg(msg)) {
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
