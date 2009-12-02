/*                 N E T S O C K P O R T A L . H
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file NetSockPortal.h
 *
 * Brief description
 *
 */

#ifndef __NETSOCKPORTAL_H__
#define __NETSOCKPORTAL_H__

#include <QTcpSocket>
#include <QString>

#include "GE/Logger.h"
#include "GS/netMsg/NetMsgFactory.h"

class NetSockPortal: public QTcpSocket
{
	Q_OBJECT

	friend class NetSockPortalManager;

public:
	NetSockPortal(QObject* parent = 0);
	virtual ~NetSockPortal();

	bool hasMsg();
	NetMsg* getNextMsg();
	void disconnect(quint8 reason);

	void send(NetMsg& msg);

	QString getRemoteHostName();

	enum
	{
		NotConnected = 0, Handshaking = 5, Ready = 10, Failed = 15,
	};

signals:
	void msgReady();
	void portalHandshakeComplete();

protected slots:
	void moveDataFromSocketBuffer();

private:
	QString remHostName;
	Logger* log;

	NetMsgFactory* factory;

	int portStatus;

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
