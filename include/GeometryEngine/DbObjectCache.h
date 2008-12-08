///////////////////////////////////////////////////////////
//  ResourceCache.h
//  Implementation of the Class DbObjectCache
//  Created on:      04-Dec-2008 8:26:39 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__RESOURCECACHE_H__)
#define __RESOURCECACHE_H__

#include "AbstractResourceSource.h"
#include "AbstractResource.h"

class DbObjectCache : public AbstractDbObjectSource
{

public:
	DbObjectCache();
	virtual ~DbObjectCache();
	DbObject *m_DbObject;

	virtual DbObject& getDbObjectByURL(URL url);
	bool addDbObject(DbObject& ar);
	bool putDbObject(DbObject& res);

private:
	std::set <DbObject&> DbObjectCacheSet;
	std::map <URL, DbObject&> URLDbObjectMap;
	std::map <UUID, DbObject&> UUIDDbObjectMap;
	std::map <DbObject&, AbstractDbObjectSource&> DbObjectOriginMap;

};
#endif // !defined(__RESOURCECACHE_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
