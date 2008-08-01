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

public class SampleApplication01 {

	/*
	 * 
	 * This application sets up a MessagingSystem, 2 ReactionSubsystems and 1
	 * SendSubSystem.
	 * 
	 * Proper behaivor should be that the SendSubSystem sends a single message
	 * of a random type, and after a random pause the EchoSubSystems will reply
	 * to the sent message. If both EchoSubSystems are assigned the same
	 * MessageType then there is a chance for the two EchoSubSystems to do into
	 * an 'Echo Loop.' This is why the main thread will time out after 15
	 * Seconds and then issues a sequence of ShutDown Commands.
	 */

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			@SuppressWarnings("unused")
			SampleApplication01 SA01 = new SampleApplication01(InetAddress
					.getLocalHost(), 41111);
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}

	}

	public SampleApplication01(InetAddress host, int port) {

		int[] mts01 = { 100, 200, 300, 400, 500, 600, 700, 800, 900 };
		long MinDelay = 1000L;
		long MaxDelay = 5000L;
		SNRoot.VerbosityLevel = 2;

		try {
			MessagingSystem MS = new MessagingSystem("SA01-MessagingSystem");
			MessageDispatcher MD = new MessageDispatcher("SA01-MsgDispatcher",
					MS);
			PortalManager PM = new PortalManager("SA01-PortMan", host, port, MS);
			STRunManager RMcore = new STRunManager("SA01-CoreRunMan");
			STRunManager RMss = new STRunManager("SA01-SubSystemRunMan");

			ReactionSubsystem rss01 = new ReactionSubsystem("RSS01", MS, mts01, MinDelay,
					MaxDelay);
			ReactionSubsystem rss02 = new ReactionSubsystem("RSS02", MS, mts01, MinDelay,
					MaxDelay);

			SendSubSystem sss01 = new SendSubSystem("SSS01", MS, mts01,
					MinDelay, MaxDelay);

			MS.RegisterMsgStop(rss01.getMsgStop());
			MS.RegisterMsgStop(rss02.getMsgStop());
			MS.RegisterMsgStop(sss01.getMsgStop());

			RMcore.addExecute(MD.gON(), MD);
			RMcore.addExecute(PM.gON(), PM);
			RMss.addExecute(rss01.gON(), rss01);
			RMss.addExecute(rss02.gON(), rss02);
			RMss.addExecute(sss01.gON(), sss01);

			
			for (int i = 0; i<1000; i++ ) {
				// pause for 5 Seconds.
				STUtilities.pause(5000L);
				
				System.err.println("\n\nHosts:" + MS.getRemoteHostNamesString() + "\n\n");
			}			
			
			
			// pause for 15 Seconds.
			STUtilities.pause(15000L);

			
			
			
			
			// Shut Everything down.
			RMss.stop(rss01.gON(), true);
			STUtilities.pause(5000L);
			RMss.stop(rss02.gON(), true);
			STUtilities.pause(5000L);
			RMss.stop(sss01.gON(), true);

			RMcore.stopAll(true);

			System.out.println("Done.");
		} catch (IOException e) {
			e.printStackTrace();
		}

	}
}
