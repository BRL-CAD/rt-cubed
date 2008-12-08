///////////////////////////////////////////////////////////
//  SendSubSystem.h
//  Implementation of the Class SendSubSystem
//  Created on:      06-Aug-2008 8:03:17 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_40F1AF69_2FA9_42b7_AA6C_D29A009E5DC5__INCLUDED_)
#define EA_40F1AF69_2FA9_42b7_AA6C_D29A009E5DC5__INCLUDED_

#include "MsgStop.h"
#include "MessagingSystem.h"
#include "TestAppCore.h"

class SendSubSystem : public TestAppCore
{

public:
	SendSubSystem();
	virtual ~SendSubSystem();

	SendSubSystem(String Name, MessagingSystem ms, int[] msgTypes, long MinDelay, long MaxDelay);
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
#endif // !defined(EA_40F1AF69_2FA9_42b7_AA6C_D29A009E5DC5__INCLUDED_)
