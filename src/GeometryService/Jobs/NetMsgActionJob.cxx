///////////////////////////////////////////////////////////
//  NetMsgActionJob.cxx
//  Implementation of the Class NetMsgActionJob
//  Created on:      04-Dec-2008 8:26:45 AM
//  Original author: Dave Loman
///////////////////////////////////////////////////////////

#include "GeometryService/Jobs/NetMsgActionJob.h"

NetMsgActionJob::NetMsgActionJob() {
}

NetMsgActionJob::~NetMsgActionJob() {
}

/**
 * Constructor
 */
NetMsgActionJob::NetMsgActionJob(NetMsg& msg) {
}

/**
 * 1) Performs lookup on NetMsgActionDefManager.actionDefs map
 * 2) Calls AbstractNetMsgActionDef.convert(NetMsg)
 * 3) Obtains reference to AbstractPortal of NetMsg's origin from
 * CommunicationsManager.portals map.
 */
bool NetMsgActionJob::doJob() {
	return false;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
