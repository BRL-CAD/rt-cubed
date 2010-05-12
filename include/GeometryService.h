/*               G E O M E T R Y S E R V I C E . H
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
/** @file GeometryService.h
 *
 * Brief description
 *
 */

#ifndef __GEOMETRYSERVICE_H__
#define __GEOMETRYSERVICE_H__

#include "libnetwork.h"
#include "libutility.h"

#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QCoreApplication>

class GeometryService : public INetMsgHandler
{

public:
	GeometryService(const QString localGSHostname);
	virtual ~GeometryService();
	void startListening(const QHostAddress& addy, quint16 port);
	void stopListening();
	bool isListening() const;

private:
	Logger* log;
	QString localGSHostname;
	NetPortalManager* portalMan;

	void handleNetMsg(NetMsg* msg, NetPortal* origin);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
