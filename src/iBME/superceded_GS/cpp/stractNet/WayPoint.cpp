///////////////////////////////////////////////////////////
//  WayPoint.cpp
//  Implementation of the Class WayPoint
//  Created on:      06-Aug-2008 7:50:40 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "WayPoint.h"


WayPoint::WayPoint(){

}



WayPoint::~WayPoint(){

}





/**
 * Manual Constructor
 */
WayPoint::WayPoint(long time, String host){

}


WayPoint::WayPoint(String host){

}


/**
 * Deserializing Constructor
 */
WayPoint::WayPoint(byte[] data) throw IOException{

}


WayPoint::WayPoint(DataInputStream in) throw IOException{

}


/**
 * @return the host
 */
String WayPoint::getHost(){

	return Host;
}


/**
 * @return the time
 */
long WayPoint::getTime(){

	return 0;
}


byte WayPoint::Serialize(){

	return  NULL;
}


String WayPoint::toString(){

	return  NULL;
}