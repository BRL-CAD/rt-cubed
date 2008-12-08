///////////////////////////////////////////////////////////
//  BrlcadDbResource.h
//  Implementation of the Class BrlcadDb
//  Created on:      04-Dec-2008 8:26:36 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__BRLCADDBRESOURCE_H__)
#define __BRLCADDBRESOURCE_H__

#include "AbstractResource.h"

class BrlcadDb: public DbObject {

public:
	BrlcadDb();
	virtual ~BrlcadDb();

	virtual DbObject& getDbObjectByObjectName(std::string name);
	virtual DbObject& getDbObjectByUUID(UUID uuid);

private:
	/**
	 * The title of this BRL-CAD db
	 */
	std::string dbTitle;
	/**
	 * Directory of BRL-CAD object names and their offset into the BRL-CAD db
	 */
	Map<std::string, long> fileIndex;
	/**
	 * Directory of BRL-CAD object names and their offset into the BRL-CAD db
	 */
	Map<std::string, DbObject&> nameMap;

};
#endif // !defined(__BRLCADDBRESOURCE_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
