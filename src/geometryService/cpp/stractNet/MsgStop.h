///////////////////////////////////////////////////////////
//  MsgStop.h
//  Implementation of the Class MsgStop
//  Created on:      06-Aug-2008 7:51:11 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_F1D00E32_F7E9_4409_8C53_5C60B1234B36__INCLUDED_)
#define EA_F1D00E32_F7E9_4409_8C53_5C60B1234B36__INCLUDED_

#include "StdMsg.h"
#include "SNRoot.h"

class MsgStop : public SNRoot
{

public:
	MsgStop();
	virtual ~MsgStop();

	MsgStop(String Name, HashSet<Integer> msgTypes, LinkedList<StdMsg> inQ);
	MsgStop(String Name, LinkedList<StdMsg> inQ);
	void addMsgType(int msgType);
	void addMsgTypes(int[] msgTypes);
	HashSet<Integer> getMsgTypesHashSet();
	int getMsgTypesIntArray();
	void remMsgType(int msgType);
	void sendToMS(StdMsg msg);
	void sendToMsgStop(StdMsg msg);

private:
	/**
	 * This is a reference to the Queue for messages coming FROM the MS to the
	 * destined MsgStop
	 */
	LinkedList<StdMsg> msgQ;
	HashSet<Integer> MsgTypes;

};
#endif // !defined(EA_F1D00E32_F7E9_4409_8C53_5C60B1234B36__INCLUDED_)
