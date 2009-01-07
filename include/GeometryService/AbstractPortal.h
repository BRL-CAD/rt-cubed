/*                      A B S T R A C T P O R T A L . H
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

/** @file AbstractPortal.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_ABSTRACTPORTAL_H_)
#define _ABSTRACTPORTAL_H_

#include <iostream>
#include <list>
#include "iBME/iBMECommon.h"

class AbstractPortal
{

public:
	AbstractPortal();
	virtual ~AbstractPortal();

private:
	uInt connectionType;
	String host;
	std::list <String> proxy_hosts();

};

#endif // !defined(_ABSTRACTPORTAL_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
