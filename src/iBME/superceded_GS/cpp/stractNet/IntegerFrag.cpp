///////////////////////////////////////////////////////////
//  IntegerFrag.cpp
//  Implementation of the Class IntegerFrag
//  Created on:      06-Aug-2008 7:51:52 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////
#include "IntegerFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
IntegerFrag::~IntegerFrag(){}
IntegerFrag::IntegerFrag(int in){
	MsgFrag("IntegerFrag", in, MsgFrag::mftInteger);
}
IntegerFrag::IntegerFrag(DataInputStream& in){
	MsgFrag("IntegerFrag", in, MsgFrag::mftInteger);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
void IntegerFrag::Deserialize(DataInputStream& in){
	try {
		// Read Integer
		this->field = in.readInt();
	} catch (IOException ioe) {
		SNRoot::err("IOException in Deserialize()", 0);
	}
	return;
}
void IntegerFrag::Serialize_Specific(DataOutputStream& out){
	try {
		// write in new data
		out.writeInt(this->field);
	} catch (IOException ioe) {
		SNRoot::err("IOException in Serialize()", 0);
	}
	return;
}
