///////////////////////////////////////////////////////////
//  WayPoint.h
//  Implementation of the Class WayPoint
//  Created on:      06-Aug-2008 7:50:39 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_991F4D44_231D_42fe_A206_0FCFADF76F5F__INCLUDED_)
#define EA_991F4D44_231D_42fe_A206_0FCFADF76F5F__INCLUDED_

#include "SNRoot.h"

class WayPoint : public SNRoot
{

public:
	WayPoint();
	virtual ~WayPoint();

	WayPoint(long time, String host);
	WayPoint(String host);
	WayPoint(byte[] data) throw IOException;
	WayPoint(DataInputStream in) throw IOException;
	String getHost();
	long getTime();
	byte Serialize();
	String toString();

private:
	String Host;
	long time;

};
#endif // !defined(EA_991F4D44_231D_42fe_A206_0FCFADF76F5F__INCLUDED_)
