///////////////////////////////////////////////////////////
//  DBOBJECTCache.h
//  Implementation of the Class DbObjectCache
//  Created on:      04-Dec-2008 8:26:39 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__DBOBJECTCACHE_H__)
#define __DBOBJECTCACHE_H__

#include <set>
#include <map>

#include "iBMECommon.h"
#include "AbstractDbObjectSource.h"
#include "DbObject.h"

class DbObjectCache : public AbstractDbObjectSource
{

public:
	DbObjectCache();
	virtual ~DbObjectCache();

	virtual DbObject& getDbObjectByURL(URL& url);
	bool addDbObject(DbObject& dbo);
	bool putDbObject(DbObject& dbo);

private:
	set <DbObject> dbObjectCacheSet;
	map <URL, DbObject> urlDbObjectMap;
	map <UUID, DbObject> uuidDbObjectMap;
	map <DbObject, AbstractDbObjectSource> dbObjectOriginMap;

};
#endif // !defined(__DBOBJECTCACHE_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
