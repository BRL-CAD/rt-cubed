///////////////////////////////////////////////////////////
//  BrlcadDbResource.h
//  Implementation of the Class BrlcadDb
//  Created on:      04-Dec-2008 8:26:36 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_F576828D_6495_4f32_8BD9_9264BDA263A9__INCLUDED_)
#define EA_F576828D_6495_4f32_8BD9_9264BDA263A9__INCLUDED_

#include "AbstractResource.h"

class BrlcadDb : public DbObject
{

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
	Map < std::string, long > fileIndex;
	/**
	 * Directory of BRL-CAD object names and their offset into the BRL-CAD db
	 */
	Map < std::string, DbObject& > nameMap;

};
#endif // !defined(EA_F576828D_6495_4f32_8BD9_9264BDA263A9__INCLUDED_)
