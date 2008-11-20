package stractNet.messaging.tests;

import java.io.*;
import java.net.*;

import stractNet.*;
import stractNet.messaging.*;
import stractNet.portals.PortalManager;
import stractThread.STRunManager;

public class PlaceboMessageServer extends SNRoot {

	private int[] MTsInUseA;
	private int[] MTsInUseB;
	private PlaceboMsgStoppableClass MsgStopObj01;
	private PlaceboMsgStoppableClass MsgStopObj02;
	private MessageDispatcher MD = null;
	private STRunManager STRM = null;
	private PortalManager PortMan = null;
	

	public PlaceboMessageServer(String name, InetAddress host, int port,
								int[] ocsInUseA, int mtiA, long delayA, 
								int[] ocsInUseB, int mtiB, long delayB) throws IOException {
		super(name);
		this.MTsInUseA = ocsInUseA;
		this.MTsInUseB = ocsInUseB;


		this.setLocalMS(new MessagingSystem(this.gON()+ "-MessagingSystem"));

		this.MsgStopObj01 = new PlaceboMsgStoppableClass(this.gON() + "-MsgStoppableClass01", mtiA, delayA, this.getLocalMS());
		this.MsgStopObj01.getMsgStop().addMsgTypes(this.MTsInUseA);
		this.getLocalMS().RegisterMsgStop(MsgStopObj01.getMsgStop());
		
		this.MsgStopObj02 = new PlaceboMsgStoppableClass(this.gON()+ "-MsgStoppableClass02", mtiB, delayB, this.getLocalMS());
		this.MsgStopObj02.getMsgStop().addMsgTypes(this.MTsInUseB);
		this.getLocalMS().RegisterMsgStop(MsgStopObj02.getMsgStop());
		
		this.MD = new MessageDispatcher(this.gON() + "-MsgDispatcher", this.getLocalMS());
		
		this.PortMan = new PortalManager(this.gON() + "-PortMan", host, port, this.getLocalMS());
		
		this.STRM = new STRunManager(this.gON() + "-RunMan");
	}
	

	public int[] getMTsInUseA() {
		return MTsInUseA;
	}


	public int[] getMTsInUseB() {
		return MTsInUseB;
	}


	public PlaceboMsgStoppableClass getMsgStopObj01() {
		return MsgStopObj01;
	}


	public PlaceboMsgStoppableClass getMsgStopObj02() {
		return MsgStopObj02;
	}


	public MessageDispatcher getMD() {
		return MD;
	}

	public STRunManager getRunMan() {
		return this.STRM;
	}
	
	public PortalManager getPortMan() {
		return PortMan;
	}


	public void start() {
		STRM.addExecute(this.MsgStopObj01.gON(), this.MsgStopObj01);
		STRM.addExecute(this.MsgStopObj02.gON(), this.MsgStopObj02);
		STRM.addExecute(this.MD.gON(), this.MD);
		STRM.addExecute(this.PortMan.gON(), this.PortMan);
	}
	
	public void printAllHosts() {
		this.out("Host Report: " + this.getLocalMS().getRemoteHostNamesString(), 0);
	}
}
