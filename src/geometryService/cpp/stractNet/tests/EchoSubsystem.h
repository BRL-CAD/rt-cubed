///////////////////////////////////////////////////////////
//  EchoSubsystem.h
//  Implementation of the Class EchoSubsystem
//  Created on:      06-Aug-2008 8:02:55 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_A20DDE76_53C1_48a8_B5D3_24694077DFF7__INCLUDED_)
#define EA_A20DDE76_53C1_48a8_B5D3_24694077DFF7__INCLUDED_

#include "MsgStop.h"
#include "MessagingSystem.h"
#include "TestAppCore.java"

class EchoSubsystem : public TestAppCore
{

public:
	EchoSubsystem();
	virtual ~EchoSubsystem();

	EchoSubsystem(String Name, MessagingSystem ms, int[] msgTypes, long MinDelay, long MaxDelay);
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
#endif // !defined(EA_A20DDE76_53C1_48a8_B5D3_24694077DFF7__INCLUDED_)
