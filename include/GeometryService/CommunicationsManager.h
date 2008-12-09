///////////////////////////////////////////////////////////
//  CommunicationsManager.h
//  Implementation of the Class CommunicationsManager
//  Created on:      04-Dec-2008 8:26:37 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__COMMUNICATIONSMANAGER_H__)
#define __COMMUNICATIONSMANAGER_H__

#include <iostream>
#include <list>
#include <map>

#include "GeometryService/AbstractPortal.h"
#include "GeometryService/NetMsg.h"

using namespace std;

/**
 * CommMan performs the netMsg <-> Job conversion
 */
class CommunicationsManager
{

public:
	CommunicationsManager();
	virtual ~CommunicationsManager();

private:
	list <NetMsg> inbox;
	list <NetMsg> outbox;
	/**
	 * Maps hostnames to AbstractPortals
	 *
	 * This MAY not be necessary if all outgoing Traffic is handled by the individual
	 * Session Objects
	 */
	map <string, AbstractPortal> portals;

};
#endif // !defined(__COMMUNICATIONSMANAGER_H__)


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
