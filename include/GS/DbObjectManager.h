/*               D B O B J E C T M A N A G E R . H
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
/** @file DbObjectManager.h
 *
 * Brief description
 *
 */

#ifndef __DBOBJECTMANAGER_H__
#define __DBOBJECTMANAGER_H__

#include "GS/GSCommon.h"
#include <string>
#include <list>
#include <QUuid>

class DbObjectManager {

public:
	DbObjectManager();
	virtual ~DbObjectManager();

	std::string getDbObjectByURL(std::string url);
	std::string getDbObjectByUUID(QUuid& uuid);

private:

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
