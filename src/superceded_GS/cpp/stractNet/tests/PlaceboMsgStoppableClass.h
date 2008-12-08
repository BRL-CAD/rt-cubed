///////////////////////////////////////////////////////////
//  PlaceboMsgStoppableClass.h
//  Implementation of the Class PlaceboMsgStoppableClass
//  Created on:      06-Aug-2008 8:00:29 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3A077E20_454C_4936_B460_7662ED66BEFC__INCLUDED_)
#define EA_3A077E20_454C_4936_B460_7662ED66BEFC__INCLUDED_

#include "MsgStop.h"
#include "MessagingSystem.h"
#include "SNRoot.h"

class PlaceboMsgStoppableClass : public SNRoot
{

public:
	PlaceboMsgStoppableClass();
	virtual ~PlaceboMsgStoppableClass();

	PlaceboMsgStoppableClass(String Name, int msgsToSend, long delay);
	PlaceboMsgStoppableClass(String Name, int msgsToSend, long delay, MessagingSystem ms);
	MsgStop getMsgStop();
	boolean getRunCmd();
	boolean getRunStatus();
	Thread getThread();
	void run();
	void SendMoreMsgs(int i);
	void start();
	void stop();

private:
	LinkedList<StdMsg> inbox;
	long lDelay;
	int MSGsSent;
	int MSGsToSend;
	MsgStop myMsgStop;
	Thread myThread;
	boolean runCmd;
	boolean runStatus;

};
#endif // !defined(EA_3A077E20_454C_4936_B460_7662ED66BEFC__INCLUDED_)
