///////////////////////////////////////////////////////////
//  NetMsg.h
//  Implementation of the Class NetMsg
//  Created on:      20-Nov-2008 12:36:17 PM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_1151FC1B_D817_4831_BBA7_763549B9CE58__INCLUDED_)
#define EA_1151FC1B_D817_4831_BBA7_763549B9CE58__INCLUDED_

/**
 * Point to Point Messaging ONLY.
 */
class NetMsg
{

public:
	virtual ~NetMsg();

	void NetMsg();

private:
	/**
	 * consists of origin_hostname::int where int = auto incr
	 */
	std:string msgID;
	/**
	 * OPCODE for the message
	 */
	int msgType;
	byte[] data;

};
#endif // !defined(EA_1151FC1B_D817_4831_BBA7_763549B9CE58__INCLUDED_)
