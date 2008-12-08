package stractNet.portals.tests;

import stractNet.messaging.tests.*;
import stractThread.STUtilities;
import java.io.IOException;

/*
 * 
 * Establishes a localhost set of 2 Portals, sends a msg, disconnects, sends a msg, reconnects, sends a message.
 * 
 * A->B
 * 
 */

public class PortalTest08 extends PortalTestAbstract {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		@SuppressWarnings("unused")
		PortalTest08 p01 = new PortalTest08();
		System.out.println("Done.");
	}

	public PortalTest08() {
		super("PortalTest04");

		try {

			PlaceboMessageServer pmsA = new PlaceboMessageServer("PMS_Alpha", localhost, 45111,
					mtsInUseA,  0, 500L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsB = new PlaceboMessageServer("PMS_Bravo", localhost, 45222,
					mtsInUseA,  0, 400L, mtsInUseB, 0, 10L);
	

			pmsA.start();
			pmsB.start();
			
			// Send messages
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: A->B ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsA.getPortMan().ConnectTo(localhost, 45222);
			STUtilities.pause(this.sleep);
					
			// Send messages
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			pmsB.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);

			pmsA.printAllHosts();
			pmsB.printAllHosts();
			
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Disconnecting A from B...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to Disconnect!
			pmsA.getPortMan().disconnectFrom(pmsB.getLocalMS().getHostName());
			STUtilities.pause(this.sleep);
					
			// Send messages
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			pmsB.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);	
			
			pmsA.printAllHosts();
			pmsB.printAllHosts();
			
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: A->B ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsA.getPortMan().ConnectTo(localhost, 45222);
			STUtilities.pause(this.sleep);
					
			// Send messages
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			pmsB.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);

			pmsA.printAllHosts();
			pmsB.printAllHosts();

			
			
			
			
			
			
			
			
			// Keep everythign alive while Anything is running.
			while (pmsA.getRunMan().areAnyStatusRunning() 
					|| pmsB.getRunMan().areAnyStatusRunning() 
					) {
				STUtilities.pause(25L);
			}
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Shutting Everything Down ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			pmsA.getRunMan().stopAll(true);
			pmsB.getRunMan().stopAll(true);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
