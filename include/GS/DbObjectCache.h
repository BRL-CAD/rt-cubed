/*                 D B O B J E C T C A C H E . H
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

/** @file DbObjectCache.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#if !defined(_DBOBJECTCACHE_H_)
#define _DBOBJECTCACHE_H_

#include <set>
#include <map>
#include <string>

#include "iBME/iBMECommon.h"
#include "GS/AbstractDbObjectSource.h"

class DbObjectCache : public AbstractDbObjectSource
{

public:
	DbObjectCache();
	virtual ~DbObjectCache();

  virtual std::string getDbObjectByURL(std::string url);
  bool addDbObject(std::string dbo);
  bool putDbObject(std::string dbo);

private:
  std::set <std::string> dbObjectCacheSet;
  std::map <std::string, std::string> urlDbObjectMap;
	std::map <UUID, std::string> uuidDbObjectMap;
	std::map <std::string, AbstractDbObjectSource> dbObjectOriginMap;

};

#endif // !defined(_DBOBJECTCACHE_H_)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
