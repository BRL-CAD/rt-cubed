///////////////////////////////////////////////////////////
//  CommunicationsManager.h
//  Implementation of the Class CommunicationsManager
//  Created on:      20-Nov-2008 8:00:09 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_92AA3A5A_13E3_4189_824B_A233219A3C8D__INCLUDED_)
#define EA_92AA3A5A_13E3_4189_824B_A233219A3C8D__INCLUDED_

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
	std::list <NetMsg> inbox;
	std::list <NetMsg> outbox;
	/**
	 * Maps hostnames to AbstractPortals
	 * 
	 * This MAY not be necessary if all outgoing Traffic is handled by the individual
	 * Session Objects
	 */
	std::map <std::string, AbstractPortal> portals;

};
#endif // !defined(EA_92AA3A5A_13E3_4189_824B_A233219A3C8D__INCLUDED_)
