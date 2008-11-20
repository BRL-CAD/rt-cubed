package stractNet;

import stractNet.messaging.MessagingSystem;

public abstract class SNRoot {
	public SNRoot (String Name) {
		this.ObjName = Name;
		this.MS_Local = SNRoot.MS_Global;
	}
	
	
	/*
	 * 0 = Normal Waypoints
	 * 1 = Object Status reports (NON-Debuging)
	 * 2 = Object Data output (Debuging)
	 * 
	 */
	public static int VerbosityLevel = 0;
	
	protected String ObjName = "";

	
	
	
	
	//Messaging System configurations
	private static MessagingSystem MS_Global;
	private MessagingSystem MS_Local = SNRoot.MS_Global;
	
	public static MessagingSystem getGlobalMS() {		
		return SNRoot.MS_Global;
	}

	public static void setGlobalMS(MessagingSystem ms) {
		SNRoot.MS_Global = ms;
	}

	
	public MessagingSystem getLocalMS() {		
		return this.MS_Local;
	}

	public void setLocalMS(MessagingSystem ms) {
		this.MS_Local = ms;
	}

	
	
	
	
	
	protected void out(String message, int vLevel) {
		SNRoot.sout(gON() + ":\t" + message, vLevel);
	}

	protected void err(String message, int vLevel) {
		SNRoot.serr(gON() + ":\t" + message, vLevel);
	}

	// TODO Clean up out,err,sout,err routing.
	public static void sout(String message, int vLevel) {
		if (vLevel <= SNRoot.VerbosityLevel) {
			synchronized(System.out) {
				System.out.println(message);
			}
		}
	}

	public static void serr(String message, int vLevel) {
		if (vLevel <= SNRoot.VerbosityLevel) {
			synchronized(System.err) {
				System.err.println(message);
			}
		}
	}

	
	
	
	
	
	// Quick & Dirty getter'n'setters -> simplifies inclusion into Strings
	public String gON() {
		return this.ObjName;
	}
	public void sON(String name) {
		this.ObjName = name;
	}
	
	public String gOT() {
		return this.getClass().getSimpleName();
	}
}
