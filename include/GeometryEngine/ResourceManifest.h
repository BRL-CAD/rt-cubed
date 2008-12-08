///////////////////////////////////////////////////////////
//  ResourceManifest.h
//  Implementation of the Class DbObjectManifest
//  Created on:      04-Dec-2008 8:26:40 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__RESOURCEMANIFEST_H__)
#define __RESOURCEMANIFEST_H__

class DbObjectManifest
{

public:
	DbObjectManifest();
	virtual ~DbObjectManifest();

private:
	std::list<UUID> DbObjectList;
	std::map<UUID, DbObject& > DbObjectMap;

};
#endif // !defined(__RESOURCEMANIFEST_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
