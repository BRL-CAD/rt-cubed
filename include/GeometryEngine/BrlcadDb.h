///////////////////////////////////////////////////////////
//  BrlcadDb.h
//  Implementation of the Class BrlcadDb
//  Created on:      04-Dec-2008 8:26:36 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__BRLCADDB_H__)
#define __BRLCADDB_H__

#include <iostream>
#include <map>
#include "DbObject.h"

using namespace std;

class BrlcadDb : public DbObject {

public:
	BrlcadDb();
	virtual ~BrlcadDb();

	virtual DbObject& getDbObjectByObjectName(string name);
	virtual DbObject& getDbObjectByUUID(UUID uuid);

private:
	/**
	 * The title of this BRL-CAD db
	 */
	string dbTitle;
	/**
	 * Directory of BRL-CAD object names and their offset into the BRL-CAD db
	 */
	map<string, long> fileIndex;
	/**
	 * Directory of BRL-CAD object names and their offset into the BRL-CAD db
	 */
	map<string, DbObject> nameMap;

};
#endif // !defined(__BRLCADDB_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
