package stractNet.messaging.tests;

import stractNet.messaging.*;
import stractNet.*;
import stractNet.messaging.msgs.*;
import stractThread.*;

import java.util.*;

public class PlaceboMsgStoppableClass extends SNRoot implements STRunnable {

	private int MSGsToSend;
	private int MSGsSent;
	private long lDelay;
	private MsgStop myMsgStop = null;
	private Thread myThread = null;
	private boolean runStatus = false;
	private boolean runCmd = false;
	private LinkedList<StdMsg> inbox = null;

	public PlaceboMsgStoppableClass(String Name, int msgsToSend, long delay) {
		this(Name, msgsToSend, delay, SNRoot.getGlobalMS());
	}

	public PlaceboMsgStoppableClass(String Name, int msgsToSend, long delay,
			MessagingSystem ms) {
		super(Name);
		this.setLocalMS(ms);
		this.inbox = new LinkedList<StdMsg>();
		this.MSGsToSend = msgsToSend;
		this.lDelay = delay;
		this.myMsgStop = new MsgStop(this.gON() + "-MsgStop", inbox);
		this.myMsgStop.setLocalMS(ms);
		this.myMsgStop.sON(this.gON() + "-MsgStop");
	}

	@Override
	public void run() {
		this.runStatus = true;
		this.out("Running.", 1);

		STUtilities.pause(this.lDelay);

		// Use the MsgTypes on this MsgStop as the Basis for a random draw of
		// MsgType.
		int[] mts = this.myMsgStop.getMsgTypesIntArray();
		int numMsgTypes = mts.length;

		while (this.runCmd) {
			this.runStatus = true;
			
			
			while ((this.MSGsSent < this.MSGsToSend) || (!this.inbox.isEmpty())) {

				if (!this.inbox.isEmpty()) {
					synchronized (this.inbox) {
						@SuppressWarnings("unused")
						StdMsg sm1 = this.inbox.poll();
//						System.out.println("\n\n\n\n\n\n\n");
//						System.out.println(sm1.WaypointsToString());
//						System.out.println("\n\n\n\n\n\n\n");
						
					}
				}

				if (this.MSGsSent < this.MSGsToSend) {
					StdMsg msg = StdMsgUtil.RandGenMsgFactory(this.getLocalMS());
//					msg.AddElement(new StringFrag("The quick brown fox jumps over the lazy dog"));

					
//					msg.AddElement(new StringFrag("The quick brown fox jumps over the lazy dog"));
//					msg.AddElement(new StringFrag("The quick brown fox jumps over the lazy dog"));
//					msg.AddElement(new StringFrag("The quick brown fox jumps over the lazy dog"));


					msg.setLocalMS(this.getLocalMS());
					int rmi = new Random().nextInt(numMsgTypes - 1);
					msg.setMsgType(mts[rmi]);

					msg.setToHost(StdMsgTypes.AllHosts);

					this.out("Sending StdMsg with MsgID/Type: " + msg.getMsgID()
							+ " / " + msg.getMsgType(), 2);
					this.myMsgStop.sendToMS(msg);

					MSGsSent++;

				}
				STUtilities.pause(this.lDelay);
				
			}
			this.runStatus = false;

			try {
				synchronized(this.inbox) {
					this.inbox.wait(100);
				}
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		this.out("Shutdown.", 1);
	}

	public void start() {
		this.out("Received Startup Command.", 1);
		this.runCmd = true;
		this.runStatus = true;
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
	public boolean getRunCmd() {
		return this.runCmd;
	}

	@Override
	public void stop() {
		this.out("Received Shutdown Command.", 1);
		this.runCmd = false;

		synchronized(this.inbox) {
			this.inbox.notify();
		}
	}

	public MsgStop getMsgStop() {
		return this.myMsgStop;
	}

	public void SendMoreMsgs(int i) {
		System.out.println();
		this.out("Issuing " + i + " more messages", 2);
		this.MSGsToSend += i;
//		synchronized(this.inbox) {
//			this.inbox.notify();
//		}

	}

}
