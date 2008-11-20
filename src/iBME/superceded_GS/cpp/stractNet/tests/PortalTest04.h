///////////////////////////////////////////////////////////
//  PortalTest04.h
//  Implementation of the Class PortalTest04
//  Created on:      06-Aug-2008 8:01:19 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_B21B5807_AA7C_42d3_9D48_8F7E2A642F9E__INCLUDED_)
#define EA_B21B5807_AA7C_42d3_9D48_8F7E2A642F9E__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a localhost set of 4 Portals  A->B->C<-D  Msg sent from A, should
 * arrive at D
 */
class PortalTest04 : public PortalTestAbstract
{

public:
	virtual ~PortalTest04();

	PortalTest04();
	static void main(String[] args);

};
#endif // !defined(EA_B21B5807_AA7C_42d3_9D48_8F7E2A642F9E__INCLUDED_)
