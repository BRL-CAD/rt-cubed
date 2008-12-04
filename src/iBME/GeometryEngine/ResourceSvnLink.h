///////////////////////////////////////////////////////////
//  ResourceSvnLink.h
//  Implementation of the Class SourceSvnLink
//  Created on:      04-Dec-2008 8:26:48 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_32751E74_D827_4332_B8C4_D2092B82E483__INCLUDED_)
#define EA_32751E74_D827_4332_B8C4_D2092B82E483__INCLUDED_

#include "AbstractResourceSource.h"

class SourceSvnLink : public AbstractDbObjectSource
{

public:
	SourceSvnLink();
	virtual ~SourceSvnLink();

	virtual DbObject& getDbObjectByURL(URL url);
	bool putDbObject(DbObject& dbobj);

};
#endif // !defined(EA_32751E74_D827_4332_B8C4_D2092B82E483__INCLUDED_)
