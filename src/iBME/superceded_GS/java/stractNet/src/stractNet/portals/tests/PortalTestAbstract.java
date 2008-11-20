package stractNet.portals.tests;

import stractNet.*;
import stractNet.messaging.msgs.StdMsgTypes;

import java.net.*;

public class PortalTestAbstract extends SNRoot {

	protected int[] mtsInUseA = { StdMsgTypes.mtBroadcast, 100, 200, 300 };
	protected int[] mtsInUseB = { 400, 500 };
	protected InetAddress localhost;
	protected long sleep;

	public PortalTestAbstract(String Name) {
		super(Name);
		try {
			this.localhost = InetAddress.getLocalHost();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		}
		
		this.sleep = 1000L;
		SNRoot.VerbosityLevel = 2;
		
		System.out.println();
		System.out.println("*********************************************");
		System.out.println("           Running " + this.ObjName + "...");
		System.out.println("*********************************************");
		System.out.println();

		
	}


}
