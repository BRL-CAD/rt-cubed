///////////////////////////////////////////////////////////
//  BrlcadDbResource.h
//  Implementation of the Class BrlcadDbResource
//  Created on:      20-Nov-2008 12:36:10 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_79F7C967_621A_490a_9CAE_07D646A138B8__INCLUDED_)
#define EA_79F7C967_621A_490a_9CAE_07D646A138B8__INCLUDED_

#include "AbstractResource.h"

class BrlcadDbResource : public AbstractResource
{

public:
	BrlcadDbResource();
	virtual ~BrlcadDbResource();

	virtual AbstractResource& getGeometryByObjectName(std::string name);
	virtual AbstractResource& getGeometryByUUID(UUID uuid);

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
	Map < std::string, AbstractGeometry& > nameMap;

};
#endif // !defined(EA_79F7C967_621A_490a_9CAE_07D646A138B8__INCLUDED_)
