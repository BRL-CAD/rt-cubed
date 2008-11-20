///////////////////////////////////////////////////////////
//  PortalTest02.h
//  Implementation of the Class PortalTest02
//  Created on:      06-Aug-2008 8:01:05 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_8B7557B3_C30B_444f_A339_4BA7F8CD3468__INCLUDED_)
#define EA_8B7557B3_C30B_444f_A339_4BA7F8CD3468__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a loopback set of 3 Portals  A->B->C
 */
class PortalTest02 : public PortalTestAbstract
{

public:
	virtual ~PortalTest02();

	PortalTest02();
	static void main(String[] args);

};
#endif // !defined(EA_8B7557B3_C30B_444f_A339_4BA7F8CD3468__INCLUDED_)
