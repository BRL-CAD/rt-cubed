package stractNet.messaging.tests;

import stractNet.*;
import stractNet.messaging.*;
import stractThread.*;


/*
 * Message Delievery assurance test
 */



public class MSTest01 extends SNRoot {

	public static MSTest01 test;

	public static void main(String[] args) {
		test = new MSTest01();
	}



	public MSTest01() {
		//Name the Object Instance
		super("MSTest01");
		
		//Set Verbosity
		SNRoot.VerbosityLevel = 2;

		//Set up Message Parameters for test
		int msgsToSend = 3;
		long delay = 25;


		//Instantiate a RunManager
		STRunManager strm = new STRunManager("MSTest01-RunMan");

		
		//Initantiate a MessagingSystem
		SNRoot.setGlobalMS(new MessagingSystem("MsgServer"));
		this.setLocalMS(SNRoot.getGlobalMS());
		
		MessageDispatcher md1 = this.getLocalMS().generateNewMD();
		strm.addExecute(md1.gON(),md1);

		this.out("MS is running.",0);
		
		
		int[] set01 = { 1, 2, 3};
		PlaceboMsgStoppableClass pmsc01 = new PlaceboMsgStoppableClass(
				"pmsc01", msgsToSend, delay);
		pmsc01.getMsgStop().addMsgTypes(set01);
		this.getLocalMS().RegisterMsgStop(pmsc01.getMsgStop());

		strm.addExecute("MS01", pmsc01);
	
		
		int[] set02 = { 3, 4, 5};
		PlaceboMsgStoppableClass pmsc02 = new PlaceboMsgStoppableClass(
				"pmsc02", msgsToSend, delay);
		pmsc02.getMsgStop().addMsgTypes(set02);
		this.getLocalMS().RegisterMsgStop(pmsc02.getMsgStop());
		
		strm.addExecute("MS02", pmsc02);
	
		
		int[] set03 = { 1, 3, 5 };
		PlaceboMsgStoppableClass pmsc03 = new PlaceboMsgStoppableClass(
				"pmsc03", msgsToSend, delay);
		pmsc03.getMsgStop().addMsgTypes(set03);
		this.getLocalMS().RegisterMsgStop(pmsc03.getMsgStop());

		strm.addExecute("MS03", pmsc03);

		
		this.out("Waiting...",0);
		 while (strm.areAnyStatusRunning()) {
			 STUtilities.pause(25);
		}

		
		this.out("Shutting down Runnable(s)...",0);
		strm.stopAll(true);
		if (strm.areAnyStatusRunning()) {
			this.err("Runnable(s) failed to stop.",0);
			return;
		}
					
		this.out("Done.",0);
		return;
	}

}
