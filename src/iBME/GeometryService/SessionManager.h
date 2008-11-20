///////////////////////////////////////////////////////////
//  SessionManager.h
//  Implementation of the Class SessionManager
//  Created on:      20-Nov-2008 8:00:20 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_63079AB9_C581_4699_947B_3853814E2D1D__INCLUDED_)
#define EA_63079AB9_C581_4699_947B_3853814E2D1D__INCLUDED_

#include "Session.h"

class SessionManager
{

public:
	SessionManager();
	virtual ~SessionManager();
	Session *m_Session;

};
#endif // !defined(EA_63079AB9_C581_4699_947B_3853814E2D1D__INCLUDED_)
