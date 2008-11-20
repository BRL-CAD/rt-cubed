///////////////////////////////////////////////////////////
//  CommunicationsManager.h
//  Implementation of the Class CommunicationsManager
//  Created on:      20-Nov-2008 12:36:10 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_C3CB83B5_968B_4289_B37A_44626C6BD460__INCLUDED_)
#define EA_C3CB83B5_968B_4289_B37A_44626C6BD460__INCLUDED_

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
#endif // !defined(EA_C3CB83B5_968B_4289_B37A_44626C6BD460__INCLUDED_)
