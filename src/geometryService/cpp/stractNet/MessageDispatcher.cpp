///////////////////////////////////////////////////////////
//  MessageDispatcher.cpp
//  Implementation of the Class MessageDispatcher
//  Created on:      06-Aug-2008 7:49:34 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "MessageDispatcher.h"


MessageDispatcher::MessageDispatcher(){

}



MessageDispatcher::~MessageDispatcher(){

}





MessageDispatcher::MessageDispatcher(String Name, MessagingSystem ms){

}


MessageDispatcher::MessageDispatcher(String Name){

}


boolean MessageDispatcher::CheckDuplicateMsg(StdMsg msg){

	return  NULL;
}


void MessageDispatcher::deliverLocal(StdMsg msg){

}


void MessageDispatcher::deliverRemote(StdMsg msg){

}


boolean MessageDispatcher::getRunCmd(){

	return  NULL;
}


boolean MessageDispatcher::getRunStatus(){

	return  NULL;
}


Thread MessageDispatcher::getThread(){

	return  NULL;
}


void MessageDispatcher::run(){

}


/**
 * Use start() when you want to run this object in a dedicated Thread aka Non-
 * Blocking.
 */
void MessageDispatcher::start(){

}


void MessageDispatcher::stop(){

}