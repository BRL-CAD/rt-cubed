///////////////////////////////////////////////////////////
//  SNRoot.h
//  Implementation of the Class SNRoot
//  Created on:      06-Aug-2008 7:50:21 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(SNROOT_H_INCLUDED_)
#define SNROOT_H_INCLUDED_

#include "MessagingSystem.h"

class SNRoot
{

public:
	SNRoot(String Name);
	virtual ~SNRoot();


	static int VerbosityLevel = 0;
	static MessagingSystem& getGlobalMS();
	static void setGlobalMS(MessagingSystem& ms);
	static void sout(String message);
	static void serr(String message);


	MessagingSystem& getLocalMS();
	String gON();
	String gOT();
	void setLocalMS(MessagingSystem& ms);
	void sON(String name);

protected:
	String ObjName;

	void err(String message);
	void out(String message);

private:
	static MessagingSystem MS_Global;
	MessagingSystem MS_Local;

};
#endif // !defined(SNROOT_H_INCLUDED_)
