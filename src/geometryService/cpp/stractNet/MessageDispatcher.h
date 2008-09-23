///////////////////////////////////////////////////////////
//  MessageDispatcher.h
//  Implementation of the Class MessageDispatcher
//  Created on:      06-Aug-2008 7:49:34 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(MESSAGE_DISPATCHER_H_INCLUDED_)
#define MESSAGE_DISPATCHER_H_INCLUDED_

#include "StdMsg.h"
#include "MessagingSystem.h"
#include "SNRoot.h"

//TODO Probably should work on making STRunnableI NOT a purely virtual Class
class MessageDispatcher : public SNRoot, public STRunnableI
{

public:

	MessageDispatcher(String Name, MessagingSystem& ms);
	virtual ~MessageDispatcher();

	long MsgsProcessed;

	boolean getRunCmd();
	boolean getRunStatus();
	Thread& getThread();
	void run();
	void start();
	void stop();

private:
	Thread& myThread;
	boolean runCmd;
	boolean runStatus;

	boolean CheckDuplicateMsg(StdMsg& msg);
	void deliverLocal(StdMsg& msg);
	void deliverRemote(StdMsg& msg);

};
#endif // !defined(MESSAGE_DISPATCHER_H_INCLUDED_)
