///////////////////////////////////////////////////////////
//  StdMsg.cpp
//  Implementation of the Class StdMsg
//  Created on:      06-Aug-2008 7:50:58 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "StdMsg.h"


StdMsg::StdMsg(){

}



StdMsg::~StdMsg(){

}





/**
 * Copy Constructor
 */
StdMsg::StdMsg(StdMsg sm){

}


/**
 * Manual Constructors
 */
StdMsg::StdMsg(int msgType){

}


StdMsg::StdMsg(int msgType, String to){

}


/**
 * Deserializing Constructors
 */
StdMsg::StdMsg(byte[] inData){

}


StdMsg::StdMsg(DataInputStream in){

}


void StdMsg::AddElement(MsgFrag<?> element){

}


void StdMsg::DeserializeElements(DataInputStream in) throw IOException{

}


void StdMsg::DeserializeHeader(DataInputStream in) throw IOException{

}


String StdMsg::ElementsToString(){

	return  NULL;
}


MsgFrag<?> StdMsg::GetElement(int index){

	return  NULL;
}


ArrayList<MsgFrag<?>> StdMsg::GetElements(){

	return  NULL;
}


String StdMsg::getFromHost(){

	return  NULL;
}


StringFrag StdMsg::getFromHostFrag(){

	return  NULL;
}


MsgStop StdMsg::getLocalFrom(){

	return LocalFrom;
}


NetID StdMsg::getMsgID(){

	return MsgID;
}


int StdMsg::getMsgType(){

	return MsgType;
}


String StdMsg::getToHost(){

	return  NULL;
}


StringFrag StdMsg::getToHostFrag(){

	return  NULL;
}


/**
 * Getters & Setters
 */
ArrayList<WayPoint> StdMsg::getWayPoints(){

	return  NULL;
}


boolean StdMsg::HasElement(MsgFrag<?> element){

	return  NULL;
}


int StdMsg::IndexOfElement(MsgFrag<?> element){

	return 0;
}


boolean StdMsg::RemoveElement(MsgFrag<?> element){

	return  NULL;
}


/**
 * Serializer
 */
byte StdMsg::Serialize(){

	return  NULL;
}


boolean StdMsg::Serialize(DataOutputStream out) throw IOException{

	return  NULL;
}


void StdMsg::SerializeElements(DataOutputStream out) throw IOException{

}


void StdMsg::SerializeHeader(DataOutputStream out) throw IOException{

}


void StdMsg::setFromHost(String fromHost){

}


void StdMsg::setFromHostFrag(StringFrag fromHostFrag){

}


void StdMsg::setLocalFrom(MsgStop localFrom){

	LocalFrom = newVal;
}


void StdMsg::setMsgID(NetID msgID){

	MsgID = newVal;
}


void StdMsg::setMsgType(int msgType){

	MsgType = newVal;
}


void StdMsg::setToHost(String toHost){

}


void StdMsg::setToHostFrag(StringFrag toHostFrag){

}


/**
 * Utilities
 */
void StdMsg::StampWayPoint(WayPoint wp){

}


void StdMsg::StampWayPoint(String Host){

}


String StdMsg::toString(){

	return  NULL;
}


String StdMsg::WaypointsToString(){

	return  NULL;
}