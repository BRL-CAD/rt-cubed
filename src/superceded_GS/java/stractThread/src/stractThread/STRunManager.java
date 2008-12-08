package stractThread;

import java.util.HashMap;

public class STRunManager extends StractThread {

	private long timeOut = 10000L;

	protected HashMap<String, STRunnable> Pool = new HashMap<String, STRunnable>();

	/*
	 * Constructors
	 */

	public STRunManager(String Name) {
		this.ObjName = Name;
	}

	/*
	 * Utilities
	 */
	public int getNumThreads() {
		int cnt = 0;

		for (STRunnable stru : this.Pool.values()) {
			if (stru.getThread() != null) {
				cnt++;
			}
		}
		return cnt;
	}

	public int getNumRunning() {
		int cnt = 0;

		for (STRunnable stru : this.Pool.values()) {
			Thread t = stru.getThread();
			if ((t != null) && (t.isAlive() == true)) {
				cnt++;
			}
		}
		return cnt;
	}

	public int getNumNotRunning() {
		int cnt = 0;

		for (STRunnable stru : this.Pool.values()) {
			Thread t = stru.getThread();
			if ((t != null) && (t.isAlive() != true)) {
				cnt++;
			}
		}
		return cnt;
	}

	/*
	 * Add-ers and Rem-ers
	 */

	public void addDoNotExecute(String name, STRunnable stru) {
		this.Pool.put(name, stru);
	}

	public boolean addExecute(String name, STRunnable stru) {
		this.Pool.put(name, stru);
		return this.execute(name);
	}

	public STRunnable rem(String name) {
		return this.Pool.remove(name);
	}

	/*
	 * getStatus
	 */

	public boolean areAllThreadsRunning() {
		// Are ALL in the group running?
		for (STRunnable stru : this.Pool.values()) {
			Thread t = stru.getThread();
			if ((t == null) || (t.isAlive() == false)) {
				return false;
			}
		}
		return true;
	}

	public boolean areAnyThreadsRunning() {
		// Are ANY running?
		for (STRunnable stru : this.Pool.values()) {
			Thread t = stru.getThread();
			if ((t != null) && (t.isAlive() == true)) {
				return true;
			}
		}
		return false;
	}

	public boolean areAllStatusRunning() {
		// Are ALL in the group running?
		for (STRunnable stru : this.Pool.values()) {
			if (!stru.getRunStatus()) {
				return false;
			}
		}
		return true;
	}

	public boolean areAnyStatusRunning() {
		// Are ANY running?
		for (STRunnable stru : this.Pool.values()) {
			if (stru.getRunStatus()) {
				return true;
			}
		}
		return false;
	}

	/*
	 * set Status -> RUN
	 */

	public void executeAll() {
		for (String s : this.Pool.keySet()) {
			this.execute(s, true);
		}
	}

	public void executeAll(boolean block) {
		for (String s : this.Pool.keySet()) {
			this.execute(s, block);
		}
	}

	public boolean execute(String name) {
		return execute(name, true);
	}

	public boolean execute(String name, boolean block) {
		STRunnable stru = this.Pool.get(name);

		// start
		if (stru.getRunCmd() == false && stru.getThread() == null) {
			stru.start();
		} else if (stru.getThread() == null) {
			stru.start();
		} else if (stru.getRunCmd() == false && stru.getThread() != null) {
			// RE-start
			stop_int(stru, true);
			stru.start();
		}

		while (!stru.getThread().isAlive() && block) {
			STUtilities.pause(25);
		}

		return stru.getRunStatus();
	}

	/*
	 * set Status -> STOP
	 */
	public void stopAll() {
		this.stopAll(true);
	}

	public void stopAll(boolean block) {
		//Initial Call
		for (STRunnable stru : this.Pool.values()) {
			stru.stop();
		}
		
		// Set all SBEmuRnnables to stop!
		for (STRunnable stru : this.Pool.values()) {
			stop_int(stru, block);
		}
	}

	public boolean stop(String name) {
		return this.stop(name, false);
	}

	public boolean stop(String name, boolean block) {
		STRunnable stru = this.Pool.get(name);
		if (stru == null) {
			return true;
		} else {
			return this.stop_int(stru, block);
		}
	}

	private boolean stop_int(STRunnable stru, boolean block) {
		stru.stop();

		Thread t = stru.getThread();
		if (t == null) {
			return true;
		}
		try {
			t.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		return t.isAlive();
	}

	/*
	 * Internals
	 */

	// private void _ModThreadRunStatus_All(boolean status, boolean block) {
	// ArrayList<String> toRem = new ArrayList<String>();
	//
	// synchronized (this.Pool) {
	// for (String s : this.Pool.keySet()) {
	//
	// STRunnable stru = this.Pool.get(s);
	//
	// if (stru.getRunStatus() != status) {
	// this._ModThreadRunStatus(stru, status, block);
	// }
	// if (status == false) {
	// toRem.add(s);
	// }
	// }
	//
	// for (String s : toRem) {
	// this.Pool.remove(s);
	// }
	//
	// }
	//
	// // for (STRunnable stru : this.Pool.values()) {
	// // this._ModThreadRunStatus(stru, status, block);
	// // }
	// }
	//
	// private boolean _ModThreadRunStatus(STRunnable stru, boolean status,
	// boolean block) {
	//
	// // null check
	// if (stru == null) {
	// return false;
	// }
	//
	// if ((stru.getThread() == null) && (status == false)) {
	// // null thread, but Stop requested.
	// return true;
	// } else if ((stru.getThread() == null) && (status == true)) {
	// // null thread, Start requested.
	// return this._start(stru, block);
	// }
	//
	// if (stru.getThread().isAlive() != status) {
	// if (status == false) {
	// return this._stop(stru, block);
	// } else {
	// return this._start(stru, block);
	// }
	// }
	//
	// return stru.getThread().isAlive();
	// }
	// private boolean _start(STRunnable stru, boolean block) {
	// // null check
	// if (stru == null) {
	// return false;
	// }
	//
	// stru.start(); // call start() not run() !!!!!!
	//
	// if (block) {
	// StractThread.waitForThreadRunStatusChange(stru, true, timeOut);
	// }
	//
	// return stru.getThread().isAlive();
	// }
	//
	// private boolean _stop(STRunnable stru, boolean block) {
	// // null check
	// if (stru == null) {
	// return false;
	// }
	//
	// stru.stop();
	//
	// if (block) {
	// StractThread.waitForThreadRunStatusChange(stru, false, timeOut);
	// }
	//
	// return stru.getThread().isAlive();
	// }
	public long getTimeOut() {
		return timeOut;
	}

	public void setTimeOut(long timeOut) {
		this.timeOut = timeOut;
	}

}
