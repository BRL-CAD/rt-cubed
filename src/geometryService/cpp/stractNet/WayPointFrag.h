///////////////////////////////////////////////////////////
//  WayPointFrag.h
//  Implementation of the Class WayPointFrag
//  Created on:      06-Aug-2008 7:52:48 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_65F38808_15B7_4386_904F_0E57C69F41B2__INCLUDED_)
#define EA_65F38808_15B7_4386_904F_0E57C69F41B2__INCLUDED_

#include "WayPoint.h"
#include "MsgFrag.h"

class WayPointFrag : public MsgFrag<WayPoint>
{

public:
	WayPointFrag();
	virtual ~WayPointFrag();

	WayPointFrag(WayPoint wp);
	WayPointFrag(DataInputStream in);
	WayPoint getWayPoint();

protected:
	void Deserialize(DataInputStream in);
	void Serialize_Specific(DataOutputStream out);

};
#endif // !defined(EA_65F38808_15B7_4386_904F_0E57C69F41B2__INCLUDED_)
