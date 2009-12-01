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

class NetSockPortal: public QTcpSocket
{
	Q_OBJECT

	friend class NetSockPortalManager;

public:
	NetSockPortal(QObject* parent = 0);
	virtual ~NetSockPortal();

	enum
	{
		Handshaking_HostNameLen = 2,
		Handshaking_HostName = 4,
		Handshaking_VersionLen = 6,
		Handshaking_Version = 8,
		Ready = 10,
		Failed = 12,
	};

private:
	quint32 remHostNameLen;
	QString remHostName;
	quint32 remVersionLen;
	QString remVersion;

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
