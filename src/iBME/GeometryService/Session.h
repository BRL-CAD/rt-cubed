///////////////////////////////////////////////////////////
//  Session.h
//  Implementation of the Class Session
//  Created on:      20-Nov-2008 12:36:22 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_B7E66DB6_9B7D_4665_9AB6_0ADFED6FF865__INCLUDED_)
#define EA_B7E66DB6_9B7D_4665_9AB6_0ADFED6FF865__INCLUDED_

class Session
{

public:
	Session();
	virtual ~Session();

private:
	AbstractPortal& portal;
	std:string username;
	int accessLevel;

};
#endif // !defined(EA_B7E66DB6_9B7D_4665_9AB6_0ADFED6FF865__INCLUDED_)
