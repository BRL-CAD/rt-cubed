package stractNet.portals.tests;

import stractNet.messaging.tests.*;
import stractThread.STUtilities;
import java.io.IOException;

/*
 * 
 * Establishes a localhost set of 7 Portals
 * 
 * A->B
 * v  v
 * C->D->E
 *    ^  ^
 *    F->G
 * 
 * 
 *   B   E
 *  / \ / \
 * A   D   G
 *  \ / \ /
 *   C   F
 * 
 * Msg sent from A, only one should arrive at G
 * 
 * 
 */

public class PortalTest07 extends PortalTestAbstract {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		@SuppressWarnings("unused")
		PortalTest07 p01 = new PortalTest07();
		System.out.println("Done.");
	}

	public PortalTest07() {
		super("PortalTest04");

		try {

			PlaceboMessageServer pmsA = new PlaceboMessageServer("PMS_Alpha", localhost, 45111,
					mtsInUseA,  0, 500L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsB = new PlaceboMessageServer("PMS_Bravo", localhost, 45222,
					mtsInUseB,  0, 400L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsC = new PlaceboMessageServer("PMS_Charlie", localhost, 45333,
					mtsInUseB,  0, 300L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsD = new PlaceboMessageServer("PMS_Delta", localhost, 45444,
					mtsInUseB,  0, 500L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsE = new PlaceboMessageServer("PMS_Echo", localhost, 45555,
					mtsInUseB,  0, 500L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsF = new PlaceboMessageServer("PMS_Foxtrot", localhost, 45666,
					mtsInUseB,  0, 500L, mtsInUseB, 0, 10L);
			PlaceboMessageServer pmsG = new PlaceboMessageServer("PMS_Golf", localhost, 45777,
					mtsInUseA,  0, 500L, mtsInUseA, 0, 10L);


			pmsA.start();
			pmsB.start();
			pmsC.start();
			pmsD.start();
			pmsE.start();
			pmsF.start();
			pmsG.start();
			
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
			System.out.println("        Connect the MessagingSystems: A->C ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsA.getPortMan().ConnectTo(localhost, 45333);
			STUtilities.pause(this.sleep);
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: B->D ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsB.getPortMan().ConnectTo(localhost, 45444);
			STUtilities.pause(this.sleep);
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: C->D ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsC.getPortMan().ConnectTo(localhost, 45444);
			STUtilities.pause(this.sleep);
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: D->E ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsD.getPortMan().ConnectTo(localhost, 45555);
			STUtilities.pause(this.sleep);
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: F->D ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsF.getPortMan().ConnectTo(localhost, 45444);
			STUtilities.pause(this.sleep);
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: F->G ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsF.getPortMan().ConnectTo(localhost, 45777);
			STUtilities.pause(this.sleep);
			
			System.out.println();			
			System.out.println("****************************************************");			
			System.out.println("        Connect the MessagingSystems: G->E ...");
			System.out.println("****************************************************");			
			System.out.println();			
			
			// Try to make a connection!
			pmsG.getPortMan().ConnectTo(localhost, 45555);
			STUtilities.pause(this.sleep);
			
			// Send more messages to see if they can be passed from MS to MS
			pmsA.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep * 2 );
			pmsG.getMsgStopObj01().SendMoreMsgs(1);
			STUtilities.pause(this.sleep * 2 );

			
			// Keep everythign alive while Anything is running.
			while (pmsA.getRunMan().areAnyStatusRunning() 
					|| pmsB.getRunMan().areAnyStatusRunning() 
					|| pmsC.getRunMan().areAnyStatusRunning()
					|| pmsD.getRunMan().areAnyStatusRunning()
					|| pmsE.getRunMan().areAnyStatusRunning()
					|| pmsF.getRunMan().areAnyStatusRunning()
					|| pmsG.getRunMan().areAnyStatusRunning()
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
			pmsE.getRunMan().stopAll(true);
			pmsF.getRunMan().stopAll(true);
			pmsG.getRunMan().stopAll(true);

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
