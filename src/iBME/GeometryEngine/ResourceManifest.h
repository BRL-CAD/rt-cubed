///////////////////////////////////////////////////////////
//  ResourceManifest.h
//  Implementation of the Class ResourceManifest
//  Created on:      20-Nov-2008 8:00:19 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_161D05C9_42EF_4714_9221_6E5B9D8960F9__INCLUDED_)
#define EA_161D05C9_42EF_4714_9221_6E5B9D8960F9__INCLUDED_

class ResourceManifest
{

public:
	ResourceManifest();
	virtual ~ResourceManifest();

private:
	std::list<UUID> ResourceList;
	std::map<UUID, AbstractResource> ResourceMap;

};
#endif // !defined(EA_161D05C9_42EF_4714_9221_6E5B9D8960F9__INCLUDED_)
