///////////////////////////////////////////////////////////
//  WayPointFrag.h
//  Implementation of the Class WayPointFrag
//  Created on:      06-Aug-2008 7:52:48 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(WAYPOINT_H_INCLUDED_)
#define WAYPOINT_H_INCLUDED_

#include "WayPoint.h"
#include "MsgFrag.h"

class WayPointFrag : public MsgFrag<WayPoint>
{

public:
	virtual ~WayPointFrag();
	WayPointFrag(WayPoint& wp);
	WayPointFrag(DataInputStream& in);
	WayPoint getWayPoint();

protected:
	void Deserialize(DataInputStream& in);
	void Serialize_Specific(DataOutputStream& out);

};
#endif // !defined(WAYPOINT_H_INCLUDED_)
