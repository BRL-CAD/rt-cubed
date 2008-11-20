///////////////////////////////////////////////////////////
//  AbstractResourceSource.h
//  Implementation of the Class AbstractResourceSource
//  Created on:      20-Nov-2008 8:00:08 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D1E248C9_D19C_4b63_9B7D_4417E890C8A4__INCLUDED_)
#define EA_D1E248C9_D19C_4b63_9B7D_4417E890C8A4__INCLUDED_

#include "AbstractResource.h"

class AbstractResourceSource
{

public:
	AbstractResourceSource();
	virtual ~AbstractResourceSource();

	virtual AbstractResource getResourceByURL(URL url);
	bool putResource(AbstractResource res);

};
#endif // !defined(EA_D1E248C9_D19C_4b63_9B7D_4417E890C8A4__INCLUDED_)
