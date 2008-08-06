///////////////////////////////////////////////////////////
//  MessageDispatcher.h
//  Implementation of the Class MessageDispatcher
//  Created on:      06-Aug-2008 7:49:34 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_61DD6466_ADFC_4871_BDD0_33F0918F56E7__INCLUDED_)
#define EA_61DD6466_ADFC_4871_BDD0_33F0918F56E7__INCLUDED_

#include "StdMsg.java"
#include "MessagingSystem.java"
#include "SNRoot.java"

class MessageDispatcher : public SNRoot
{

public:
	MessageDispatcher();
	virtual ~MessageDispatcher();
	long MsgsProcessed;

	MessageDispatcher(String Name, MessagingSystem ms);
	MessageDispatcher(String Name);
	boolean getRunCmd();
	boolean getRunStatus();
	Thread getThread();
	void run();
	void start();
	void stop();

private:
	Thread myThread;
	boolean runCmd;
	boolean runStatus;

	boolean CheckDuplicateMsg(StdMsg msg);
	void deliverLocal(StdMsg msg);
	void deliverRemote(StdMsg msg);

};
#endif // !defined(EA_61DD6466_ADFC_4871_BDD0_33F0918F56E7__INCLUDED_)
