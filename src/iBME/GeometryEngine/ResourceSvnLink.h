///////////////////////////////////////////////////////////
//  ResourceSvnLink.h
//  Implementation of the Class ResourceSvnLink
//  Created on:      20-Nov-2008 8:00:19 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_CFAE2FCC_88DE_4dc7_9D46_CD0ED6391472__INCLUDED_)
#define EA_CFAE2FCC_88DE_4dc7_9D46_CD0ED6391472__INCLUDED_

#include "AbstractResource.h"
#include "AbstractResourceSource.h"

class ResourceSvnLink : public AbstractResourceSource
{

public:
	ResourceSvnLink();
	virtual ~ResourceSvnLink();

	virtual AbstractResource getResourceByURL(URL url);
	bool putResource(AbstractResource res);

};
#endif // !defined(EA_CFAE2FCC_88DE_4dc7_9D46_CD0ED6391472__INCLUDED_)
