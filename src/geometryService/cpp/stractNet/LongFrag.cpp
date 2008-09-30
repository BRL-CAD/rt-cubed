///////////////////////////////////////////////////////////
//  LongFrag.cpp
//  Implementation of the Class LongFrag
//  Created on:      06-Aug-2008 7:51:41 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////
#include "LongFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
LongFrag::~LongFrag() {}
LongFrag::LongFrag(Long lo) {
	MsgFrag("LongFrag", lo, MsgFrag::mftLong);
}
LongFrag::LongFrag(DataInputStream& in) {
	MsgFrag("LongFrag", in, MsgFrag::mftLong);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
void LongFrag::Deserialize(DataInputStream& in) {
	try {
		// Read Integer
		this->field = in.readLong();
	} catch (IOException ioe) {
		SNRoot::err("IOException in Deserialize()", 0);
	}
	return;
}

void LongFrag::Serialize_Specific(DataOutputStream& out) {
	try {
		// write in new data
		out.writeLong(this->field);
	} catch (IOException ioe) {
		SNRoot::err("IOException in Serialize()", 0);
	}
	return;
}
