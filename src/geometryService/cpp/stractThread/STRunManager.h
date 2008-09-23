///////////////////////////////////////////////////////////
//  STRunManager.h
//  Implementation of the Class STRunManager
//  Created on:      17-Sep-2008 8:02:25 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_E5662096_4F99_40f3_8976_54FB9F7098B1__INCLUDED_)
#define EA_E5662096_4F99_40f3_8976_54FB9F7098B1__INCLUDED_

#include "STRunnableI.h"
#include "StractThread.h"

class STRunManager : public StractThread
{

public:
	STRunManager();
	virtual ~STRunManager();

	STRunManager(String Name);
	int getNumThreads();
	int getNumRunning();
	int getNumNotRunning();
	void addDoNotExecute(String name, STRunnableI stru);
	boolean addExecute(String name, STRunnableI stru);
	STRunnableI rem(String name);
	boolean areAllThreadsRunning();
	boolean areAnyThreadsRunning();
	boolean areAllStatusRunning();
	boolean areAnyStatusRunning();
	void executeAll();
	void executeAll(boolean block);
	boolean execute(String name);
	boolean execute(String name, boolean block);
	void stopAll();
	void stopAll(boolean block);
	boolean stop(String name);
	boolean stop(String name, boolean block);
	long getTimeOut();
	void setTimeOut(long timeOut);

protected:
	HashMap<String, STRunnableI> Pool;

private:
	long timeOut;

	boolean stop_int(STRunnableI stru, boolean block);

};
#endif // !defined(EA_E5662096_4F99_40f3_8976_54FB9F7098B1__INCLUDED_)
