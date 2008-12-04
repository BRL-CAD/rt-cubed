///////////////////////////////////////////////////////////
//  Session.h
//  Implementation of the Class Session
//  Created on:      04-Dec-2008 8:26:47 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_9965DF3D_C35B_4666_B168_E1E0C83D9A76__INCLUDED_)
#define EA_9965DF3D_C35B_4666_B168_E1E0C83D9A76__INCLUDED_

class Session
{

public:
	Session();
	virtual ~Session();

private:
	AbstractPortal& portal;
	int accessLevel;
	std::string uName;

};
#endif // !defined(EA_9965DF3D_C35B_4666_B168_E1E0C83D9A76__INCLUDED_)
