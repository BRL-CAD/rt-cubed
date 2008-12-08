package stractThread.tests;

import stractThread.*;

public class PlaceboPauseable extends StractThread implements STPauseable {
	private Thread myThread;
	private boolean runStatus = true;
	private boolean runCmd = true;
	private boolean enabledStatus = true;
	private boolean enabledCmd = true;

	public PlaceboPauseable(String Name) {
		this.ObjName = Name;
		this.myThread = new Thread(this.gON().concat("-Thread"));
	}

	/*
	 * Use start() when you want to run this object in a dedicated Thread aka
	 * Non-Blocking.
	 */
	@Override
	public void start() {
		this.out("Received Startup Command.");
		this.runCmd = true;
		this.enabledCmd = true;
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

			if (this.enabledCmd) {
				this.enabledStatus = true;

				// this.out("\tEnabled");

				try {
					Thread.sleep(750);
				} catch (InterruptedException ie) {
					this
							.err("InterruptedException in waitForThreadStatusChange().");
				}

				this.enabledStatus = false;
			} else {
				try {
					Thread.sleep(1000);
				} catch (InterruptedException ie) {
					this
							.err("InterruptedException in waitForThreadStatusChange().");
				}

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
	public void disable() {
		this.enabledCmd = false;
	}

	@Override
	public void enable() {
		this.enabledCmd = true;
	}

	@Override
	public boolean isEnabled() {
		return this.enabledStatus;
	}

	@Override
	public boolean getRunCmd() {
		return this.runCmd;
	}

}
