///////////////////////////////////////////////////////////
//  NetID.cpp
//  Implementation of the Class NetID
//  Created on:      06-Aug-2008 7:50:46 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////
#include "NetID.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
NetID::~NetID(){

}





/**
 * Manual Constructor
 */
NetID::NetID(long ID, std::string host){

}


/**
 * Copy constructor
 */
NetID::NetID(NetID addr){

}

/*
 * Deserializing Constructor
 */
NetID::NetID(DataInputStream in){

}

///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////

/**
 * @return the host
 */
std::string NetID::getHost(){

	return Host;
}


/**
 * @return the msgStopID
 */
long NetID::getID(){

	return ID;
}


byte NetID::Serialize(){

	return  NULL;
}


std::vector<byte> NetID::Serialize(DataOutputStream out){

}


std::string NetID::toString(){
	std::string out;
	out << this->ID.getField() << "@" << this->Host.getField();
	return  out;
}
