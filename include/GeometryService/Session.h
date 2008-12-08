///////////////////////////////////////////////////////////
//  Session.h
//  Implementation of the Class Session
//  Created on:      04-Dec-2008 8:26:47 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__SESSION_H__)
#define __SESSION_H__

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
#endif // !defined(__SESSION_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
