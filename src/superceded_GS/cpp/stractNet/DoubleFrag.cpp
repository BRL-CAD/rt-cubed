///////////////////////////////////////////////////////////
//  DoubleFrag.cpp
//  Implementation of the Class DoubleFrag
//  Created on:      06-Aug-2008 7:52:13 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "DoubleFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////

DoubleFrag::~DoubleFrag(){}
DoubleFrag::DoubleFrag(double db){
	MsgFrag("DoubleFrag", db, MsgFrag::mftDouble);
}
DoubleFrag::DoubleFrag(DataInputStream& in){
	MsgFrag("DoubleFrag", in, MsgFrag::mftDouble);
}

///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
void DoubleFrag::Deserialize(DataInputStream& in){
	try {
		// Read Double
		this->field = in.readDouble();
	} catch (IOException ioe) {
		SNRoot::err("IOException in Deserialize()", 0);
	}
	return;

}

void DoubleFrag::Serialize_Specific(DataOutputStream& out){
	try {
			// write in new data
			out.writeDouble(this->field);
		} catch (IOException ioe) {
			SNRoot::err("IOException in Serialize()", 0);
		}

		return;

}
