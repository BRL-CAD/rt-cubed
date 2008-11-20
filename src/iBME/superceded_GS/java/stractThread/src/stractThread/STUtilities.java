package stractThread;

import stractThread.StractThread;

public class STUtilities extends StractThread {
	
	
	public static void pause(long ms) {
		try {
			Thread.sleep(ms);
		} catch (InterruptedException ie) {
			StractThread.serr("InterruptedException.");
		}
	}
	
	
}
