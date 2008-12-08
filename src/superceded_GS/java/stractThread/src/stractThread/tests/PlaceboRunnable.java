package stractThread.tests;

import stractThread.STRunnable;
import stractThread.StractThread;

public class PlaceboRunnable extends StractThread implements STRunnable {
	private Thread myThread;
	private boolean runStatus = false;
	private boolean runCmd = false;


	
	public PlaceboRunnable(String Name) {
		this.ObjName = Name;
		this.myThread = new Thread(this.gON().concat("-Thread"));
	}
	
	

	/*
	 * Use start() when you want to run this object in a dedicated Thread
	 * aka Non-Blocking.
	 */
	@Override
	public void start() {
		this.out("Received Startup Command.");
		this.runCmd = true;
		this.myThread = new Thread(this, this.gON().concat("-Thread"));
		this.myThread.start();
	}
	
	/*
	 * Use start() when you want to run this object in a Blocking mode.
	 */
	@Override
	public void run() {
		this.runStatus = true;
		this.out("Running.");
		
		while (this.runCmd) {
			
			//this.out("\tMessage");
			try {
				Thread.sleep(100);
			} catch (InterruptedException ie) {
				this.err("InterruptedException in waitForThreadStatusChange().");
			}

		}
		this.runStatus = false;
		this.out("Shutdown.");
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
		this.out("Received Shutdown Command.");
		this.runCmd = false;
	}



	@Override
	public boolean getRunCmd() {
		return this.runCmd;
	}
	
	
}
