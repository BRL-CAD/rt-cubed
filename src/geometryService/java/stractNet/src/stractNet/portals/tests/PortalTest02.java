package stractNet.portals.tests;

import stractNet.messaging.tests.*;
import stractThread.STUtilities;
import java.io.IOException;

/*
 * 
 * Establishes a loopback set of 3 Portals
 * 
 * A->B->C
 * 
 */

public class PortalTest02 extends PortalTestAbstract {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		@SuppressWarnings("unused")
		PortalTest02 p01 = new PortalTest02();
		System.out.println("Done.");
	}

	public PortalTest02() {
		super("PortalTest02");

		try {
			PlaceboMessageServer pmsA = new PlaceboMessageServer("PMS_Alpha", localhost, 45111,
					mtsInUseA,  1, 500L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsB = new PlaceboMessageServer("PMS_Bravo", localhost, 45222,
					mtsInUseB,  0, 400L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsC = new PlaceboMessageServer("PMS_Charlie", localhost, 45333,
					mtsInUseA,  0, 300L, mtsInUseB, 0, 10L);


			pmsA.start();
			pmsB.start();
			pmsC.start();
			
			STUtilities.pause(this.sleep);
			
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: A->B ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			
			// Try to make a connection!
			pmsA.getPortMan().ConnectTo(localhost, 45222);
			STUtilities.pause(this.sleep);
			
			
			// Send more messages to see if they can be passed from MS to MS
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			pmsB.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			pmsC.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);

			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: B->C ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			
			// Try to make a connection!
			pmsB.getPortMan().ConnectTo(localhost, 45333);
			STUtilities.pause(this.sleep);
			
			
			// Send more messages to see if they can be passed from MS to MS
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			pmsB.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);
			pmsC.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);

			
			// Keep everythign alive while Anything is running.
			while (pmsA.getRunMan().areAnyStatusRunning() 
					|| pmsB.getRunMan().areAnyStatusRunning() 
					|| pmsC.getRunMan().areAnyStatusRunning()) {
				STUtilities.pause(25L);
			}

			
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Shutting Everything Down ...");
			System.out.println("****************************************************");			
			System.out.println();			
			

			
			pmsA.getRunMan().stopAll(true);
			pmsB.getRunMan().stopAll(true);
			pmsC.getRunMan().stopAll(true);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
