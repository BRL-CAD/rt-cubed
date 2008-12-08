///////////////////////////////////////////////////////////
//  CommunicationsManager.h
//  Implementation of the Class CommunicationsManager
//  Created on:      04-Dec-2008 8:26:37 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_7267D4D2_D947_4a8b_BB9E_0CDC321575EA__INCLUDED_)
#define EA_7267D4D2_D947_4a8b_BB9E_0CDC321575EA__INCLUDED_

#include "AbstractPortal.h"

/**
 * CommMan performs the netMsg <-> Job conversion
 */
class CommunicationsManager
{

public:
	CommunicationsManager();
	virtual ~CommunicationsManager();
	AbstractPortal *m_AbstractPortal;

private:
	std::list <NetMsg&> inbox;
	std::list <NetMsg&> outbox;
	/**
	 * Maps hostnames to AbstractPortals
	 * 
	 * This MAY not be necessary if all outgoing Traffic is handled by the individual
	 * Session Objects
	 */
	std::map <std::string, AbstractPortal&> portals;

};
#endif // !defined(EA_7267D4D2_D947_4a8b_BB9E_0CDC321575EA__INCLUDED_)
