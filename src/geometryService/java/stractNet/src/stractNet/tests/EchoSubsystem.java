package stractNet.tests;

import java.io.IOException;
import java.util.LinkedList;
import stractNet.messaging.MessagingSystem;
import stractNet.messaging.MsgStop;
import stractNet.messaging.msgs.StdMsg;
import stractThread.STRunnable;
import stractThread.STUtilities;

public class EchoSubsystem extends TestAppCore implements STRunnable {
	private MsgStop myMsgStop = null;
	private Thread myThread = null;
	private boolean runStatus = false;
	private boolean runCmd = false;
	private LinkedList<StdMsg> inbox = null;
	private long MAXSLEEP = 0L;
	private long MINSLEEP = 0L;

	public EchoSubsystem(String Name, MessagingSystem ms, int[] msgTypes,
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
		long delay;// = (long) ((Math.random() * (this.MAXSLEEP - this.MINSLEEP)) + this.MINSLEEP);
//		this.out("Pausing for " + delay / 1000.0f + " Seconds.");
//		STUtilities.pause(delay);

		while (this.runCmd) {
			this.runStatus = true;
			try {

				if (!this.inbox.isEmpty()) {

					StdMsg msgIn;

					synchronized (this.inbox) {
						msgIn = this.inbox.poll();
					}

					// random Delay
					delay = (long) ((Math.random() * (this.MAXSLEEP - this.MINSLEEP)) + this.MINSLEEP);
					this.out("Pausing for " + delay / 1000.0f + " Seconds.");
					STUtilities.pause(delay);

					StdMsg msgOut = this.getMs().generateNewMsg(msgIn);
					msgOut.setToHost(msgIn.getFromHost());


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
				
			} catch (IOException e) {
				e.printStackTrace();
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
