///////////////////////////////////////////////////////////
//  PortalTest01.h
//  Implementation of the Class PortalTest01
//  Created on:      06-Aug-2008 8:01:00 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_C4FD8BFD_80E5_44e2_BD93_D36F06D6792F__INCLUDED_)
#define EA_C4FD8BFD_80E5_44e2_BD93_D36F06D6792F__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a loopback set of 2 Portals  A->B
 */
class PortalTest01 : public PortalTestAbstract
{

public:
	virtual ~PortalTest01();

	PortalTest01();
	static void main(String[] args);

};
#endif // !defined(EA_C4FD8BFD_80E5_44e2_BD93_D36F06D6792F__INCLUDED_)
