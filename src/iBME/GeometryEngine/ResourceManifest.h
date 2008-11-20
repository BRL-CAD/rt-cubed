///////////////////////////////////////////////////////////
//  ResourceManifest.h
//  Implementation of the Class ResourceManifest
//  Created on:      20-Nov-2008 12:36:21 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D1CF56DA_ADE4_47bb_A75E_09930745EF0D__INCLUDED_)
#define EA_D1CF56DA_ADE4_47bb_A75E_09930745EF0D__INCLUDED_

class ResourceManifest
{

public:
	ResourceManifest();
	virtual ~ResourceManifest();

private:
	std::list<UUID> ResourceList;
	std::map<UUID, AbstractResource& > ResourceMap;

};
#endif // !defined(EA_D1CF56DA_ADE4_47bb_A75E_09930745EF0D__INCLUDED_)
