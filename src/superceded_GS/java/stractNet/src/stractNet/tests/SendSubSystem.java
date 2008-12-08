package stractNet.tests;

/*
 * 
 * MsgStop that sends one message, then monitors it's inbox and displays any recieved Messages.
 * 
 * 
 */




import java.util.LinkedList;
import stractNet.messaging.MessagingSystem;
import stractNet.messaging.MsgStop;
import stractNet.messaging.msgs.StdMsg;
import stractNet.messaging.msgs.StdMsgTypes;
import stractNet.messaging.msgs.frags.StringFrag;
import stractThread.STRunnable;
import stractThread.STUtilities;

public class SendSubSystem extends TestAppCore implements STRunnable {
	private MsgStop myMsgStop = null;
	private Thread myThread = null;
	private boolean runStatus = false;
	private boolean runCmd = false;
	private LinkedList<StdMsg> inbox = null;
	private long MAXSLEEP = 0L;
	private long MINSLEEP = 0L;

	public SendSubSystem(String Name, MessagingSystem ms, int[] msgTypes,
			long MinDelay, long MaxDelay) {
		super(Name, ms);
		this.inbox = new LinkedList<StdMsg>();

		this.myMsgStop = new MsgStop(this.gON() + "-MsgStop", inbox);
		this.myMsgStop.addMsgTypes(msgTypes);
		this.myMsgStop.setLocalMS(ms);
		this.MINSLEEP = MinDelay;
		this.MAXSLEEP = MaxDelay;
	}

	@Override
	public void run() {
		this.runStatus = true;
		this.out("Running.");

		// random Delay
		long delay = (long) ((Math.random() * (this.MAXSLEEP - this.MINSLEEP)) + this.MINSLEEP);
		this.out("Pausing for " + delay / 1000.0f + " Seconds.");
		STUtilities.pause(delay);

		// Send initial message.

		StdMsg msgOut = this.getMs().generateNewMsg(StdMsgTypes.mtBroadcast,
				StdMsgTypes.AllHosts);
		msgOut.AddElement(new StringFrag("Why, Hello there!"));
		this.out("Sending StdMsg: " + msgOut.toString());
		this.myMsgStop.sendToMS(msgOut);

		while (this.runCmd) {
			this.runStatus = true;

			// clean out inbox
			while (!this.inbox.isEmpty()) {
				synchronized (this.inbox) {
					StdMsg msgIn = this.inbox.poll();
					this.out("Recieved StdMsg: " + msgIn.toString());
				}
			}

			this.runStatus = false;

			if (this.inbox.isEmpty() && this.runCmd) {
				this.out("Waiting for Inbox.Notify.");
			}				
			while (this.inbox.isEmpty() && this.runCmd) {
				synchronized (this.inbox) {
					try {
						this.inbox.wait(200);
					} catch (InterruptedException e) {
						delay = (long) ((Math.random() * (this.MAXSLEEP - this.MINSLEEP)) + this.MINSLEEP);
						this.err("this.inbox.wait(), failed.  Pausing for " + delay/1000.0f + " Seconds.");						
						STUtilities.pause(delay);
					}
				}

			}
		}

		this.getMs().UnRegisterMsgStop(this.myMsgStop);
		this.out("Shutdown.");
	}

	public void start() {
		this.out("Received Startup Command.");
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
		this.out("Received Shutdown Command.");
		this.runCmd = false;

		synchronized (this.inbox) {
			this.inbox.notify();
		}
	}

	public MsgStop getMsgStop() {
		return this.myMsgStop;
	}

}
