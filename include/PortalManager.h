/*                 P O R T A L M A N A G E R . H
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
/** @file PortalManager.h
 *
 * Brief description
 *
 */

#ifndef __PORTALMANAGER_H__
#define __PORTALMANAGER_H__

#include "libutility.h"
#include "ControlledThread.h"
#include "PkgTcpServer.h"
#include <sys/select.h>

#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QString>

class Portal;

class PortalManager : public ControlledThread
{
public:
	PortalManager(quint16 port);
	~PortalManager();

	Portal* connectToHost(QString host, quint16 port);
protected:
	void _run();

private:
	Logger* log;
	quint16 port;
	PkgTcpServer* tcpServer;

	QMutex masterFDSLock;
	fd_set masterfds;
	int fdmax;

	QMutex* portalsLock;
	QMap<int, Portal*>* fdPortalMap;

	Portal* makeNewPortal(PkgTcpClient* client);
	void closeFD(int fd, QString logComment);

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
