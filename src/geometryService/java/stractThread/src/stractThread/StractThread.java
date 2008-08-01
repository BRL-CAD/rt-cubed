package stractThread;

public abstract class StractThread {
	protected String ObjName;

	protected void out(String message) {
		StractThread.sout(gON() + ": " + message);
	}

	protected void err(String message) {
		StractThread.serr(gON() + ": " + message);
	}

	// TODO Clean up out,err,sout,err routing.
	public static void sout(String message) {
		System.out.println(message);
	}

	public static void serr(String message) {
		System.err.println(message);
	}

	// Quick & Dirty getters -> simplifies inclusion into Strings
	public String gON() {
		return this.ObjName;
	}

	public String gOT() {
		return this.getClass().getSimpleName();
	}

	public static boolean Implements(Object object, String Interface) {
		Class<?>[] intfs = object.getClass().getInterfaces();

		for (Class<?> c : intfs) {
			if (c.getSimpleName().equals(Interface)) {
				return true;
			}
		}
		return false;
	}

	
	
	
	public static final long threadTick = 25;
	
	
	public static boolean waitForThreadRunStatusChange(STRunnable stru,
			boolean toStatus) {
		return waitForThreadRunStatusChange(stru, toStatus, 10000L);
	}
		public static boolean waitForThreadRunStatusChange(STRunnable stru,
				boolean toStatus, long timeOutInMS) {
		long tcnt = 0L;

		if(stru.getRunStatus() == toStatus) {return true;}
		
		if(stru.getRunCmd() != toStatus) {
			if (toStatus == true) {
				stru.start();
			} else {
				stru.stop();
			}
		}
		
		Thread t = stru.getThread();

		if (t == null) {
			if (toStatus == false) {
				// thread must have already exited.
				return true;
			} else {
				serr("Attempted to set a null Thread to RUN in StractThread.waitForThreadRunStatusChange()");
				return false;
			}
		}

		while (stru.getRunStatus() != toStatus) {
			
			try {
				Thread.sleep(threadTick);
				tcnt += threadTick;

				if (tcnt >= timeOutInMS) {
					serr("Timeout reached in StractThread.waitForThreadRunStatusChange(): " + t.getName());
					return false;
				}

			} catch (InterruptedException ie) {
				serr("InterruptedException in StractThread.waitForThreadRunStatusChange().");
				return false;
			}
		}
		return true;
	}

	public static boolean waitForThreadEnableStatusChange(STPauseable stp,
			boolean toStatus) {
		return waitForThreadEnableStatusChange(stp, toStatus, 10000L);
	}
	public static boolean waitForThreadEnableStatusChange(STPauseable stp,
			boolean toStatus, long timeOutInMS) {
		long tcnt = 0L;

		if (stp == null) {
			// something BAD happened
			return false;
		}

		while (stp.isEnabled() != toStatus) {
			try {
				Thread.sleep(threadTick);
				tcnt += threadTick;

				if (tcnt >= timeOutInMS) {
					serr("Timeout reached in StractThread.waitForThreadEnableStatusChange()");
					return false;
				}

			} catch (InterruptedException ie) {
				serr("InterruptedException in StractThread.waitForThreadEnableStatusChange().");
				return false;
			}
		}
		return true;
	}

}
