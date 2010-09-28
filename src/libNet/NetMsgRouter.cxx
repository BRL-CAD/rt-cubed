/*                N E T M S G R O U T E R . C X X
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
/** @file NetMsgRouter.cxx
 *
 * Brief description
 *
 */

#include "NetMsgRouter.h"
#include <QtCore/QMutexLocker>

NetMsgRouter* NetMsgRouter::pInstance = NULL;

NetMsgRouter*
NetMsgRouter::getInstance() {
	if (NetMsgRouter::pInstance == NULL) {
		NetMsgRouter::pInstance = new NetMsgRouter();
	}
	return NetMsgRouter::pInstance;
}

NetMsgRouter::NetMsgRouter() {
	this->routingTable = new QMap<quint16, QList<INetMsgHandler*>*> ();
}

NetMsgRouter::~NetMsgRouter() {
	delete routingTable;
}

bool NetMsgRouter::registerType(quint16 type, INetMsgHandler* handler) {
	//First get the appropriate list:
	QList<INetMsgHandler*>* list = this->getListOfHandlers(type);
	list->append(handler);

	return true;
}

bool NetMsgRouter::routeMsg(NetMsg* msg) {
	//First get the appropriate list:
	QList<INetMsgHandler*>* list = this->getListOfHandlers(msg->getMsgType());

	for (int i = 0; i < list->length(); ++i) {
		list->at(i)->handleNetMsg(msg);
	}

	//Now delete msg
	delete msg;
}

QList<INetMsgHandler*>*
NetMsgRouter::getListOfHandlers(quint16 type) {
	QMutexLocker(&this->mapLock);

	QList<INetMsgHandler*>* l = this->routingTable->value(type);

	if (l == 0) {
		l = new QList<INetMsgHandler*> ();
		this->routingTable->insert(type, l);
	}
	return l;
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
