///////////////////////////////////////////////////////////
//  AbstractResourceSource.h
//  Implementation of the Class AbstractResourceSource
//  Created on:      20-Nov-2008 12:36:09 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D181387C_3F7D_4a1f_A0F7_5208BFC161FC__INCLUDED_)
#define EA_D181387C_3F7D_4a1f_A0F7_5208BFC161FC__INCLUDED_

class AbstractResourceSource
{

public:
	AbstractResourceSource();
	virtual ~AbstractResourceSource();

	virtual AbstractResource& getResourceByURL(URL url);
	bool putResource(AbstractResource& res);

};
#endif // !defined(EA_D181387C_3F7D_4a1f_A0F7_5208BFC161FC__INCLUDED_)
