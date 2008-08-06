///////////////////////////////////////////////////////////
//  NetID.cpp
//  Implementation of the Class NetID
//  Created on:      06-Aug-2008 7:50:46 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "NetID.h"


NetID::NetID(){

}



NetID::~NetID(){

}





/**
 * Manual Constructor
 */
NetID::NetID(long ID, String host){

}


/**
 * Copy constructor
 */
NetID::NetID(NetID addr){

}


/**
 * public NetID(byte[] data) throws IOException { super("SNAddr");  Setup Streams
 * ByteArrayInputStream bais = new ByteArrayInputStream(data); DataInputStream in
 * = new DataInputStream(bais);  Deserialize Components this.ID = new LongFrag(in);
 * this.Host = new StringFrag(in); }
 */
NetID::NetID(DataInputStream in) throw IOException{

}


/**
 * @return the host
 */
String NetID::getHost(){

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


void NetID::Serialize(DataOutputStream out){

}


String NetID::toString(){

	return  NULL;
}