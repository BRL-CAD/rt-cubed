package stractNet.portals.tests;

import stractNet.messaging.tests.*;
import stractThread.STUtilities;
import java.io.IOException;

/*
 * 
 * Establishes a localhost set of 4 Portals
 * 
 * A->B->C<-D
 * 
 * Msg sent from A, should arrive at D
 * 
 * 
 */

public class PortalTest04 extends PortalTestAbstract {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		@SuppressWarnings("unused")
		PortalTest04 p01 = new PortalTest04();
		System.out.println("Done.");
	}

	public PortalTest04() {
		super("PortalTest04");

		try {

			PlaceboMessageServer pmsA = new PlaceboMessageServer("PMS_Alpha",
					localhost, 45111, mtsInUseA, 0, 500L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsB = new PlaceboMessageServer("PMS_Bravo",
					localhost, 45222, mtsInUseB, 0, 400L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsC = new PlaceboMessageServer("PMS_Charlie",
					localhost, 45333, mtsInUseB, 0, 300L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsD = new PlaceboMessageServer("PMS_Delta",
					localhost, 45444, mtsInUseA, 0, 500L, mtsInUseB, 0, 10L);

			pmsA.start();
			pmsB.start();
			pmsC.start();
			pmsD.start();

			STUtilities.pause(this.sleep);

			System.out.println();
			System.out.println("****************************************************");
			System.out.println("        Connect the MessagingSystems: A->B ...");
			System.out.println("****************************************************");
			System.out.println();

			// Try to make a connection!
			pmsA.getPortMan().ConnectTo(localhost, 45222);
			STUtilities.pause(this.sleep);

			System.out.println();
			System.out.println("****************************************************");
			System.out.println("        Connect the MessagingSystems: B->C ...");
			System.out.println("****************************************************");
			System.out.println();

			// Try to make a connection!
			pmsB.getPortMan().ConnectTo(localhost, 45333);
			STUtilities.pause(this.sleep);

			System.out.println();
			System.out.println("****************************************************");
			System.out.println("        Connect the MessagingSystems: D->C ...");
			System.out.println("****************************************************");
			System.out.println();

			// Try to make a connection!
			pmsD.getPortMan().ConnectTo(localhost, 45333);
			STUtilities.pause(this.sleep);

			// Send more messages to see if they can be passed from MS to MS
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);

			pmsD.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep);

			
			// Keep everythign alive while Anything is running.
			while (pmsA.getRunMan().areAnyStatusRunning() 
					|| pmsB.getRunMan().areAnyStatusRunning() 
					|| pmsC.getRunMan().areAnyStatusRunning()
					|| pmsD.getRunMan().areAnyStatusRunning()
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
			pmsC.getRunMan().stopAll(true);
			pmsD.getRunMan().stopAll(true);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
