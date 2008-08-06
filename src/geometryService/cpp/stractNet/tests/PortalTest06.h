///////////////////////////////////////////////////////////
//  PortalTest06.h
//  Implementation of the Class PortalTest06
//  Created on:      06-Aug-2008 8:01:33 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_B275A59B_C39E_4490_ABF5_A99FFFD7A3C2__INCLUDED_)
#define EA_B275A59B_C39E_4490_ABF5_A99FFFD7A3C2__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a localhost set of 4 Portals  A->B v  v C->D  B / \ A   D \ / C
 * Msg sent from A, only one should arrive at D
 */
class PortalTest06 : public PortalTestAbstract
{

public:
	virtual ~PortalTest06();

	PortalTest06();
	static void main(String[] args);

};
#endif // !defined(EA_B275A59B_C39E_4490_ABF5_A99FFFD7A3C2__INCLUDED_)
