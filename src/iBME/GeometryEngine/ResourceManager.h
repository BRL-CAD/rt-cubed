///////////////////////////////////////////////////////////
//  ResourceManager.h
//  Implementation of the Class ResourceManager
//  Created on:      20-Nov-2008 12:36:20 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_658D4563_2739_41a1_A144_82D5852AD35A__INCLUDED_)
#define EA_658D4563_2739_41a1_A144_82D5852AD35A__INCLUDED_

#include "AbstractResourceSource.h"

class ResourceManager
{

public:
	ResourceManager();
	virtual ~ResourceManager();
	AbstractResourceSource *m_AbstractResourceSource;

	AbstractResource& getResourceByURL(URL url);
	AbstractResource& getResourceByUUID(UUID uuid);

private:
	std::list <AbstractResourceSource&> resSources;

};
#endif // !defined(EA_658D4563_2739_41a1_A144_82D5852AD35A__INCLUDED_)
