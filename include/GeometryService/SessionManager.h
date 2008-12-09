///////////////////////////////////////////////////////////
//  SessionManager.h
//  Implementation of the Class SessionManager
//  Created on:      04-Dec-2008 8:26:47 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__SESSIONMANAGER_H__)
#define __SESSIONMANAGER_H__

#include "GeometryService/Session.h"

class SessionManager
{

public:
	SessionManager();
	virtual ~SessionManager();
	Session *m_Session;

};
#endif // !defined(__SESSIONMANAGER_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
