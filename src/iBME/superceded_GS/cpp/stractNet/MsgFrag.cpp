///////////////////////////////////////////////////////////
//  MsgFrag.cpp
//  Implementation of the Class MsgStop
//  Created on:      06-Aug-2008 7:51:11 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////
#include "MsgFrag.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
MsgFrag::MsgFrag(String name, E& in, int mfType) {
	SNRoot(name);
	this->field = in;
	this->MFType = mfType;
}
MsgFrag::MsgFrag(String name, DataInputStream& in, int mfType) {
	SNRoot(name);
	this->MFType = mfType;
	this->Deserialize(in);
}
MsgFrag::~MsgFrag() {
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////

byte* MsgFrag::Serialize() {
	ByteArrayOutputStream baos;
	DataOutputStream out;

	try {
		this->Serialize(out);
		return baos.toByteArray(); //TODO convert these functions to use streams.
	} catch (IOException e) {
		SNRoot::err("IOException in Serialize()", 0);
	}
	return null;

}

void MsgFrag::Serialize(DataOutputStream& out) {
	out.writeInt(this->MFType);
	this->Serialize_Specific(out);
}


E MsgFrag::getField() {
	return this->field;
}

void MsgFrag::setField(E val) {
	this->field = val;
}

int MsgFrag::getMFType() {
	return this->MFType;
}

std::string MsgFrag::toString() {
	std::string out;
	out << this->field << "(" << this->name << ")";
	return out;
}








