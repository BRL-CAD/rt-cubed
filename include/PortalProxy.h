/*                   P O R T A L P R O X Y . H
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
/** @file PortalProxy.h
 * PortalProxy.h
 *
 *  Created on: Sep 28, 2010
 *      Author: dloman
 */

#ifndef __PORTALPROXY_H__
#define __PORTALPROXY_H__

#include "Portal.h"
#include <QtCore/QMutex>

class PortalProxy {
public:
	PortalProxy(Portal* p = 0);
	virtual ~PortalProxy();

	bool hasPortal();
	Portal* getPortal();
	void setPortal(Portal* portal);

private:
	QMutex portalLock;
	Portal* portal;

};

#endif /* __PORTALPROXY_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
