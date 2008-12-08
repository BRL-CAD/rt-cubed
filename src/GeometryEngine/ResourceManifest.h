///////////////////////////////////////////////////////////
//  ResourceManifest.h
//  Implementation of the Class DbObjectManifest
//  Created on:      04-Dec-2008 8:26:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_CFEA95F7_A065_494c_8B60_C33B4BB1B89C__INCLUDED_)
#define EA_CFEA95F7_A065_494c_8B60_C33B4BB1B89C__INCLUDED_

class DbObjectManifest
{

public:
	DbObjectManifest();
	virtual ~DbObjectManifest();

private:
	std::list<UUID> DbObjectList;
	std::map<UUID, DbObject& > DbObjectMap;

};
#endif // !defined(EA_CFEA95F7_A065_494c_8B60_C33B4BB1B89C__INCLUDED_)
