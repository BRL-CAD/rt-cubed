///////////////////////////////////////////////////////////
//  ResourceCache.h
//  Implementation of the Class DbObjectCache
//  Created on:      04-Dec-2008 8:26:39 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_1945575A_81CE_4e89_BD04_97CBAB90EE3B__INCLUDED_)
#define EA_1945575A_81CE_4e89_BD04_97CBAB90EE3B__INCLUDED_

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
	std::map <DbObject&. AbstractDbObjectSource&> DbObjectOriginMap;

};
#endif // !defined(EA_1945575A_81CE_4e89_BD04_97CBAB90EE3B__INCLUDED_)
