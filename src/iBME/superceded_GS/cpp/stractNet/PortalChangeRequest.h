///////////////////////////////////////////////////////////
//  PortalChangeRequest.h
//  Implementation of the Class PortalChangeRequest
//  Created on:      06-Aug-2008 7:48:23 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_F8B2C875_9C85_4054_9592_6BE88F734869__INCLUDED_)
#define EA_F8B2C875_9C85_4054_9592_6BE88F734869__INCLUDED_

class PortalChangeRequest
{

public:
	PortalChangeRequest();
	virtual ~PortalChangeRequest();
	static const int CHANGEOPS = 2;
	int ops;
	static const int REGISTER = 1;
	SocketChannel socket;
	int type;

	PortalChangeRequest(SocketChannel socket, int type, int ops);

};
#endif // !defined(EA_F8B2C875_9C85_4054_9592_6BE88F734869__INCLUDED_)
