///////////////////////////////////////////////////////////
//  MessagingSystem.cpp
//  Implementation of the Class MessagingSystem
//  Created on:      06-Aug-2008 7:50:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "MessagingSystem.h"


MessagingSystem::MessagingSystem(){

}



MessagingSystem::~MessagingSystem(){

}





MessagingSystem::MessagingSystem(String HostName){

}


NetID MessagingSystem::AddMsgToQueue(StdMsg msg){

	return  NULL;
}


/**
 * Message Dispatcher Routines
 */
MessageDispatcher MessagingSystem::generateNewMD(){

	return  NULL;
}


/**
 * StdMsg Factories
 */
StdMsg MessagingSystem::generateNewMsg(int msgType){

	return  NULL;
}


StdMsg MessagingSystem::generateNewMsg(int msgType, String to){

	return  NULL;
}


StdMsg MessagingSystem::generateNewMsg(StdMsg msg) throw IOException{

	return  NULL;
}


StdMsg MessagingSystem::generateNewMsg(DataInputStream in) throw IOException{

	return  NULL;
}


StdMsg MessagingSystem::generateNewMsg(byte[] data) throw IOException{

	return  NULL;
}


StdMsg MessagingSystem::generateNewMsgCommon(StdMsg sm){

	return  NULL;
}


HashSet<MsgStop> MessagingSystem::getAllMsgStops(){

	return  NULL;
}


ArrayList<Portal> MessagingSystem::getAllPortals(){

	return  NULL;
}


HashMap<Long, String> MessagingSystem::getDispatchedMsgs(){

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
HashSet<MsgStop> MessagingSystem::getMsgStops(int msgType){

	return  NULL;
}


/**
 * Portal Utilities.
 */
Portal MessagingSystem::getPortal(String Hostname){

	return  NULL;
}


ConcurrentLinkedQueue<StdMsg> MessagingSystem::getQ(){

	return Q;
}


ArrayList<String> MessagingSystem::getRemoteHostNamesArray(){

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


StdMsg MessagingSystem::peekQ(){

	return  NULL;
}


StdMsg MessagingSystem::pollQ(){

	return  NULL;
}


void MessagingSystem::purgeDispatchedMsgList(){

}


void MessagingSystem::RegisterMsgStop(MsgStop ms){

}


boolean MessagingSystem::RegisterPortal(Portal p){

	return  NULL;
}


void MessagingSystem::UnRegisterMsgStop(MsgStop ms){

}


boolean MessagingSystem::UnRegisterPortal(Portal p){

	return  NULL;
}