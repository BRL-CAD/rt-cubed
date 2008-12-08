///////////////////////////////////////////////////////////
//  NetMsg.h
//  Implementation of the Class NetMsg
//  Created on:      04-Dec-2008 8:26:44 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NETMSG_H__)
#define __NETMSG_H__

#include <list>
#include "iBMECommon.h"




class NetMsg
{

public:
	virtual ~NetMsg();
	NetMsg();

private:
	int msgLen;

	/**
	 * OPCODE for the message
	 */
	int msgType;

	/**
	 * 
	 */

	UUID msgID;
	UUID regardingMsgID;
	list<char> data;

};
#endif // !defined(__NETMSG_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
