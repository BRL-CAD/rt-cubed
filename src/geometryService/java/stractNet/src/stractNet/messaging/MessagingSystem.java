package stractNet.messaging;

import java.io.DataInputStream;
import java.io.IOException;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

import stractNet.messaging.MessageDispatcher;
import stractNet.messaging.MessagingSystem;
import stractNet.messaging.MsgStop;
import stractNet.messaging.msgs.StdMsg;
import stractNet.portals.Portal;
import stractNet.SNRoot;

public class MessagingSystem extends SNRoot {

	private ConcurrentLinkedQueue<StdMsg> Q = null;
	private int MsgIDCnt = 0;
	private int MsgsRouted = 0;

	/**
	 * MsgType, List of MsgStops<BR/><BR/>
	 */
	private HashMap<Integer, HashSet<MsgStop>> msgTypeRoutingTable = null;

	/**
	 * MsgType, List of MsgStops<BR/><BR/>
	 */
	private HashSet<MsgStop> msgStops = null;

	/**
	 * HostName, local Portal Reference<BR/><BR/>
	 */
	// private Hashtable<String, Portal> portals = new Hashtable<String,
	// Portal>();
	private ArrayList<Portal> portals = new ArrayList<Portal>();
	/**
	 * TimeStamp, MS assigned Network ID<BR/><BR/>
	 */
	private HashMap<Long, String> DispatchedMsgs = new HashMap<Long, String>();

	// private MessageDispatcher MD = null;
	private int MDCounter = 0;

	public MessagingSystem(String HostName) {
		super(HostName);
		this.Q = new ConcurrentLinkedQueue<StdMsg>();
		this.msgTypeRoutingTable = new HashMap<Integer, HashSet<MsgStop>>();
		this.msgStops = new HashSet<MsgStop>();
	}

	public String getHostName() {
		return this.gON();
	}

	/*
	 * Message addition, removal and peeking.
	 */

	public boolean isQueueEmpty() {
		synchronized (this.Q) {
			return this.Q.isEmpty();
		}
	}

	public synchronized StdMsg pollQ() {
		synchronized (this.Q) {
			this.MsgsRouted++;
			return this.Q.poll();
		}
	}

	public synchronized StdMsg peekQ() {
		synchronized (this.Q) {
			return this.Q.peek();
		}
	}

	/*
	 * StdMsg Factories
	 */

	public synchronized StdMsg generateNewMsg(int msgType) {
		return generateNewMsgCommon(new StdMsg(msgType));
	}

	public synchronized StdMsg generateNewMsg(int msgType, String to) {
		return generateNewMsgCommon(new StdMsg(msgType, to));
	}

	public synchronized StdMsg generateNewMsg(StdMsg msg) throws IOException {
		return generateNewMsgCommon(new StdMsg(msg));
	}

	public synchronized StdMsg generateNewMsg(DataInputStream in)
			throws IOException {
		return new StdMsg(in); // Don't issue a new MsgID when deserializing!
	}

	public synchronized StdMsg generateNewMsg(byte[] data) throws IOException {
		return new StdMsg(data); // Don't issue a new MsgID when deserializing!
	}

	private synchronized StdMsg generateNewMsgCommon(StdMsg sm) {
		this.MsgIDCnt++;
		sm.setMsgID(new NetID(this.MsgIDCnt, this.getHostName()));
		sm.setFromHost(this.getHostName());

		this.out("Issued new StdMsg with MsgID of: " + sm.getMsgID(), 2);

		return sm;
	}

	public synchronized NetID AddMsgToQueue(StdMsg msg) {
		msg.StampWayPoint(this.gON());
		this.out("Recieved StdMsg with MsgID/Type: " + msg.getMsgID() + " / "
				+ msg.getMsgType(), 2);
		this.out("Details:\n\t" + msg.toString() + "\n"
				+ msg.ElementsToString(), 3);
		synchronized (this.Q) {
			this.Q.add(msg);
			this.Q.notify();
		}
		return new NetID(msg.getMsgID());
	}

	public ConcurrentLinkedQueue<StdMsg> getQ() {
		return Q;
	}

	/*
	 * Portal Utilities.
	 */
	public Portal getPortal(String Hostname) {
		synchronized (this.portals) {
			for (Portal p : this.portals) {
				if (p.getRemoteHostName().equals(Hostname)) {
					return p;
				}
			}
		}
		return null;
	}

	public boolean hasRemoteHostOnFile(String Hostname) {
		if (this.getPortal(Hostname) == null) {
			return false;
		} else {
			return true;
		}
	}

	public synchronized ArrayList<Portal> getAllPortals() {
		return this.portals;
	}

	public synchronized String getRemoteHostNamesString() {
		String sout = "";
		synchronized (this.portals) {
			for (Portal p : this.portals) {
				sout += "[" + p.getRemoteHostName() + "]";
			}
		}
		return sout;
	}

	public synchronized ArrayList<String> getRemoteHostNamesArray() {
		ArrayList<String> sout = new ArrayList<String>();
		synchronized (this.portals) {
			for (Portal p : this.portals) {
				sout.add(p.getRemoteHostName());
			}
		}
		return sout;
	}

	public boolean RegisterPortal(Portal p) {

		synchronized (this.portals) {
			// String RemHostName = new String(p.getRemoteHostName());

			this.out("Recieved Registration Request for remote Portal: "
					+ p.getRemoteHostName(), 2);

			if (this.portals.contains(p) == false) {
				// No entry for RemHostName
				this.portals.add(p);
				return true;
			} else {
				this.err("Warning: Remote Hostname already Registered", 0);
				return false;
			}
		}
	}

	public boolean UnRegisterPortal(Portal p) {
		if (p == null) {
			return false;
		}
		
		this.out("Recieved UnRegistration Request for remote Portal: "
				+ p.getRemoteHostName(), 2);

		synchronized (this.portals) {
			return this.portals.remove(p);
		}
	}

	/*
	 * MsgStop Utilities.
	 */

	public synchronized HashSet<MsgStop> getMsgStops(int msgType) {
		return this.msgTypeRoutingTable.get(msgType);
	}

	public synchronized HashSet<MsgStop> getAllMsgStops() {
		return this.msgStops;
	}

	public synchronized void RegisterMsgStop(MsgStop ms) {
		this.out("Recieved Registration Request for MsgStop: " + ms.gON(), 2);

		// Add to master MsgStop HashSet
		this.msgStops.add(ms);

		// Get msgTypes for this stop.
		HashSet<Integer> msgTypes = ms.getMsgTypesHashSet();

		// Iterate though them.
		for (int type : msgTypes) {
			// Pull the routing table reference for this MsgType
			HashSet<MsgStop> hs = this.msgTypeRoutingTable.get(type);

			// Check to see if there is one.
			if (hs != null) {
				// if yes, add to the HashSet of MsgStops
				hs.add(ms);
			} else {
				// if not, make a new HashSet<MsgStop>
				hs = new HashSet<MsgStop>();
				// add the stop
				hs.add(ms);
				// then add the New Hashset to the Routing table using msgType
				// as key.
				this.msgTypeRoutingTable.put(type, hs);
			}
		}

		return;
	}

	public synchronized void UnRegisterMsgStop(MsgStop ms) {
		this.out("Recieved UnRegistration Request for MsgStop: " + ms.gON(), 2);

		this.msgStops.remove(ms);

		// Get the set of existing msgTypes on the Entire Routing Table
		Set<Integer> msgTypes = this.msgTypeRoutingTable.keySet();

		for (int type : msgTypes) {
			// For each type, get the reference to the HashSet of MsgStop IDs
			HashSet<MsgStop> hs = this.msgTypeRoutingTable.get(type);
			if (hs != null) {
				// remove the ms from the HashSet
				hs.remove(ms);
			}
		}

		return;
	}

	/*
	 * 
	 * Message Dispatcher Routines
	 */

	public MessageDispatcher generateNewMD() {
		this.MDCounter++;
		return new MessageDispatcher(this.gON() + "MsgDisp-" + this.MDCounter,
				this);
	}

	public void purgeDispatchedMsgList() {

		ArrayList<Long> toDel = null;
		long cutoff;
		// FIXME there is a synchronization issue here.
		synchronized (this.DispatchedMsgs) {
			cutoff = new Date().getTime() - 60000L; // 600000 = 1 min

			toDel = new ArrayList<Long>();

			for (long l : this.DispatchedMsgs.keySet()) {
				if (l < cutoff) {
					toDel.add(l);
				}
			}
		}
		synchronized (this.DispatchedMsgs) {
			for (long l : toDel) {
				this.DispatchedMsgs.remove(l);
			}
			// this.out("Purged Dispatch History: (" + before + " -> "
			// + this.DispatchedMsgs.size() + ")", 2);
		}

	}

	public int getMsgsRouted() {
		return MsgsRouted;
	}

	public synchronized HashMap<Long, String> getDispatchedMsgs() {
		return DispatchedMsgs;
	}

}
