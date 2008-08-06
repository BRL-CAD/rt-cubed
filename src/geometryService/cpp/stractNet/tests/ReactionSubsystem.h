///////////////////////////////////////////////////////////
//  ReactionSubsystem.h
//  Implementation of the Class ReactionSubsystem
//  Created on:      06-Aug-2008 8:03:01 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_85D250EB_434D_4b40_AF7D_84F3E0C0F625__INCLUDED_)
#define EA_85D250EB_434D_4b40_AF7D_84F3E0C0F625__INCLUDED_

#include "MsgStop.h"
#include "MessagingSystem.h"
#include "TestAppCore.java"

class ReactionSubsystem : public TestAppCore
{

public:
	ReactionSubsystem();
	virtual ~ReactionSubsystem();

	ReactionSubsystem(String Name, MessagingSystem ms, int[] msgTypes, long MinDelay, long MaxDelay);
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
#endif // !defined(EA_85D250EB_434D_4b40_AF7D_84F3E0C0F625__INCLUDED_)
