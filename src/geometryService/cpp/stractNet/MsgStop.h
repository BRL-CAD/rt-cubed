///////////////////////////////////////////////////////////
//  MsgStop.h
//  Implementation of the Class MsgStop
//  Created on:      06-Aug-2008 7:51:11 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(MSGSTOP_H_INCLUDED_)
#define MSGSTOP_H_INCLUDED_

#include "StdMsg.h"
#include "SNRoot.h"
#include "StdMsgTypes.h"

class MsgStop : public SNRoot
{

public:
	virtual ~MsgStop();

	MsgStop(std::string Name, std::Set<Integer> msgTypes, std::List<StdMsg> inQ);
	MsgStop(std::string Name, std::List<StdMsg> inQ);

	void addMsgType(int msgType);
	void addMsgTypes(int msgTypes[]);
	void remMsgType(int msgType);

	std::Set<Integer> getMsgTypesSet();
	int getMsgTypesIntArray();

	void sendToMS(StdMsg msg);
	void sendToMsgStop(StdMsg msg);

private:
	/**
	 * This is a reference to the Queue for messages coming FROM the MS to the
	 * destined MsgStop
	 */
	std::List<StdMsg> msgQ;
	std::Set<Integer> MsgTypes;

};
#endif // !defined(MSGSTOP_H_INCLUDED_)
