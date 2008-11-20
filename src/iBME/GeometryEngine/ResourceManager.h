///////////////////////////////////////////////////////////
//  ResourceManager.h
//  Implementation of the Class ResourceManager
//  Created on:      20-Nov-2008 8:00:18 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_0A18A8C8_8F96_4f41_B602_63E24FD71031__INCLUDED_)
#define EA_0A18A8C8_8F96_4f41_B602_63E24FD71031__INCLUDED_

#include "AbstractResourceSource.h"

class ResourceManager
{

public:
	ResourceManager();
	virtual ~ResourceManager();
	AbstractResourceSource *m_AbstractResourceSource;

private:
	std::list <AbstractResourceSource> resSources;

};
#endif // !defined(EA_0A18A8C8_8F96_4f41_B602_63E24FD71031__INCLUDED_)
