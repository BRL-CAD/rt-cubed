package stractNet.tests;

import java.io.IOException;
import java.net.InetAddress;
import java.net.UnknownHostException;

import stractNet.SNRoot;
import stractNet.messaging.MessageDispatcher;
import stractNet.messaging.MessagingSystem;
import stractNet.portals.PortalManager;
import stractThread.STRunManager;
import stractThread.STUtilities;

public class SampleApplication02 {

	/*
	 * This application sets up a MessagingSystem, and 1 EchoSubsystem.
	 * 
	 * This Sample Application is designed to connect to an already running
	 * SampleApplication01. If the connection is successful, then the running
	 * SampleApplication01 will Echo several messages across the network
	 * connection to this SampleApplication02. Note: The 15 Second main thread
	 * timeout will need to be removed/extended in SampleApplication01
	 */

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			@SuppressWarnings("unused")
			SampleApplication02 SA02 = new SampleApplication02(InetAddress
					.getLocalHost(), 41222);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}

	}

	public SampleApplication02(InetAddress host, int port) {

		int[] mts01 = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };
		long MinDelay = 1000L;
		long MaxDelay = 5000L;
		SNRoot.VerbosityLevel = 2;

		try {
			MessagingSystem MS = new MessagingSystem("SA02-MessagingSystem");
			MessageDispatcher MD = new MessageDispatcher("SA02-MsgDispatcher",
					MS);
			PortalManager PM = new PortalManager("SA02-PortMan", host, port, MS);
			STRunManager RMcore = new STRunManager("SA02-CoreRunMan");
			STRunManager RMss = new STRunManager("SA02-SubSystemRunMan");

			ReactionSubsystem rss01 = new ReactionSubsystem("RSS01", MS, mts01, MinDelay,
					MaxDelay);

			MS.RegisterMsgStop(rss01.getMsgStop());

			RMcore.addExecute(MD.gON(), MD);
			RMcore.addExecute(PM.gON(), PM);
			RMss.addExecute(rss01.gON(), rss01);

			// pause for 10 Seconds.
			STUtilities.pause(10000L);
			
			for (int i = 0; i<10; i++ ) {
				System.err.println("\n\nConnecting to Localhost Port 41111\n\n");
				PM.ConnectTo(InetAddress.getByName("128.63.24.84"), 41111);
				
				// pause for 30 Seconds.
				STUtilities.pause(30000L);
				
				System.err.println("\n\nDisconnecting from Localhost Port 41111\n\n");
				PM.disconnectFrom(InetAddress.getByName("128.63.24.84"), 41111);
			
				// pause for 5 Seconds.
				STUtilities.pause(5000L);
			}
			
			// Shut Everything down.
			RMss.stopAll(true);
			RMcore.stopAll(true);

			System.out.println("Done.");
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
