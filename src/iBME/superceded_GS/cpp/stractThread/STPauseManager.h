///////////////////////////////////////////////////////////
//  STPauseManager.h
//  Implementation of the Class STPauseManager
//  Created on:      17-Sep-2008 8:02:24 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_0A324EDA_1F2B_47ac_887A_D667B9B0D3D0__INCLUDED_)
#define EA_0A324EDA_1F2B_47ac_887A_D667B9B0D3D0__INCLUDED_

#include "STRunnable.h"
#include "STPauseable.h"
#include "STRunManager.h"

class STPauseManager : public STRunManager
{

public:
	STPauseManager();
	virtual ~STPauseManager();

	STPauseManager(String Name);
	int getNumRunnables();
	int getNumPauseables();
	int getNumEnabled();
	int getNumDisabled();
	boolean areAllEnabled();
	boolean areAnyEnabled();
	void enableAll();
	void enableAll(boolean block);
	boolean enable(String name);
	boolean enable(String name, boolean block);
	void disableAll();
	void disableAll(boolean block);
	boolean disable(String name);
	boolean disable(String name, boolean block);
	long getTimeOut();
	void setTimeOut(long timeOut);

private:
	long timeOut;

	void _ModThreadEnableStatus_All(boolean status, boolean block);
	boolean _ModThreadEnableStatus(STRunnable stru, boolean status, boolean block);
	boolean _enable(STPauseable stp, boolean block);
	boolean _disable(STPauseable stp, boolean block);

};
#endif // !defined(EA_0A324EDA_1F2B_47ac_887A_D667B9B0D3D0__INCLUDED_)
