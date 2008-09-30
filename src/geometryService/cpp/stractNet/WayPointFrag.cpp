///////////////////////////////////////////////////////////
//  WayPointFrag.cpp
//  Implementation of the Class WayPointFrag
//  Created on:      06-Aug-2008 7:52:49 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "WayPointFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
WayPointFrag::~WayPointFrag(){}
WayPointFrag::WayPointFrag(WayPoint& way){
	MsgFrag("WayPointFrag", way, MsgFrag::mftWaypoint);
}
WayPointFrag::WayPointFrag(DataInputStream& in){
	MsgFrag("WayPointFrag", in, MsgFrag::mftWaypoint);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
void WayPointFrag::Deserialize(DataInputStream& in){
	try {
		//Read WayPoint
		Waypoint wp(in); //TODO Check to make sure this is the right way to declare a class!!!!
		this->field = wp;

	} catch (IOException ioe) {
		SNRoot::err("IOException in Deserialize()", 0);
	}
	return;
}
void WayPointFrag::Serialize_Specific(DataOutputStream& out){
	try {
		// write in new data
		out.write(this->field.Serialize());
	} catch (IOException ioe) {
		SNRoot::err("IOException in Serialize()", 0);
	}
	return;
}

/**
 * Custom Getter
 */
WayPoint& WayPointFrag::getWayPoint(){
	return (WayPoint)this->getField();
}


