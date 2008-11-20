///////////////////////////////////////////////////////////
//  PortalDataEvent.h
//  Implementation of the Class PortalDataEvent
//  Created on:      06-Aug-2008 7:48:52 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_B8244182_650C_4c2d_A4FE_9B9B9953901D__INCLUDED_)
#define EA_B8244182_650C_4c2d_A4FE_9B9B9953901D__INCLUDED_

#include "PortalManager.h"

class PortalDataEvent
{

public:
	PortalDataEvent();
	virtual ~PortalDataEvent();
	byte data[];
	PortalManager server;
	SocketChannel socket;

	PortalDataEvent(PortalManager server, SocketChannel socket, byte[] data);

};
#endif // !defined(EA_B8244182_650C_4c2d_A4FE_9B9B9953901D__INCLUDED_)
