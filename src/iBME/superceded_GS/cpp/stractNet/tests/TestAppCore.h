///////////////////////////////////////////////////////////
//  TestAppCore.h
//  Implementation of the Class TestAppCore
//  Created on:      06-Aug-2008 8:03:11 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_FAB92596_E8A3_45b1_AC69_FE8F16DD432E__INCLUDED_)
#define EA_FAB92596_E8A3_45b1_AC69_FE8F16DD432E__INCLUDED_

#include "MessagingSystem.h"

class TestAppCore
{

public:
	TestAppCore();
	virtual ~TestAppCore();

	TestAppCore(String Name, MessagingSystem MS);
	void err(String data);
	MessagingSystem getMs();
	String gON();
	void out(String data);

private:
	MessagingSystem ms;
	String ObjName;

};
#endif // !defined(EA_FAB92596_E8A3_45b1_AC69_FE8F16DD432E__INCLUDED_)
