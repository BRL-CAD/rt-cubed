///////////////////////////////////////////////////////////
//  ResourceDiskLink.h
//  Implementation of the Class SourceDiskLink
//  Created on:      04-Dec-2008 8:26:48 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_BB2055DE_7F5F_4852_A3D8_009A152991BE__INCLUDED_)
#define EA_BB2055DE_7F5F_4852_A3D8_009A152991BE__INCLUDED_

#include "AbstractResourceSource.h"

class SourceDiskLink : public AbstractDbObjectSource
{

public:
	SourceDiskLink();
	virtual ~SourceDiskLink();

	virtual DbObject& getDbObjectByURL(URL url);
	bool putDbObject(DbObject& dbobj);

};
#endif // !defined(EA_BB2055DE_7F5F_4852_A3D8_009A152991BE__INCLUDED_)
