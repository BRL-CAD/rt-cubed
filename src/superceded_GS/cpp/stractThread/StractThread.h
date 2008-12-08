///////////////////////////////////////////////////////////
//  StractThread.h
//  Implementation of the Class StractThread
//  Created on:      17-Sep-2008 8:02:25 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_FF44BAA7_3E76_45a8_A7A2_1FE0AB20F1E0__INCLUDED_)
#define EA_FF44BAA7_3E76_45a8_A7A2_1FE0AB20F1E0__INCLUDED_

#include "STRunnable.h"
#include "STPauseable.h"

class StractThread
{

public:
	StractThread();
	virtual ~StractThread();
	static const long threadTick = 25;

	static void sout(String message);
	static void serr(String message);
	String gON();
	String gOT();
	static boolean Implements(Object object, String Interface);
	static boolean waitForThreadRunStatusChange(STRunnable stru, boolean toStatus);
	static boolean waitForThreadRunStatusChange(STRunnable stru, boolean toStatus, long timeOutInMS);
	static boolean waitForThreadEnableStatusChange(STPauseable stp, boolean toStatus);
	static boolean waitForThreadEnableStatusChange(STPauseable stp, boolean toStatus, long timeOutInMS);

protected:
	String ObjName;

	void out(String message);
	void err(String message);

};
#endif // !defined(EA_FF44BAA7_3E76_45a8_A7A2_1FE0AB20F1E0__INCLUDED_)
