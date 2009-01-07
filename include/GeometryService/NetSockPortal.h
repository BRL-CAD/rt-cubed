/*                 N E T S O C K P O R T A L . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2008 United States Government as represented by
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
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(__NETSOCKPORTAL_H__)
#define __NETSOCKPORTAL_H__

#include "GeometryService/AbstractPortal.h"

class NetSockPortal : public AbstractPortal
{

public:
	NetSockPortal();
	virtual ~NetSockPortal();

};

#endif // !defined(__NETSOCKPORTAL_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
