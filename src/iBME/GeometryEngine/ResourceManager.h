///////////////////////////////////////////////////////////
//  ResourceManager.h
//  Implementation of the Class DbObjectManager
//  Created on:      04-Dec-2008 8:26:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_DB729CE6_B0CD_4141_A603_18DD152317A3__INCLUDED_)
#define EA_DB729CE6_B0CD_4141_A603_18DD152317A3__INCLUDED_

#include "AbstractResourceSource.h"

class DbObjectManager
{

public:
	DbObjectManager();
	virtual ~DbObjectManager();
	AbstractDbObjectSource *m_AbstractDbObjectSource;

	DbObject& getDbObjectByURL(URL url);
	DbObject& getDbObjectByUUID(UUID uuid);

private:
	std::list <AbstractDbObjectSource&> DbObjectSources;

};
#endif // !defined(EA_DB729CE6_B0CD_4141_A603_18DD152317A3__INCLUDED_)
