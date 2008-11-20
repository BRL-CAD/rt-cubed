package stractNet.messaging;

/*
 * Meant to be an Aggragate class.
 */

import java.util.LinkedList;
import java.util.HashSet;
import stractNet.messaging.msgs.StdMsg;
import stractNet.messaging.msgs.StdMsgTypes;
import stractNet.SNRoot;
import java.util.Iterator;

public class MsgStop extends SNRoot {

	// This is a reference to the Queue for messages coming FROM the MS to the
	// destined MsgStop
	private LinkedList<StdMsg> msgQ = null;
	private HashSet<Integer> MsgTypes;

	public MsgStop(String Name, HashSet<Integer> msgTypes,
			LinkedList<StdMsg> inQ) {
		super(Name);
		this.MsgTypes = msgTypes;
		this.msgQ = inQ;
		
		this.addMsgType(StdMsgTypes.mtBroadcast);
		this.addMsgType(StdMsgTypes.mtHello);
	}
	
	

	public MsgStop(String Name, LinkedList<StdMsg> inQ) {
		this(Name, new HashSet<Integer>(), inQ);
	}

	public void sendToMsgStop(StdMsg msg) {
		synchronized (this.msgQ) {
			this.out("Recieved StdMsg from " + this.getLocalMS().gON() + " with MsgID/Type: " + msg.getMsgID()
					+ " / " + msg.getMsgType(), 2);
			this.out("\n" + msg.ElementsToString(), 3);
			this.msgQ.add(msg);
			this.msgQ.notify();			
		}
	}
	
	

	public void sendToMS(StdMsg msg) {
		this.out("Sent StdMsg to " + this.getLocalMS().gON() + " with MsgID/Type: " + msg.getMsgID()
				+ " / " + msg.getMsgType(), 2);
		this.out("\n" + msg.ElementsToString(), 3);
		msg.setLocalFrom(this);
		this.getLocalMS().AddMsgToQueue(msg);
	}
	
	public HashSet<Integer> getMsgTypesHashSet() {
		return MsgTypes;
	}

	public int[] getMsgTypesIntArray() {

		Iterator<Integer> it = this.MsgTypes.iterator();
		int[] mts = new int[this.MsgTypes.size()];

		for (int i = 0; i < this.MsgTypes.size(); i++) {
			mts[i] = it.next();
		}

		return mts;
	}

	public void addMsgType(int msgType) {
		MsgTypes.add(msgType);
	}

//	public void addMsgTypes(HashSet<Integer> msgTypes) {
//		MsgTypes.addAll(MsgTypes);
//	}

	public void addMsgTypes(int[] msgTypes) {
		for (int t : msgTypes) {
			this.addMsgType(t);
		}
	}

	public void remMsgType(int msgType) {
		MsgTypes.remove(msgType);
	}


}
