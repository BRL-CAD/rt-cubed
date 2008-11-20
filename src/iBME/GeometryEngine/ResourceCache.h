///////////////////////////////////////////////////////////
//  ResourceCache.h
//  Implementation of the Class ResourceCache
//  Created on:      20-Nov-2008 8:00:18 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_B6EDC994_8297_4093_841B_35133708BBAC__INCLUDED_)
#define EA_B6EDC994_8297_4093_841B_35133708BBAC__INCLUDED_

#include "AbstractResourceSource.h"
#include "AbstractResource.h"

class ResourceCache : public AbstractResourceSource
{

public:
	ResourceCache();
	virtual ~ResourceCache();
	AbstractResource *m_AbstractResource;

	virtual AbstractResource getResourceByURL(URL url);
	bool addResource(AbstractResource ar);
	bool putResource(AbstractResource res);

private:
	std::set <AbstractResource> ResourceCacheSet;
	std::map <URL, AbstractResource> URLResourceMap;

};
#endif // !defined(EA_B6EDC994_8297_4093_841B_35133708BBAC__INCLUDED_)
