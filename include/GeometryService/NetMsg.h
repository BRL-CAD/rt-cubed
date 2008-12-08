///////////////////////////////////////////////////////////
//  NetMsg.h
//  Implementation of the Class NetMsg
//  Created on:      04-Dec-2008 8:26:44 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#if !defined(__NETMSG_H__)
#define __NETMSG_H__

/**
 * Point to Point Messaging ONLY.
 */
class NetMsg
{

public:
	virtual ~NetMsg();

	void NetMsg();

private:
	int msgLen;
	/**
	 * OPCODE for the message
	 */
	int msgType;
	/**
	 * consists of origin_hostname::int where int = auto incr
	 */
	UUID msgID;
	UUID regardingMsgID;
	std::list<byte> data;

};
#endif // !defined(__NETMSG_H__)

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
