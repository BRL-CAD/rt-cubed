/*                     N E T P O R T A L . H
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
/** @file NetPortal.h
 *
 * Brief description
 *
 */

#ifndef __NETPORTAL_H__
#define __NETPORTAL_H__

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include "GE/Logger.h"
#include "GS/netMsg/NetMsgFactory.h"

class NetPortalManager;

class NetPortal: public QTcpSocket
{
Q_OBJECT

friend class NetPortalManager;

public:
	NetPortal(NetPortalManager* parent);
	virtual ~NetPortal();

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

	NetPortalManager* nspm;

};

#endif


/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
