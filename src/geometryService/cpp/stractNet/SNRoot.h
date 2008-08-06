///////////////////////////////////////////////////////////
//  SNRoot.h
//  Implementation of the Class SNRoot
//  Created on:      06-Aug-2008 7:50:21 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_65F16620_CA28_4439_A43C_F4F00BC530A1__INCLUDED_)
#define EA_65F16620_CA28_4439_A43C_F4F00BC530A1__INCLUDED_

#include "MessagingSystem.h"

class SNRoot
{

public:
	SNRoot();
	virtual ~SNRoot();
	/**
	 * 0 = Normal Waypoints 1 = Object Status reports (NON-Debuging) 2 = Object Data
	 * output (Debuging)
	 */
	static int VerbosityLevel;

	SNRoot(String Name);
	static MessagingSystem getGlobalMS();
	MessagingSystem getLocalMS();
	String gON();
	String gOT();
	static void serr(String message, int vLevel);
	static void setGlobalMS(MessagingSystem ms);
	void setLocalMS(MessagingSystem ms);
	void sON(String name);
	static void sout(String message, int vLevel);

protected:
	String ObjName;

	void err(String message, int vLevel);
	void out(String message, int vLevel);

private:
	/**
	 * Messaging System configurations
	 */
	static MessagingSystem MS_Global;
	MessagingSystem MS_Local;

};
#endif // !defined(EA_65F16620_CA28_4439_A43C_F4F00BC530A1__INCLUDED_)
