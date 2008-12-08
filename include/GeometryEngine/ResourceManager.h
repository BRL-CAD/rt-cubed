///////////////////////////////////////////////////////////
//  ResourceManager.h
//  Implementation of the Class DbObjectManager
//  Created on:      04-Dec-2008 8:26:40 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__RESOURCEMANAGER_H__)
#define __RESOURCEMANAGER_H__

#include "AbstractResourceSource.h"

class DbObjectManager {

public:
	DbObjectManager();
	virtual ~DbObjectManager();
	AbstractDbObjectSource *m_AbstractDbObjectSource;

	DbObject& getDbObjectByURL(URL url);
	DbObject& getDbObjectByUUID(UUID uuid);

private:
	std::list <AbstractDbObjectSource&> DbObjectSources;

};
#endif // !defined(__RESOURCEMANAGER_H__)
// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
