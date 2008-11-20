package stractNet.tests;

import stractNet.messaging.MessagingSystem;

public class TestAppCore {
	
	public TestAppCore (String Name, MessagingSystem MS) {
		this.ObjName = Name;
		this.ms = MS;
	}
	
	private String ObjName = "";
	private MessagingSystem ms = null;
	
	
	public String gON() {
		return ObjName;
	}


	public MessagingSystem getMs() {
		return ms;
	}

	public void out(String data) {
		synchronized(System.out) {
			System.out.println(this.gON() + ": " + data);
		}
	}
	public void err(String data) {
		synchronized(System.err) {
			System.err.println(this.gON() + ": " + data);
		}
	}
	

}
