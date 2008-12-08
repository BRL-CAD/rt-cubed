///////////////////////////////////////////////////////////
//  NetMsgActionJob.cpp
//  Implementation of the Class NetMsgActionJob
//  Created on:      04-Dec-2008 8:26:45 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "NetMsgActionJob.h"


NetMsgActionJob::NetMsgActionJob(){

}



NetMsgActionJob::~NetMsgActionJob(){

}





/**
 * Constructor
 */
void NetMsgActionJob::NetMsgActionJob(NetMsg& msg){

}


/**
 * 1) Performs lookup on NetMsgActionDefManager.actionDefs map
 * 2) Calls AbstractNetMsgActionDef.convert(NetMsg)
 * 3) Obtains reference to AbstractPortal of NetMsg's origin from
 * CommunicationsManager.portals map.
 */
bool NetMsgActionJob::doJob(){

	return false;
}