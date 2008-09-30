///////////////////////////////////////////////////////////
//  BooleanFrag.cpp
//  Implementation of the Class BooleanFrag
//  Created on:      06-Aug-2008 7:52:28 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "BooleanFrag.h"

///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
BooleanFrag::~BooleanFrag(){}
BooleanFrag::BooleanFrag(boolean boo){
	MsgFrag("BooleanFrag", boo, MsgFrag::mftBoolean);
}
BooleanFrag::BooleanFrag(DataInputStream& in){
	MsgFrag("BooleanFrag", in, MsgFrag::mftBoolean);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////

void BooleanFrag::Deserialize(DataInputStream& in){
	try {
		//Read Boolean
		this->field = in.readBoolean();

	} catch (IOException ioe) {
		this->err("IOException in Deserialize()", 0);
	}
	return ;

}


void BooleanFrag::Serialize_Specific(DataOutputStream& out){
	try {
		// write in new data
		out.writeBoolean(this->field);
	} catch (IOException ioe) {
		this->err("IOException in Serialize()", 0);
	}

	return;

}
