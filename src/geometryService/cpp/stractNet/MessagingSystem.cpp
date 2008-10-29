///////////////////////////////////////////////////////////
//  MessagingSystem.cpp
//  Implementation of the Class MessagingSystem
//  Created on:      06-Aug-2008 7:50:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "MessagingSystem.h"
///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////
MessagingSystem::~MessagingSystem(){

}
MessagingSystem::MessagingSystem(String HostName){
	SNRoot(HostName);
	this->Q = std::vector<StdMsg>();
	this->msgTypeRoutingTable = std::map<int, std::set<MsgStop>>();
	this->msgStops = std::set<MsgStop>();
}
///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////
NetID& MessagingSystem::AddMsgToQueue(StdMsg& msg){
	msg.StampWayPoint(this->gON());
	this->Q.push_back(msg);
	return NetID(msg.getMsgID();
}


/**
 * Message Dispatcher Routines
 */
MessageDispatcher& MessagingSystem::generateNewMD(){

	return  NULL;
}


/**
 * StdMsg Factories
 */
StdMsg& MessagingSystem::generateNewMsg(int msgType){

	return  NULL;
}


StdMsg& MessagingSystem::generateNewMsg(int msgType, String to){

	return  NULL;
}


StdMsg& MessagingSystem::generateNewMsg(StdMsg& msg){

	return  NULL;
}


StdMsg& MessagingSystem::generateNewMsg(DataInputStream& in) {

	return  NULL;
}


StdMsg& MessagingSystem::generateNewMsg(std::vector<byte> data){

	return  NULL;
}


StdMsg& MessagingSystem::generateNewMsgCommon(StdMsg& sm){

	return  NULL;
}


std::set<MsgStop> MessagingSystem::getAllMsgStops(){

	return  NULL;
}


std::vector<Portal> MessagingSystem::getAllPortals(){

	return  NULL;
}


std::map<Long, String> MessagingSystem::getDispatchedMsgs(){

	return DispatchedMsgs;
}


String MessagingSystem::getHostName(){

	return  NULL;
}


int MessagingSystem::getMsgsRouted(){

	return MsgsRouted;
}


/**
 * MsgStop Utilities.
 */
std::set<MsgStop> MessagingSystem::getMsgStops(int msgType){

	return  NULL;
}


/**
 * Portal Utilities.
 */
Portal& MessagingSystem::getPortal(String Hostname){

	return  NULL;
}


std::vector<StdMsg> MessagingSystem::getQ(){

	return Q;
}


std::vector<String> MessagingSystem::getRemoteHostNamesArray(){

	return  NULL;
}


String MessagingSystem::getRemoteHostNamesString(){

	return  NULL;
}


boolean MessagingSystem::hasRemoteHostOnFile(String Hostname){

	return  NULL;
}


/**
 * Message addition, removal and peeking.
 */
boolean MessagingSystem::isQEmpty(){

	return  NULL;
}


StdMsg& MessagingSystem::peekQ(){

	return  NULL;
}


StdMsg& MessagingSystem::pollQ(){

	return  NULL;
}


void MessagingSystem::purgeDispatchedMsgList(){

}


void MessagingSystem::RegisterMsgStop(MsgStop& ms){

}


boolean MessagingSystem::RegisterPortal(Portal& p){

	return  NULL;
}


void MessagingSystem::UnRegisterMsgStop(MsgStop& ms){

}


boolean MessagingSystem::UnRegisterPortal(Portal& p){

	return  NULL;
}
