///////////////////////////////////////////////////////////
//  ShortFrag.cpp
//  Implementation of the Class ShortFrag
//  Created on:      06-Aug-2008 7:51:59 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////
#include "ShortFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
ShortFrag::~ShortFrag(){}
ShortFrag::ShortFrag(Short sh){
	MsgFrag("ShortFrag", sh, MsgFrag::mftShort);
}
ShortFrag::ShortFrag(DataInputStream& in){
	MsgFrag("ShortFrag", in, MsgFrag::mftShort);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
void ShortFrag::Deserialize(DataInputStream& in){
	try {
		// Read Short
		this->field = in.readShort();
	} catch (IOException ioe) {
		SNRoot::err("IOException in Deserialize()", 0);
	}
	return;
}
void ShortFrag::Serialize_Specific(DataOutputStream& out){
	try {
		// write in new data
		out.writeShort(this->field);
	} catch (IOException ioe) {
		SNRoot::err("IOException in Serialize()", 0);
	}
	return;
}
