package stractNet.tests;

import java.util.LinkedList;
import stractNet.messaging.MessagingSystem;
import stractNet.messaging.MsgStop;
import stractNet.messaging.msgs.StdMsg;
import stractNet.messaging.msgs.StdMsgTypes;
import stractNet.messaging.msgs.frags.IntegerFrag;
import stractNet.messaging.msgs.frags.LongFrag;
import stractNet.messaging.msgs.frags.StringFrag;
import stractThread.STRunnable;
import stractThread.STUtilities;

public class SendAndEchoSubSystem extends TestAppCore implements STRunnable {
	private MsgStop myMsgStop = null;
	private Thread myThread = null;
	private boolean runStatus = false;
	private boolean runCmd = false;
	private LinkedList<StdMsg> inbox = null;
	private long MAXSLEEP = 0L;
	private long MINSLEEP = 0L;

	public SendAndEchoSubSystem(String Name, MessagingSystem ms,
			int[] msgTypes, long MinDelay, long MaxDelay) {
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

		//random Delay
		long delay = (long) ((Math.random() * (this.MAXSLEEP - this.MINSLEEP)) + this.MINSLEEP);
		this.out("Pausing for " + delay/1000.0f + " Seconds.");
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
				StdMsg msgIn = null;
				
				
				synchronized (this.inbox) {
					msgIn = this.inbox.poll();
				}
				
				// random pause
				delay = (long) ((Math.random() * (this.MAXSLEEP - this.MINSLEEP)) + this.MINSLEEP);
				this.out("Pausing for " + delay/1000.0f + " Seconds.");
				STUtilities.pause(delay);
				
				
				//Send some random data
				
				// Generate a Random MsgType
				int mtindex = (int) ((Math.random() * (this.myMsgStop
						.getMsgTypesIntArray().length - 1)));
				int mt = this.myMsgStop.getMsgTypesIntArray()[mtindex];

				// Create new message
				msgOut = this.getMs().generateNewMsg(mt,
						msgIn.getFromHost());
				msgOut.AddElement(new StringFrag("SomeData:"));
				msgOut.AddElement(new IntegerFrag(9823475));
				msgOut.AddElement(new LongFrag(90873459875345L));

				this.out("Sending StdMsg: " + msgOut.toString());
				this.myMsgStop.sendToMS(msgOut);

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
