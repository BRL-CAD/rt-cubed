///////////////////////////////////////////////////////////
//  SessionManager.h
//  Implementation of the Class SessionManager
//  Created on:      20-Nov-2008 12:36:22 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_227EDD18_0599_4a15_9C7A_15E5A16344F4__INCLUDED_)
#define EA_227EDD18_0599_4a15_9C7A_15E5A16344F4__INCLUDED_

#include "Session.h"

class SessionManager
{

public:
	SessionManager();
	virtual ~SessionManager();
	Session *m_Session;

};
#endif // !defined(EA_227EDD18_0599_4a15_9C7A_15E5A16344F4__INCLUDED_)
