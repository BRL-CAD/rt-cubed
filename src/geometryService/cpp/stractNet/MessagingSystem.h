///////////////////////////////////////////////////////////
//  MessagingSystem.h
//  Implementation of the Class MessagingSystem
//  Created on:      06-Aug-2008 7:50:12 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_597FB80E_BE25_471e_A681_E1E6E605229C__INCLUDED_)
#define EA_597FB80E_BE25_471e_A681_E1E6E605229C__INCLUDED_

#include "NetID.h"
#include "StdMsg.h"
#include "MessageDispatcher.h"
#include "Portal.h"
#include "MsgStop.h"
#include "SNRoot.h"

class MessagingSystem : public SNRoot
{

public:
	MessagingSystem();
	virtual ~MessagingSystem();

	MessagingSystem(String HostName);
	NetID AddMsgToQueue(StdMsg msg);
	MessageDispatcher generateNewMD();
	StdMsg generateNewMsg(int msgType);
	StdMsg generateNewMsg(int msgType, String to);
	StdMsg generateNewMsg(StdMsg msg) throw IOException;
	StdMsg generateNewMsg(DataInputStream in) throw IOException;
	StdMsg generateNewMsg(byte[] data) throw IOException;
	HashSet<MsgStop> getAllMsgStops();
	ArrayList<Portal> getAllPortals();
	HashMap<Long, String> getDispatchedMsgs();
	String getHostName();
	int getMsgsRouted();
	HashSet<MsgStop> getMsgStops(int msgType);
	Portal getPortal(String Hostname);
	ConcurrentLinkedQueue<StdMsg> getQ();
	ArrayList<String> getRemoteHostNamesArray();
	String getRemoteHostNamesString();
	boolean hasRemoteHostOnFile(String Hostname);
	boolean isQEmpty();
	StdMsg peekQ();
	StdMsg pollQ();
	void purgeDispatchedMsgList();
	void RegisterMsgStop(MsgStop ms);
	boolean RegisterPortal(Portal p);
	void UnRegisterMsgStop(MsgStop ms);
	boolean UnRegisterPortal(Portal p);

private:
	/**
	 * TimeStamp, MS assigned Network ID<BR/><BR/>
	 */
	HashMap<Long, String> DispatchedMsgs;
	/**
	 * private MessageDispatcher MD = null;
	 */
	int MDCounter;
	int MsgIDCnt;
	int MsgsRouted;
	/**
	 * MsgType, List of MsgStops<BR/><BR/>
	 */
	HashSet<MsgStop> msgStops;
	/**
	 * MsgType, List of MsgStops<BR/><BR/>
	 */
	HashMap<Integer, HashSet<MsgStop>> msgTypeRoutingTable;
	/**
	 * private Hashtable<String, Portal> portals = new Hashtable<String, Portal>();
	 */
	ArrayList<Portal> portals;
	ConcurrentLinkedQueue<StdMsg> Q;

	StdMsg generateNewMsgCommon(StdMsg sm);

};
#endif // !defined(EA_597FB80E_BE25_471e_A681_E1E6E605229C__INCLUDED_)
