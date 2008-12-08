///////////////////////////////////////////////////////////
//  ByteArrayFrag.cpp
//  Implementation of the Class ByteArrayFrag
//  Created on:      06-Aug-2008 7:52:41 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "ByteArrayFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////

ByteArrayFrag::~ByteArrayFrag(){}
ByteArrayFrag::ByteArrayFrag(byte b[]){
	MsgFrag("ByteArrayFrag", b, MsgFrag::mftByteArray);
}
ByteArrayFrag::ByteArrayFrag(DataInputStream& in){
	MsgFrag("ByteArrayFrag", in, MsgFrag::mftByteArray);
}

///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////

void ByteArrayFrag::Deserialize(DataInputStream& in){
	try {
		//Read length of array
		int len = in.readInt();

		//Assign array
		this->field = byte[len];

		//Read byte[]
		in.read(this->field );

	} catch (IOException ioe) {
		SNRoot::err("IOException in Deserialize()", 0);
	}
	return ;
}


void ByteArrayFrag::Serialize_Specific(DataOutputStream& out){
	try {
		//Write length of array
		out.writeInt(this->field.length);

		//Write byte[]
		out.write(this->field);

	} catch (IOException ioe) {
		SNRoot::err("IOException in Serialize()", 0);
	}

	return;
}
