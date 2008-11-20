package stractThread;



public class STPauseManager extends STRunManager {

	private long timeOut = 10000L;

	/*
	 * Constructors
	 */

	public STPauseManager(String Name) {
		super(Name);
	}

	
	
	
	
	/*
	 * Utilities
	 */

	public int getNumRunnables() {
		int cnt = 0;
		for (STRunnable stru : this.Pool.values()) {
			//Check the class type
			if (!StractThread.Implements(stru, "STPauseable")) {
				cnt++;
			}
		}
		return cnt;
	}
	

	public int getNumPauseables() {
		int cnt = 0;
		for (STRunnable stru : this.Pool.values()) {
			//Check the class type
			if (!StractThread.Implements(stru, "STPauseable")) {
				cnt++;
			}
		}
		return cnt;
	}
	

	public int getNumEnabled() {
		int cnt = 0;

		for (STRunnable stru : this.Pool.values()) {
			
			//Check the class type
			if (!StractThread.Implements(stru, "STPauseable")) {
				//this.err("Not a STPauseable");
				continue;
			}
			//cast up
			STPauseable stpa = (STPauseable)stru;

			if (stpa.isEnabled() == true) {
				cnt++;
			}
		}
		return cnt;
	}
	
	public int getNumDisabled() {
		int cnt = 0;

		for (STRunnable stru : this.Pool.values()) {
			
			//Check the class type
			if (!StractThread.Implements(stru, "STPauseable")) {
				//this.err("Not a STPauseable");
				continue;
			}
			//cast up
			STPauseable stpa = (STPauseable)stru;

			if (stpa.isEnabled() == false) {
				cnt++;
			}
		}
		return cnt;
	}
	

	/*
	 * getStatus
	 */

	public boolean areAllEnabled() {
		// Are ALL in the group Enabled?
		for (STRunnable stru : this.Pool.values()) {
			//type check
			if (!StractThread.Implements(stru, "STPauseable")) {
				//this.err("Not a STPauseable");
				continue;
			}
			//cast up
			STPauseable stp = (STPauseable)stru;

			if (stp.isEnabled() == false) {
				return false;
			}
		}
		return true;
	}

	public boolean areAnyEnabled() {
		// Are ANY Enabled?
		for (STRunnable stru : this.Pool.values()) {
			//type check
			if (!StractThread.Implements(stru, "STPauseable")) {
				//this.err("Not a STPauseable");
				continue;
			}
			//cast up
			STPauseable stp = (STPauseable)stru;

			if (stp.isEnabled() == true) {
				return true;
			}
		}
		return false;
	}

	
	/*
	 * set Status -> ENABLE
	 */

	public void enableAll() {
		this.enableAll( false);
	}
	public void enableAll(boolean block) {
		// Set all STPauseables to ENABLE!
		this._ModThreadEnableStatus_All(true, block);
	}
	
	public boolean enable(String name) {
		return this.enable(name, false);
	}
	public boolean enable(String name, boolean block) {
		STRunnable stru = this.Pool.get(name);
		//type check
		if (!StractThread.Implements(stru, "STPauseable")) {
			//this.err("Not a STPauseable");
			return false;
		}
		//cast up
		STPauseable stp = (STPauseable)stru;
		return this._enable(stp, block);
	}

	
	
	
	
	
	/*
	 * set Status -> DISABLE
	 */
	public void disableAll() {
		this.disableAll( false);
	}
	public void disableAll(boolean block) {
		// Set all STPauseables to DISABLE!
		this._ModThreadEnableStatus_All(false, block);
	}
	
	public boolean disable(String name) {
		return this.disable(name, false);
	}
	public boolean disable(String name, boolean block) {
		STRunnable stru = this.Pool.get(name);
		//type check
		if (!StractThread.Implements(stru, "STPauseable")) {
			//this.err("Not a STPauseable");
			return false;
		}
		//cast up
		STPauseable stp = (STPauseable)stru;
		return this._disable(stp, block);
	}



	
	
	
	
	/*
	 * Internals
	 */
	
	private void _ModThreadEnableStatus_All(boolean status, boolean block) {
		for (STRunnable stru : this.Pool.values()) {
			this._ModThreadEnableStatus(stru, status, block);
		}
	}

	private boolean _ModThreadEnableStatus(STRunnable stru, boolean status,
			boolean block) {

		// null check
		if (stru == null) {
			return false;
		}

		//type check
		if (!StractThread.Implements(stru, "STPauseable")) {
			//this.err("Not a STPauseable");
			return false;
		}
		//cast up
		STPauseable stp = (STPauseable)stru;
		
		if (stp.getThread().isAlive() != status) {
			if (status == false) {
				return this._enable(stp, block);
			} else {
				return this._disable(stp, block);
			}
		}

		return stru.getThread().isAlive();
	}

	private boolean _enable(STPauseable stp, boolean block) {
		// null check
		if (stp == null) {
			return false;
		}

		//type check
		if (!StractThread.Implements(stp, "STPauseable")) {
			//this.err("Not a STPauseable");
			return false;
		}
		
		stp.enable();

		if (block) {
			StractThread.waitForThreadEnableStatusChange(stp, true, timeOut);
		}

		return stp.isEnabled();
	}

	private boolean _disable(STPauseable stp, boolean block) {
		// null check
		if (stp == null) {
			return false;
		}

		//type check
		if (!StractThread.Implements(stp, "STPauseable")) {
			//this.err("Not a STPauseable");
			return false;
		}


		stp.disable();
		
		if (block) {
			StractThread.waitForThreadEnableStatusChange(stp, false, timeOut);
		}

		return stp.isEnabled();
	}




	public long getTimeOut() {
		return timeOut;
	}
	public void setTimeOut(long timeOut) {
		this.timeOut = timeOut;
	}



}


