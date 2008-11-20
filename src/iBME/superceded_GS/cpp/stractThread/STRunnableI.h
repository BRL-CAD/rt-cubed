///////////////////////////////////////////////////////////
//  STRunnable.h
//  Implementation of the Interface STRunnable
//  Created on:      17-Sep-2008 8:02:26 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_0DF0FDB2_6631_49b9_9681_F1B217FCA984__INCLUDED_)
#define EA_0DF0FDB2_6631_49b9_9681_F1B217FCA984__INCLUDED_

class STRunnable : public Runnable
{

public:
	STRunnable() {

	}

	virtual ~STRunnable() {

	}

	void start() =0;
	Thread getThread() =0;
	void stop() =0;
	boolean getRunStatus() =0;
	boolean getRunCmd() =0;

};
#endif // !defined(EA_0DF0FDB2_6631_49b9_9681_F1B217FCA984__INCLUDED_)
