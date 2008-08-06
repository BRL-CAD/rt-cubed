///////////////////////////////////////////////////////////
//  PortalTest08.h
//  Implementation of the Class PortalTest08
//  Created on:      06-Aug-2008 8:01:49 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_824EDE41_6A94_4409_9E3B_0C160EE623A8__INCLUDED_)
#define EA_824EDE41_6A94_4409_9E3B_0C160EE623A8__INCLUDED_

#include "PortalTestAbstract.h"

/**
 * Establishes a localhost set of 2 Portals, sends a msg, disconnects, sends a msg,
 * reconnects, sends a message.  A->B
 */
class PortalTest08 : public PortalTestAbstract
{

public:
	virtual ~PortalTest08();

	PortalTest08();
	static void main(String[] args);

};
#endif // !defined(EA_824EDE41_6A94_4409_9E3B_0C160EE623A8__INCLUDED_)
