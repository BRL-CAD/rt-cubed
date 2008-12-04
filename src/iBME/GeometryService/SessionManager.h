///////////////////////////////////////////////////////////
//  SessionManager.h
//  Implementation of the Class SessionManager
//  Created on:      04-Dec-2008 8:26:47 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3CB984D5_0FC2_44e9_97EF_35B7556C56BF__INCLUDED_)
#define EA_3CB984D5_0FC2_44e9_97EF_35B7556C56BF__INCLUDED_

#include "Session.h"

class SessionManager
{

public:
	SessionManager();
	virtual ~SessionManager();
	Session *m_Session;

};
#endif // !defined(EA_3CB984D5_0FC2_44e9_97EF_35B7556C56BF__INCLUDED_)
