///////////////////////////////////////////////////////////
//  Session.h
//  Implementation of the Class Session
//  Created on:      20-Nov-2008 8:00:20 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_B705221C_D98B_4c8d_A0BD_482E4B17E3CB__INCLUDED_)
#define EA_B705221C_D98B_4c8d_A0BD_482E4B17E3CB__INCLUDED_

#include "AbstractPortal.h"

class Session
{

public:
	Session();
	virtual ~Session();

private:
	AbstractPortal portal;
	std:string username;
	int accessLevel;

};
#endif // !defined(EA_B705221C_D98B_4c8d_A0BD_482E4B17E3CB__INCLUDED_)
