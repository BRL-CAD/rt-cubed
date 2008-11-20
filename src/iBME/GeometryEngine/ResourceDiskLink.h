///////////////////////////////////////////////////////////
//  ResourceDiskLink.h
//  Implementation of the Class ResourceDiskLink
//  Created on:      20-Nov-2008 8:00:18 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_4B2A4CB8_C5C7_4170_8F5C_C027B2137287__INCLUDED_)
#define EA_4B2A4CB8_C5C7_4170_8F5C_C027B2137287__INCLUDED_

#include "AbstractResourceSource.h"

class ResourceDiskLink : public AbstractResourceSource
{

public:
	ResourceDiskLink();
	virtual ~ResourceDiskLink();

	virtual AbstractResource getResourceByURL(URL url);
	bool putResource(AbstractResource res);

};
#endif // !defined(EA_4B2A4CB8_C5C7_4170_8F5C_C027B2137287__INCLUDED_)
