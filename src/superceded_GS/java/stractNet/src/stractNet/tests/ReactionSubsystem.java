package stractNet.tests;


import java.util.LinkedList;
import stractNet.messaging.MessagingSystem;
import stractNet.messaging.MsgStop;
import stractNet.messaging.msgs.StdMsg;
import stractNet.messaging.msgs.StdMsgTypes;
import stractThread.STRunnable;
import stractThread.STUtilities;

public class ReactionSubsystem extends TestAppCore implements STRunnable {
	private MsgStop myMsgStop = null;
	private Thread myThread = null;
	private boolean runStatus = false;
	private boolean runCmd = false;
	private LinkedList<StdMsg> inbox = null;
	private long MAXSLEEP = 0L;
	private long MINSLEEP = 0L;

	public ReactionSubsystem(String Name, MessagingSystem ms, int[] msgTypes,
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
		long delay;// = (long) ((Math.random() * (this.MAXSLEEP -
					// this.MINSLEEP)) + this.MINSLEEP);
		// this.out("Pausing for " + delay / 1000.0f + " Seconds.");
		// STUtilities.pause(delay);

		while (this.runCmd) {
			this.runStatus = true;
			try {

				if (!this.inbox.isEmpty()) {

					StdMsg msgIn;

					synchronized (this.inbox) {
						msgIn = this.inbox.poll();
					}

					// random Delay
					delay = (long) ((Math.random() * (this.MAXSLEEP - this.MINSLEEP)) + this.MINSLEEP) / (this.inbox.size() + 1);
					this.out("Pausing for " + delay / 1000.0f + " Seconds. Inbox Size: " + this.inbox.size());
					STUtilities.pause(delay);

					StdMsg msgOut = null;

					// Generate a Random MsgType
					int mtindex = (int) ((Math.random() * (this.myMsgStop
							.getMsgTypesIntArray().length - 1)));
					int mt = this.myMsgStop.getMsgTypesIntArray()[mtindex];

					// 5% change of being a broadcast& ALLHOSTS, 10% chance of going to ALLHOSTS
					if ((Math.random() * 100) < 5.0f) {
						msgOut = this.getMs().generateNewMsg(StdMsgTypes.mtBroadcast,StdMsgTypes.AllHosts);
					} else if ((Math.random() * 100) < 10.0f) {
						msgOut = this.getMs().generateNewMsg(mt,StdMsgTypes.AllHosts);
					} else {
						msgOut = this.getMs().generateNewMsg(mt,msgIn.getFromHost());
					}

					this.out("Sending StdMsg: " + msgOut.toString());
					this.myMsgStop.sendToMS(msgOut);

				}

				this.runStatus = false;

				if (this.inbox.isEmpty() && this.runCmd) {
					this.out("Waiting for Inbox.Notify.");
				}
				while (this.inbox.isEmpty() && this.runCmd) {
					synchronized (this.inbox) {
						this.inbox.wait(200);
					}

				}

			} catch (InterruptedException e) {
				e.printStackTrace();
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
