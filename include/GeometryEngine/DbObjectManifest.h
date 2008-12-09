///////////////////////////////////////////////////////////
//  DbObjectManifest.h
//  Implementation of the Class DbObjectManifest
//  Created on:      04-Dec-2008 8:26:40 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__DBOBJECTMANIFEST_H__)
#define __DBOBJECTMANIFEST_H__

#include <list>
#include <map>
#include "GeometryEngine/DbObject.h"
#include "iBME/iBMECommon.h"


class DbObjectManifest
{

public:
	DbObjectManifest();
	virtual ~DbObjectManifest();

private:
	std::list<UUID> DbObjectList;
	std::map<UUID, DbObject > DbObjectMap;

};
#endif // !defined(__DBOBJECTMANIFEST_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
