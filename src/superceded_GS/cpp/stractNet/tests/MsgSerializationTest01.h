///////////////////////////////////////////////////////////
//  MsgSerializationTest01.h
//  Implementation of the Class MsgSerializationTest01
//  Created on:      06-Aug-2008 8:02:50 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_09813CCF_E68A_452c_833B_0D2619CD2B25__INCLUDED_)
#define EA_09813CCF_E68A_452c_833B_0D2619CD2B25__INCLUDED_

class MsgSerializationTest01
{

public:
	MsgSerializationTest01();
	virtual ~MsgSerializationTest01();

	static void main(String[] args) throw InterruptedException;

private:
	static void printBar();
	static void TestWayPoints() throw InterruptedException;

};
#endif // !defined(EA_09813CCF_E68A_452c_833B_0D2619CD2B25__INCLUDED_)
