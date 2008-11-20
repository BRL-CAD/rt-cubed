package stractThread.tests;

import stractThread.*;

public class STRunManagerTest01 {

	public static void main(String[] args) {
		long pause = 300L;
		
		
		STRunManager strm = new STRunManager("MyRunManager");

		// Instantiate Runnables;
		PlaceboRunnable r00 = new PlaceboRunnable("r00");
		PlaceboRunnable r01 = new PlaceboRunnable("r01");
		PlaceboRunnable r02 = new PlaceboRunnable("r02");
		PlaceboRunnable r03 = new PlaceboRunnable("r03");
		PlaceboRunnable r04 = new PlaceboRunnable("r04");
		PlaceboRunnable r05 = new PlaceboRunnable("r05");

		// Execute some
		strm.addExecute("Runnable 00", r00);
		strm.addExecute("Runnable 01", r01);
		strm.addExecute("Runnable 02", r02);
		strm.addExecute("Runnable 03", r03);

		// Add but don't execute a few.
		strm.addDoNotExecute("Runnable 04", r04);
		strm.addDoNotExecute("Runnable 05", r05);

		STUtilities.pause(pause);
		printstatus(strm,6,4);
		STUtilities.pause(pause);

		// stop one.
		strm.stop("Runnable 03");
		STUtilities.pause(pause);
		printstatus(strm,6,3);

		STUtilities.pause(pause);

		// start all
		strm.executeAll();
		STUtilities.pause(pause);
		printstatus(strm,6,6);
		STUtilities.pause(pause);

		// stop all
		strm.stopAll(true);
		STUtilities.pause(pause);
		printstatus(strm,6,0);
		STUtilities.pause(pause);

		System.out.println("Main Thread Exit.");
		return;
	}

	public static void printstatus(STRunManager p, int total, int run) {
		synchronized (System.out) {
			System.out.println("Test:  Should be " + run + " of " + total + " threads running.");

			System.out.println("\tTotal Threads: " + p.getNumThreads());
			System.out.println("\tRunning: " + p.getNumRunning());
			System.out.println("\tNot Running: " + p.getNumNotRunning());
			if (p.getNumThreads()== total && p.getNumRunning() == run) {
				System.out.println("Test Step Passed.");
			} else {
				System.out.println("Test Step Failed.");
			}
			System.out.println("\n");
		}
	}

}
