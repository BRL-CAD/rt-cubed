package stractThread.tests;

import stractThread.*;

public class STPauseManagerTest01 {
	
	public static void main(String[] args) {
		STPauseManager stpm = new STPauseManager("MyPauseManager");
		
		System.out.println(stpm.gOT());
		
		
		//Instantiate Runnables & Pauseables;
		PlaceboRunnable r00 = new PlaceboRunnable("r00");
		PlaceboPauseable p01 = new PlaceboPauseable("p01");
		PlaceboRunnable r02 = new PlaceboRunnable("r02");
		PlaceboPauseable p03 = new PlaceboPauseable("p03");
		PlaceboRunnable r04 = new PlaceboRunnable("r04");
		PlaceboPauseable p05 = new PlaceboPauseable("p05");

		//Execute some
		stpm.addExecute("Runnable 00", r00);
		stpm.addExecute("Pauseable 01", p01);
		stpm.addExecute("Runnable 02", r02);
		stpm.addExecute("Pauseable 03", p03);
		
		//Add but don't execute a few.
		stpm.addDoNotExecute("Runnable 04", r04);
		stpm.addDoNotExecute("Pauseable 05", p05);

		System.err.println("\n\n\nStart / Stop Tests...");

		printstatus(stpm);
		

		
		
		STUtilities.pause(3000);

		//stop one.
		System.err.println("Stopping Pauseable 03...");
		stpm.stop("Pauseable 03");
		printstatus(stpm);
		
			
		STUtilities.pause(3000);

		//start all
		System.err.println("Starting all...");
		stpm.executeAll();
		printstatus(stpm);
		
		STUtilities.pause(5000);
		
		
		System.err.println("\n\n\nEnable/Disable Tests...");
		printstatus(stpm);


		
		//disable one.
		System.err.println("Disabling Pauseable 03...");
		stpm.disable("Pauseable 03");
		printstatus(stpm);
		
		STUtilities.pause(3000);

		
		//disable all.
		System.err.println("Disabling all...");
		stpm.disableAll();
		printstatus(stpm);
		
		STUtilities.pause(3000);
	
		
		//enable one.
		System.err.println("Enabling Pauseable 03...");
		stpm.enable("Pauseable 03");
		printstatus(stpm);
		
		STUtilities.pause(3000);
	
		//enable all.
		System.err.println("Enabling all...");
		stpm.enableAll();
		printstatus(stpm);
		
		STUtilities.pause(3000);
		
		
		//stop all
		System.err.println("Stopping all...");
		stpm.stopAll();
	
		//print totals
		printstatus(stpm);
		
		
		
		System.out.println("Main Thread Exit.");
		return;
	}

	
	public static void printstatus(STPauseManager p) {
		System.out.println("\n\tTotal Threads: " + p.getNumThreads());
		System.out.println("\tRunning: " + p.getNumRunning());
		System.out.println("\tNot Running: " + p.getNumNotRunning());
		System.out.println("\tEnabled: " + p.getNumEnabled());
		System.out.println("\tDisabled: " + p.getNumDisabled());
		System.out.println("\n\n");
	}
	
	
	
	

	
}
