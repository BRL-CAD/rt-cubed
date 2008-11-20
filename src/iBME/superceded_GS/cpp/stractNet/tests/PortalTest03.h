///////////////////////////////////////////////////////////
//  PortalTest03.h
//  Implementation of the Class PortalTest03
//  Created on:      06-Aug-2008 8:01:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_8BD61748_613C_4d92_89CC_4619E4951A16__INCLUDED_)
#define EA_8BD61748_613C_4d92_89CC_4619E4951A16__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a loopback set of 4 Portals  A->B->C->D  Msg sent from A, should
 * arrive at D
 */
class PortalTest03 : public PortalTestAbstract
{

public:
	virtual ~PortalTest03();

	PortalTest03();
	static void main(String[] args);

};
#endif // !defined(EA_8BD61748_613C_4d92_89CC_4619E4951A16__INCLUDED_)
