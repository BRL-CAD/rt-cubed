package stractNet.messaging.msgs;

public class StdMsgTypes {
	/*
	 * 
	 * MsgType enumeration Completely Static Class Inherits from
	 * java.lang.Object
	 */
	
	
	//Ensure a unique name to avoid collisions with a HostName that someone might pick.
	public static String AllHosts = "ALLHOSTS";	

	public final static int mtBroadcast = 0;
	public final static int mtHello = 1;
	public final static int mtGoodBye = 2;
	public final static int mtMSCannotAcceptConn = 3;
	public final static int mtMyMsgTypes = 4;

	public final static int mtPortalSetRemoteHostName = 10;
	public final static int mtPortalHostNameNotUnique = 11;
	public final static int mtPortalHostNameAlreadyInUse = 12;
	public final static int mtPortalHostNameAlreadyOnNet = 13;
	public final static int mtMSNotMaster = 14;
	
	public final static int mtPing = 20;
	public final static int mtPong = 21;

}
