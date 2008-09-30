///////////////////////////////////////////////////////////
//  FloatFrag.cpp
//  Implementation of the Class FloatFrag
//  Created on:      06-Aug-2008 7:52:20 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "FloatFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
FloatFrag::~FloatFrag(){}
FloatFrag::FloatFrag(float fl){
	MsgFrag("FloatFrag", fl, MsgFrag.mftFloat);
}
FloatFrag::FloatFrag(DataInputStream& in){
	MsgFrag("FloatFrag", in, MsgFrag.mftFloat);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////


void FloatFrag::Deserialize(DataInputStream& in){
	try {
		// Read Float
		this->field = in.readFloat();
	} catch (IOException ioe) {
		SBRoot::err("IOException in Deserialize()", 0);
	}
	return;
}


void FloatFrag::Serialize_Specific(DataOutputStream& out){
	try {
		// write in new data
		out.writeFloat(this->field);
	} catch (IOException ioe) {
		SBRoot::err("IOException in Serialize()", 0);
	}

	return;

}
