///////////////////////////////////////////////////////////
//  NetMsg.h
//  Implementation of the Class NetMsg
//  Created on:      20-Nov-2008 8:00:15 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_5A08A2EE_97A1_434e_8FF6_1A531C9BACE5__INCLUDED_)
#define EA_5A08A2EE_97A1_434e_8FF6_1A531C9BACE5__INCLUDED_

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
#endif // !defined(EA_5A08A2EE_97A1_434e_8FF6_1A531C9BACE5__INCLUDED_)
