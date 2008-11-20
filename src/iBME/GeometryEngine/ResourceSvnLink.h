///////////////////////////////////////////////////////////
//  ResourceSvnLink.h
//  Implementation of the Class ResourceSvnLink
//  Created on:      20-Nov-2008 12:36:21 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_874F027B_30FB_4d9a_997A_F868A7683BEC__INCLUDED_)
#define EA_874F027B_30FB_4d9a_997A_F868A7683BEC__INCLUDED_

#include "AbstractResourceSource.h"

class ResourceSvnLink : public AbstractResourceSource
{

public:
	ResourceSvnLink();
	virtual ~ResourceSvnLink();

	virtual AbstractResource& getResourceByURL(URL url);
	bool putResource(AbstractResource& res);

};
#endif // !defined(EA_874F027B_30FB_4d9a_997A_F868A7683BEC__INCLUDED_)
