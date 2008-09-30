///////////////////////////////////////////////////////////
//  MsgStop.cpp
//  Implementation of the Class MsgStop
//  Created on:      06-Aug-2008 7:51:11 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////
#include "MsgStop.h"

///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
MsgStop::~MsgStop(){}
MsgStop::MsgStop(std::string Name, std::Set<Integer> msgTypes, std::List<StdMsg> inQ){
	SNRoot(Name);
	this->MsgTypes = msgTypes;
	this->msgQ = inQ;

	this->addMsgType(StdMsgTypes::mtBroadcast);
	this->addMsgType(StdMsgTypes::mtHello);
}
MsgStop::MsgStop(std::string Name, std::List<StdMsg> inQ){
	SNRoot(Name);
	this->MsgTypes = msgTypes;
	this->msgQ = inQ;

	this->addMsgType(StdMsgTypes::mtBroadcast);
	this->addMsgType(StdMsgTypes::mtHello);

}


void MsgStop::addMsgType(int msgType){

}

 void addMsgTypes(std::Set<Integer> msgTypes) {

 }


void MsgStop::addMsgTypes(int msgTypes[]){

}


std::Set<Integer> MsgStop::getMsgTypesSet(){
	return  NULL;
}


int MsgStop::getMsgTypesIntArray(){

	return 0;
}


void MsgStop::remMsgType(int msgType){

}


void MsgStop::sendToMS(StdMsg msg){

}


void MsgStop::sendToMsgStop(StdMsg msg){

}
