/*               G E O M E T R Y S E R V I C E . H
 * BRL-CAD
 *
 * Copyright (c) 2011 United States Government as represented by
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

#include "libutility.h"
#include "libnet.h"
#include "DataManager.h"

#include <QtCore/QString>
#include <QtNetwork/QHostAddress>

static const quint16 DEFAULT_LISTEN_PORT = 5309;
static const QHostAddress DEFAULT_LISTEN_ADDY = QHostAddress::LocalHost;

class GeometryService : public ControlledThread, public INetMsgHandler
{
public:
	GeometryService(const QString localNodeName, const quint16 listenPort = DEFAULT_LISTEN_PORT, const QHostAddress listenAddy = DEFAULT_LISTEN_ADDY);
	virtual ~GeometryService();
    bool handleNetMsg(NetMsg* msg);
    DataManager* getDataManager();

protected:
	bool preRunHook();
	void _run();
	bool postRunHook();

private:
	Logger* log;
	QString localNodeName;
	quint16 listenPort;
	QHostAddress listenAddy;

	PortalManager* portalMan;
	DataManager* dataMan;

	void registerMsgRoutes();

	/* Disable copy cstr and =operator */
	GeometryService(GeometryService const&){};
	GeometryService& operator=(GeometryService const&){};
};

#endif /* __GEOMETRYSERVICE_H__ */

/*
 * Local Variables: ***
 * mode: C++ ***
 * tab-width: 8 ***
 * c-basic-offset: 2 ***
 * indent-tabs-mode: t ***
 * End: ***
 * ex: shiftwidth=2 tabstop=8
*/
