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
NetID::NetID(long id, std::string host){
	SNRoot("");
	this->ID = LongFrag(id);
	this->Host = StringFrag(host);
}

/**
 * Copy constructor
 */
NetID::NetID(NetID& addr){
	SNRoot("");
	this->ID = addr.getID();
	this->Host = addr.getHost();
}

/*
 * Deserializing Constructor
 */
NetID::NetID(DataInputStream& in){
	super("NetID");
	in.readInt();
	this->ID = LongFrag(in);
	in.readInt();
	this->Host = StringFrag(in);

}

///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////


std::vector<byte> NetID::Serialize(){
	ByteArrayOutputStream baos = ByteArrayOutputStream();
	DataOutputStream out = DataOutputStream(baos);

	this->Serialize(out);

	return baos.toByteArray();
}

void NetID::Serialize(DataOutputStream& out){
	this->ID.Serialize(out);
	this->Host.Serialize(out);
	return;
}


/**
 * @return the host
 */
std::string NetID::getHost(){
	return this->Host;
}


/**
 * @return the msgStopID
 */
long NetID::getID(){
	return this->ID;
}


std::string NetID::toString(){
	std::string out;
	out << this->ID.getField() << "@" << this->Host.getField();
	return out;
}
