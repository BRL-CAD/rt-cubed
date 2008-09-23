///////////////////////////////////////////////////////////
//  MessageDispatcher.cpp
//  Implementation of the Class MessageDispatcher
//  Created on:      06-Aug-2008 7:49:34 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "MessageDispatcher.h"

///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////

MessageDispatcher::~MessageDispatcher() {
}

MessageDispatcher::MessageDispatcher(std::string Name, MessagingSystem& ms) :
	SNRoot(Name) {
	SNRoot::setLocalMS(ms);
}

boolean MessageDispatcher::CheckDuplicateMsg(StdMsg& msg) {
	return this->getLocalMS().getDispatchedMsgs().containsValue(
			msg.getMsgID().tostd::string());
}

void MessageDispatcher::deliverLocal(StdMsg& msg) {

	int msgType = msg.getMsgType();

	std::set<MsgStop> msgStopSet = null;

	// get the set of stops for this msg's opcode
	if (msg.getMsgType() == StdMsgTypes::mtBroadcast) {
		// Deliver to ALL stops:
		msgStopSet = this->getLocalMS().getAllMsgStops();
	} else {
		// Deliver to specific stops:
		msgStopSet = this->getLocalMS().getMsgStops(msgType);
	}

	// Null if there are no stops for this Msg Type!
	if (msgStopSet == null) {
		//TODO is itos() going to be a problem?!? Not an ANSI-C Standard
		SNRoot::out("Unknown MsgType Encountered:" + itos(msg.getMsgType())
				+ "");

		//TODO put the message into an undeliverable queue
		//TODO But for now, destruct the msg and free the memory
		return;
	}

	if (msgStopSet.size() == 0) {
		if (SNRoot::VerbosityLevel >= 2) {
			SNRoot::out("No Local Stops qualify for delivery of StdMsg: "
					+ msg.tostd::string());
		}
		return;
	}

	// Iterate through all the stops
	Set<MsgStop>::const_iterator it = msgStopSet.begin();

	for (it = msgStopSet.begin(); it != msgStopSet.end(); it++) {
		cout << *it << endl;

		MsgStop msgstop = *it;

		if (msgstop == msg.getLocalFrom()) {//TODO Need to implement the == operator in MsgStop
			continue;
		}

		if (SNRoot::VerbosityLevel >= 2) {
			SNRoot::out("Dispatching(Local) StdMsg with MsgID/Type: "
					+ msg.getMsgID() + " / " + msg.getMsgType()
					+ " to MsgStop: " + msgstop.gON());
		}

		// Pass the MsgStop a reference to the Message.
		msgstop.sendToMsgStop(msg);
	}

}

void MessageDispatcher::deliverRemote(StdMsg& msg) {
	list<std::string> hosts;

	if (msg.getToHost().equals(StdMsgTypes.AllHosts)) {
		// Deliver to EVERYONE on the map

		hosts = this.getLocalMS().getRemoteHostNamesArray();
	} else {
		// just one host

		hosts.add(msg.getToHost());
	}

	// Now remove any hosts that have already been delivered to.
	list<WayPoint> wps = msg.getWayPoints();
	list<WayPoint>::const_iterator itw;

	for (itw = wps.begin(); itw != wps.end(); itw++) {
		algorithm::remove(hosts.begin(), hosts.end(), *itw.getHost());
	}

	std::string sout = "";
	list<std::string>::const_iterator its;
	for (its = hosts.begin(); its != hosts.end(); its++) {
		sout += "[" + *its + "]";
	}

	if (hosts.size() == 0) {
		if (SNRoot::VerbosityLevel >= 2) {
			SNRoot::out("No Remote Hosts qualify for delivery of StdMsg: "
					+ msg.tostd::string());
		}
		return;
	}

	if (SNRoot::VerbosityLevel >= 2) {
		SNRoot::out("Dispatching(Remote) StdMsg with MsgID/Type: "
				+ msg.getMsgID() + " / " + msg.getMsgType() + " to hosts: "
				+ sout);
	}

	for (its = hosts.begin(); its != hosts.end(); its++) {
		Portal p = this->getLocalMS().getPortal(*its);

		// COPY it, don't get a new Msg! We need to keep the MsgID intact for echo/dup Msg Detection
		StdMsg msg2 = new StdMsg(msg);

		//TODO fix the logic here.
		if (p == null) {
			SNRoot::err("Undeliverable Msg. Localhost: " + this->getLocalMS().gON()
					+ " doesn't know about Remotehost: " + msg2.getToHost());

			// TODO add an Undeliverable Msg Queue / System.
			return;
		}

		p.SendToRemHost(msg2);

	}

}

void MessageDispatcher::run() {
	STRunnableI::runStatus = true; //TODO Encapsulate
	if (SNRoot::VerbosityLevel >= 1) {
		SNRoot::out("Running.");
	}

	// TODO add in functionality to allow User to select FORCEQUIT or
	// QUIT_WHEN_QUEUE_EMPTY
	while (STRunnableI::runCmd || !this->getLocalMS().isQEmpty()) {//TODO Encapsulate

		//Synch on this->getLocalMS().getQ()
		if (this->getLocalMS().isQEmpty()) {
			this->getLocalMS().getQ().wait(50); //This is the thread sleep point
		}
		//EndSynch

		if (!this->getLocalMS().isQEmpty()) {
			this->runStatus = true;

			StdMsg msg;

			//Synch on this->getLocalMS()
			msg = this->getLocalMS().pollQ();
			//EndSynch

			if (msg == null) {
				continue;
			}

			// check for echo StdMsg
			if (CheckDuplicateMsg(msg)) {
				SNRoot::err(
						msg.getMsgID().tostd::string() + " is a duplicate.", 0);
				continue;
			}

			this->MsgsProcessed++;

			//TODO Put a bit more logic into the purging of the DispatchedMsg list!
			if (this->MsgsProcessed % 10000 == 0) {
				this->getLocalMS().purgeDispatchedMsgList();
			}

			//LOG the dispatched messageID and time onto the MAP
			this->getLocalMS().getDispatchedMsgs().put(new Date().getTime(),
					msg.getMsgID().tostd::string());

			// Determine Local or Remote
			std::::string destHost = msg.getToHost();
			if (destHost == this->getLocalMS().getHostName()) {
				// LOCAL DELIVERY
				this->deliverLocal(msg);

			} else if (destHost == StdMsgTypes::AllHosts) {
				// LOCAL AND REMOTE Deliveries.
				this->deliverLocal(msg);
				this->deliverRemote(msg);

			} else {
				// REMOTE DELIVERY
				this->deliverRemote(msg);
			}
		} else {
			STUtilities::pause(25);

		}
		this->runStatus = false;//TODO Encapsulate
	}
	this->runStatus = false;//TODO Encapsulate
	if (SNRoot::VerbosityLevel >=1 ) {SNRoot::out("Shutdown.");}
}

void MessageDispatcher::start() {
	if (SNRoot::VerbosityLevel >= 1) {
		SNRoot::out("Received Startup Command");
	}
	STRunnableI::runCmd = true; //TODO Encapsulate
	Thread STRunnableI::myThread;
	STRunnableI::myThread.start();
}

void MessageDispatcher::stop() {
	if (SNRoot::VerbosityLevel >= 1) {
		SNRoot::out("Received Shutdown Command");
	}
	STRunnableI::runCmd = false; //TODO Encapsulate
}

//TODO if STRunnableI becomes a NON purely Virtual, will we need these Delegates?
boolean MessageDispatcher::getRunCmd() {
	return STRunnableI::runCmd;
}
boolean MessageDispatcher::getRunStatus() {
	return STRunnableI::runStatus;
}
Thread& MessageDispatcher::getThread() {
	return STRunnableI::myThread;
}
