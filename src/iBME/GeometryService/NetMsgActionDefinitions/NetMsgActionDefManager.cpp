///////////////////////////////////////////////////////////
//  NetMsgActionDefManager.cpp
//  Implementation of the Class NetMsgActionDefManager
//  Created on:      20-Nov-2008 8:00:16 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "NetMsgActionDefManager.h"


NetMsgActionDefManager::NetMsgActionDefManager(){

}



NetMsgActionDefManager::~NetMsgActionDefManager(){

}





void NetMsgActionDefManager::registerNetMsgActionDef(AbstractNetMsgActionDef def){

}


int NetMsgActionDefManager::unregisterNetMsgActionDef(AbstractNetMsgActionDef def){

	return 0;
}


AbstractNetMsgActionDef NetMsgActionDefManager::unregisterNetMsgActionDef(int msgType){

	return  NULL;
}


AbstractNetMsgActionDef NetMsgActionDefManager::getNetMsgActionDef(int msgType){

	return  NULL;
}