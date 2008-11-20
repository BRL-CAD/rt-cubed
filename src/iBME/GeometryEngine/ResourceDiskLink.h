///////////////////////////////////////////////////////////
//  ResourceDiskLink.h
//  Implementation of the Class ResourceDiskLink
//  Created on:      20-Nov-2008 12:36:20 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_445C945E_EB00_4bfc_8252_D317E7E84456__INCLUDED_)
#define EA_445C945E_EB00_4bfc_8252_D317E7E84456__INCLUDED_

#include "AbstractResourceSource.h"

class ResourceDiskLink : public AbstractResourceSource
{

public:
	ResourceDiskLink();
	virtual ~ResourceDiskLink();

	virtual AbstractResource& getResourceByURL(URL url);
	bool putResource(AbstractResource& res);

};
#endif // !defined(EA_445C945E_EB00_4bfc_8252_D317E7E84456__INCLUDED_)
