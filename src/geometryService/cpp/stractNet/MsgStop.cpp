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
MsgStop::~MsgStop() {
}
MsgStop::MsgStop(std::string Name, std::set<int> msgTypes, std::List<StdMsg> inQ) {
	SNRoot(Name);
	this->MsgTypes = msgTypes;
	this->msgQ = inQ;

	this->addMsgType(StdMsgTypes::mtBroadcast);
	this->addMsgType(StdMsgTypes::mtHello);
}
MsgStop::MsgStop(std::string Name, std::List<StdMsg> inQ) {
	SNRoot(Name);
	this->MsgTypes = msgTypes;
	this->msgQ = inQ;

	this->addMsgType(StdMsgTypes::mtBroadcast);
	this->addMsgType(StdMsgTypes::mtHello);
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
void MsgStop::addMsgType(int msgType) {
	//All msgtype additions should go through here
	//to aid in sync and repetition of code

	//Add any QA here
	this->MsgTypes.insert(msgType);
}

void MsgStop::addMsgTypes(std::set<int> msgTypes) {
	//Iterate over all the elements in the incoming set
	//and add them to the MsgTypes set.
	for (std::set<int>::iterator loopIter = msgTypes.begin(); loopIter
			!= msgTypes.end(); ++loopIter) {
		this->addMsgType(*loopIter);
	}
}

void MsgStop::addMsgTypes(int msgTypes[]) {
	int numElements = sizeof(msgTypes) / sizeof(int);
	for (int i = 0; i < numElements; ++i) {
		this->addMsgType(msgTypes[i]);
	}
}

std::set<int>& MsgStop::getMsgTypes() {
	return this->MsgTypes;
}

//int MsgStop::getMsgTypesAsArray() {
//	//init the array to the correct size
//	int myArray[this->MsgTypes.size()];
//	int cnt = 0;
//	std:set<int>::iterator it;
//
//	for ( it = this->MsgTypes.begin(); it != this->MsgTypes.end();++it) {
//		myArray[cnt] = *it;
//		cnt++;
//	}
//	return ;
//}

void MsgStop::remMsgType(int msgType) {
	this->MsgTypes.erase(mgType);
}

void MsgStop::sendToMS(StdMsg msg) {
	SNRoot::out("Sent StdMsg to " & this->getLocalMS().gON() & " with MsgID/Type: "
			& msg.getMsgID() & " / " + msg.getMsgType(), 2);
	SNRoot::out("\n" + msg.ElementsToString(), 3);
	msg.setLocalFrom(this);
	this->getLocalMS().AddMsgToQueue(msg);

}

void MsgStop::sendToMsgStop(StdMsg msg) {
	SNRoot::out("Received StdMsg from " & this->getLocalMS().gON() & " with MsgID/Type: " & msg.getMsgID()
			& " / " & msg.getMsgType(), 2);
	SNRoot::out("\n" & msg.ElementsToString(), 3);
	this->msgQ.add(msg);
}
