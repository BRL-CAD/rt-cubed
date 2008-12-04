///////////////////////////////////////////////////////////
//  NetMsg.h
//  Implementation of the Class NetMsg
//  Created on:      04-Dec-2008 8:26:44 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_527B4B31_C424_4ea8_80F8_A3C0CCD87CE7__INCLUDED_)
#define EA_527B4B31_C424_4ea8_80F8_A3C0CCD87CE7__INCLUDED_

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
#endif // !defined(EA_527B4B31_C424_4ea8_80F8_A3C0CCD87CE7__INCLUDED_)
