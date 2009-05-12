/*                 S O U R C E D I S K L I N K . H
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

/** @file SourceDiskLink.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_SOURCEDISKLINK_H_)
#define _SOURCEDISKLINK_H_

#include "iBME/iBMECommon.h"
#include "GE/SourceDiskLink.h"
#include "GE/AbstractDbObjectSource.h"
#include <string>


class SourceDiskLink : public AbstractDbObjectSource
{

public:
	SourceDiskLink();
	virtual ~SourceDiskLink();

	virtual std::string getDbObjectByURL(std::string url);
	bool putDbObject(std::string dbobj);

};

#endif // !defined(_SOURCEDISKLINK_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
