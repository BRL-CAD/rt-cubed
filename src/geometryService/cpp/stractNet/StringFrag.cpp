///////////////////////////////////////////////////////////
//  StringFrag.cpp
//  Implementation of the Class StringFrag
//  Created on:      06-Aug-2008 7:52:07 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////
#include "StringFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
StringFrag::~StringFrag(){}
StringFrag::StringFrag(String str){
	MsgFrag("StringFrag", str, MsgFrag::mftString);
}
StringFrag::StringFrag(DataInputStream& in){
	MsgFrag("StringFrag", in, MsgFrag::mftString);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
void StringFrag::Deserialize(DataInputStream& in){
	try {
		// Read LEN then String
		int strLen = in.readInt();
		char c[strLen];

		// Convert String
		for (int i = 0; i < strLen; i++) {
			c[i] = in.readChar();
		}
		this->field = new String(c);

	} catch (IOException ioe) {
		SNRoot::err("IOException in Deserialize()", 0);
	}
	return;
}
void StringFrag::Serialize_Specific(DataOutputStream& out){
	try {
		// write in new data
		out.writeInt(this->field.length());
		out.writeChars(this->field);
	} catch (IOException ioe) {
		SNRoot::err("IOException in Serialize()", 0);
	}
	return;
}
