package stractNet.messaging;

import java.util.ArrayList;
import java.util.Date;
import java.util.Set;
import java.util.Iterator;

import stractNet.messaging.MessagingSystem;
import stractNet.messaging.MsgStop;
import stractNet.messaging.msgs.StdMsg;
import stractNet.messaging.msgs.StdMsgTypes;
import stractNet.portals.Portal;
import stractNet.SNRoot;
import stractThread.STRunnable;
import stractThread.STUtilities;

public class MessageDispatcher extends SNRoot implements STRunnable {
	private Thread myThread;
	private boolean runStatus = false;
	private boolean runCmd = false;
	public long MsgsProcessed = 0L;

	public MessageDispatcher(String Name, MessagingSystem ms) {
		super(Name);
		this.setLocalMS(ms);
	}


	public void run() {
		this.runStatus = true;
		this.out("Running.", 1);

		// TODO add in functionality to allow User to select FORCEQUIT or
		// QUIT_WHEN_QUEUE_EMPTY
		while (this.runCmd || !this.getLocalMS().isQEmpty()) {

			synchronized (this.getLocalMS().getQ()) {

				this.getLocalMS().getQ().notify();

				if (this.getLocalMS().isQEmpty()) {
					try {
						this.getLocalMS().getQ().wait(50);
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
				}
			}

			if (!this.getLocalMS().isQEmpty()) {
				this.runStatus = true;

				StdMsg msg;

				synchronized (this.getLocalMS()) {
					msg = this.getLocalMS().pollQ();
				}

				if (msg == null) {
					continue;
				}

				// check for echo msgs
				if (CheckDuplicateMsg(msg)) {
					this.err(msg.getMsgID().toString() + " is a duplicate.", 0);
					continue;
				}

				this.MsgsProcessed++;

				if (this.MsgsProcessed % 10000 == 0) {
					this.getLocalMS().purgeDispatchedMsgList();
				}

				this.getLocalMS().getDispatchedMsgs().put(new Date().getTime(),
						msg.getMsgID().toString());

				// Determine Local or Remote
				String destHost = msg.getToHost();
				if (destHost.equals(this.getLocalMS().getHostName())) {
					// LOCAL DELIVERY
					this.deliverLocal(msg);

				} else if (destHost.equals(StdMsgTypes.AllHosts)) {
					// LOCAL AND REMOTE Deliveries.
					this.deliverLocal(msg);
					this.deliverRemote(msg);

				} else {
					// REMOTE DELIVERY
					this.deliverRemote(msg);
				}
			} else {
				STUtilities.pause(25);

			}
			this.runStatus = false;
		}
		this.runStatus = false;
		this.out("Shutdown.", 1);
	}

	private boolean CheckDuplicateMsg(StdMsg msg) {
		return this.getLocalMS().getDispatchedMsgs().containsValue(
				msg.getMsgID().toString());
	}

	private void deliverRemote(StdMsg msg) {
		ArrayList<String> hosts;

		if (msg.getToHost().equals(StdMsgTypes.AllHosts)) {
			// Deliever to EVERYONE on the map

			hosts = this.getLocalMS().getRemoteHostNamesArray();
		} else {
			// just one host
			hosts = new ArrayList<String>();
			hosts.add(msg.getToHost());
		}

		// Now remove any hosts that have already been delivered to.
		ArrayList<WayPoint> wps = msg.getWayPoints();

		for (WayPoint wp : wps) {
			hosts.remove(wp.getHost());
		}

		String sout = "";
		for (String s : hosts) {
			sout += "[" + s + "]";
		}

		if (hosts.size() == 0) {
			this.out("No Remote Hosts qualify for delievery of StdMsg: "
					+ msg.toString(), 2);
			return;
		}

		this.out("Dispatching(Remote) StdMsg with MsgID/Type: "
				+ msg.getMsgID() + " / " + msg.getMsgType() + " to hosts: "
				+ sout, 2);

		for (String s : hosts) {
			Portal p = this.getLocalMS().getPortal(s);

			// COPY it, don't get a new Msg! We need to keep the MsgID intact
			StdMsg msg2 = new StdMsg(msg);

			// msg2.setToHost(s);

			if (p == null) {
				this.err(
						"Undeliverable Msg. Localhost: "
								+ this.getLocalMS().gON()
								+ " doesn't know about Remotehost: "
								+ msg2.getToHost(), 0);
				// TODO add an Undeliverable Msg Queue / System.
				return;
			}

			p.SendToRemHost(msg2);

		}

		return;
	}

	private void deliverLocal(StdMsg msg) {

		int msgType = msg.getMsgType();

		Set<MsgStop> hs = null;

		// get the set of stops for this msg's opcode
		if (msg.getMsgType() == StdMsgTypes.mtBroadcast) {
			// Deliver to ALL stops:
			hs = this.getLocalMS().getAllMsgStops();
		} else {
			// Deliver to specific stops:
			hs = this.getLocalMS().getMsgStops(msgType);
		}

		// Null if there are no stops for this Msg Type!
		if (hs == null) {
			this.out("Unknown MsgType Encountered:".concat(Integer.toString(msg
					.getMsgType())
					+ ""), 0);
			return;
		}

		if (hs.size() == 0) {
			this.out("No Local Stops qualify for delievery of StdMsg: "
					+ msg.toString(), 2);
			return;
		}

		// Iterate through all the stops
		Iterator<MsgStop> it = hs.iterator();
		while (it.hasNext()) {
			// Get the MsgStop
			MsgStop msgstop = it.next();

			if (msgstop == msg.getLocalFrom()) {
				continue;
			}

			this.out("Dispatching(Local) StdMsg with MsgID/Type: "
					+ msg.getMsgID() + " / " + msg.getMsgType()
					+ " to MsgStop: " + msgstop.gON(), 2);
			// Pass It a reference to the Message.
			msgstop.sendToMsgStop(msg);
		}
	}

	/*
	 * Use start() when you want to run this object in a dedicated Thread aka
	 * Non-Blocking.
	 */
	@Override
	public void start() {
		this.out("Received Startup Command.", 1);
		this.runCmd = true;
		this.myThread = new Thread(this, this.gON().concat("-Thread"));
		this.myThread.start();
	}

	@Override
	public Thread getThread() {
		return this.myThread;
	}

	@Override
	public boolean getRunStatus() {
		return this.runStatus;
	}

	@Override
	public void stop() {
		this.out("Received Shutdown Command.", 1);
		this.runCmd = false;
	}

	@Override
	public boolean getRunCmd() {
		return this.runCmd;
	}

}
