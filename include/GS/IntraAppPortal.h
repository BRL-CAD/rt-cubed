/*                 I N T R A A P P P O R T A L . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
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

/** @file IntraAppPortal.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_INTRAAPPPORTAL_H_)
#define _INTRAAPPPORTAL_H_

#include "GS/AbstractPortal.h"

class IntraAppPortal : public AbstractPortal
{

public:
	IntraAppPortal();
	virtual ~IntraAppPortal();

};

#endif // !defined(_INTRAAPPPORTAL_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
