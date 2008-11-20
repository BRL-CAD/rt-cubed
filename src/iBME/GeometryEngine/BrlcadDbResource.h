///////////////////////////////////////////////////////////
//  BrlcadDbResource.h
//  Implementation of the Class BrlcadDbResource
//  Created on:      20-Nov-2008 8:00:09 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_415FFE3D_2D17_4d6c_916B_A23DEE280A15__INCLUDED_)
#define EA_415FFE3D_2D17_4d6c_916B_A23DEE280A15__INCLUDED_

#include "AbstractResource.h"

class BrlcadDbResource : public AbstractResource
{

public:
	BrlcadDbResource();
	virtual ~BrlcadDbResource();

	virtual AbstractResource getGeometryByObjectName(std::string name);
	virtual AbstractResource getGeometryByUUName(UUName uuname);

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
	Map < std::string, AbstractGeometry> nameMap;

};
#endif // !defined(EA_415FFE3D_2D17_4d6c_916B_A23DEE280A15__INCLUDED_)
