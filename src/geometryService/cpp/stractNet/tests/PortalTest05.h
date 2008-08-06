///////////////////////////////////////////////////////////
//  PortalTest05.h
//  Implementation of the Class PortalTest05
//  Created on:      06-Aug-2008 8:01:25 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_D370697D_79B9_409f_9AAC_4808EA1E68E9__INCLUDED_)
#define EA_D370697D_79B9_409f_9AAC_4808EA1E68E9__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a localhost set of 5 Portals  A->B->C<-D ^ E Msg sent from A,
 * should arrive at D & E
 */
class PortalTest05 : public PortalTestAbstract
{

public:
	virtual ~PortalTest05();

	PortalTest05();
	static void main(String[] args);

};
#endif // !defined(EA_D370697D_79B9_409f_9AAC_4808EA1E68E9__INCLUDED_)
