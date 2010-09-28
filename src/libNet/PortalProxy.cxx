/*                 P O R T A L P R O X Y . C X X
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
/** @file PortalProxy.cxx
 * PortalProxy.cxx
 *
 *  Created on: Sep 28, 2010
 *      Author: dloman
 */

#include "PortalProxy.h"
#include <QtCore/QMutexLocker>

PortalProxy::PortalProxy(Portal* p) {
	this->portal = p;
}

PortalProxy::~PortalProxy() {
}
bool PortalProxy::hasPortal() {
	return (this->getPortal() != 0);
}

Portal* PortalProxy::getPortal() {
	QMutexLocker(&this->portalLock);
	return this->portal;
}
void PortalProxy::setPortal(Portal* p) {
	QMutexLocker(&this->portalLock);
	this->portal = p;

}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
