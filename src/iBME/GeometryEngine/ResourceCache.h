///////////////////////////////////////////////////////////
//  ResourceCache.h
//  Implementation of the Class ResourceCache
//  Created on:      20-Nov-2008 12:36:20 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_F50C50EA_ED65_432e_B579_983979FFFF2B__INCLUDED_)
#define EA_F50C50EA_ED65_432e_B579_983979FFFF2B__INCLUDED_

#include "AbstractResourceSource.h"
#include "AbstractResource.h"

class ResourceCache : public AbstractResourceSource
{

public:
	ResourceCache();
	virtual ~ResourceCache();
	AbstractResource *m_AbstractResource;

	virtual AbstractResource& getResourceByURL(URL url);
	bool addResource(AbstractResource& ar);
	bool putResource(AbstractResource& res);

private:
	std::set <AbstractResource&> ResourceCacheSet;
	std::map <URL, AbstractResource&> URLResourceMap;
	std::map <UUID, AbstractResource&> UUIDResourceMap;
	std::map <AbstractResource&. AbstractResourceSource&> ResourceOriginMap;

};
#endif // !defined(EA_F50C50EA_ED65_432e_B579_983979FFFF2B__INCLUDED_)
