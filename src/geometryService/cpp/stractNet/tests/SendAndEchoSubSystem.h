///////////////////////////////////////////////////////////
//  SendAndEchoSubSystem.h
//  Implementation of the Class SendAndEchoSubSystem
//  Created on:      06-Aug-2008 8:03:24 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_3610A50F_1943_44ea_B6D4_CC90C6723473__INCLUDED_)
#define EA_3610A50F_1943_44ea_B6D4_CC90C6723473__INCLUDED_

#include "MsgStop.h"
#include "MessagingSystem.h"
#include "TestAppCore.h"

class SendAndEchoSubSystem : public TestAppCore
{

public:
	SendAndEchoSubSystem();
	virtual ~SendAndEchoSubSystem();

	SendAndEchoSubSystem(String Name, MessagingSystem ms, int[] msgTypes, long MinDelay, long MaxDelay);
	MsgStop getMsgStop();
	boolean getRunCmd();
	boolean getRunStatus();
	Thread getThread();
	void run();
	void start();
	void stop();

private:
	LinkedList<StdMsg> inbox;
	long MAXSLEEP;
	long MINSLEEP;
	MsgStop myMsgStop;
	Thread myThread;
	boolean runCmd;
	boolean runStatus;

};
#endif // !defined(EA_3610A50F_1943_44ea_B6D4_CC90C6723473__INCLUDED_)
