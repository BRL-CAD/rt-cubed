///////////////////////////////////////////////////////////
//  MessagingSystem.h
//  Implementation of the Class MessagingSystem
//  Created on:      06-Aug-2008 7:50:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(MESSAGINGSYSTEM_H_INCLUDED_)
#define MESSAGINGSYSTEM_H_INCLUDED_

#include "NetID.h"
#include "StdMsg.h"
#include "MessageDispatcher.h"
#include "Portal.h"
#include "MsgStop.h"
#include "SNRoot.h"

class MessagingSystem : public SNRoot
{

public:
	virtual ~MessagingSystem();
	MessagingSystem(String HostName);

	NetID& AddMsgToQueue(StdMsg& msg);
	MessageDispatcher& generateNewMD();
	StdMsg& generateNewMsg(int msgType);
	StdMsg& generateNewMsg(int msgType, String to);
	StdMsg& generateNewMsg(StdMsg& msg);
	StdMsg& generateNewMsg(DataInputStream& in);
	StdMsg& generateNewMsg(std::vector<byte> data);
	std::set<MsgStop> getAllMsgStops();
	std::vector<Portal> getAllPortals();
	std::map<Long, String> getDispatchedMsgs();
	String getHostName();
	int getMsgsRouted();
	std::set<MsgStop> getMsgStops(int msgType);
	Portal& getPortal(String Hostname);
	std::vector<StdMsg> getQ();
	std::vector<String> getRemoteHostNamesArray();
	String getRemoteHostNamesString();
	boolean hasRemoteHostOnFile(String Hostname);
	boolean isQEmpty();
	StdMsg& peekQ();
	StdMsg& pollQ();
	void purgeDispatchedMsgList();
	void RegisterMsgStop(MsgStop& ms);
	boolean& RegisterPortal(Portal& p);
	void UnRegisterMsgStop(MsgStop& ms);
	boolean& UnRegisterPortal(Portal& p);

private:
	//TimeStamp, MS assigned Network ID
	std::map<Long, String> DispatchedMsgs;

	int MDCounter;
	int MsgIDCnt;
	int MsgsRouted;

	//MsgType, List of MsgStops
	std::set<MsgStop> msgStops;

	//MsgType, List of MsgStops
	std::map<int, std::set<MsgStop> > msgTypeRoutingTable;

	//private Hashtable<String, Portal> portals = new Hashtable<String, Portal>();
	std::vector<Portal> portals;
	std::vector<StdMsg> Q;

	StdMsg& generateNewMsgCommon(StdMsg sm);

};
#endif // !defined(MESSAGINGSYSTEM_H_INCLUDED_)
