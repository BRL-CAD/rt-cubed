///////////////////////////////////////////////////////////
//  NetMsgActionDefManager.cxx
//  Implementation of the Class NetMsgActionDefManager
//  Created on:      04-Dec-2008 8:26:45 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#include "NetMsgActionDefManager.h"

NetMsgActionDefManager::NetMsgActionDefManager() {

}

NetMsgActionDefManager::~NetMsgActionDefManager() {

}

void NetMsgActionDefManager::registerNetMsgActionDef(
		AbstractNetMsgActionDef& def) {

}

int NetMsgActionDefManager::unregisterNetMsgActionDef(
		AbstractNetMsgActionDef& def) {

	return 0;
}

AbstractNetMsgActionDef& NetMsgActionDefManager::unregisterNetMsgActionDef(
		int msgType) {

	return NULL;
}

AbstractNetMsgActionDef& NetMsgActionDefManager::getNetMsgActionDef(int msgType) {

	return NULL;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
