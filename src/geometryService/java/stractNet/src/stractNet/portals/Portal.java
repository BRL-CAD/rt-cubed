package stractNet.portals;

import stractNet.SNRoot;
import java.io.IOException;
import java.nio.channels.SocketChannel;
import stractNet.messaging.MessagingSystem;
import stractNet.messaging.msgs.StdMsg;
import stractNet.messaging.msgs.StdMsgTypes;

public class Portal extends SNRoot {

	private String RemoteHostName = "";
	private PortalManager PM = null;
	private SocketChannel sockChan = null;

	public Portal(String Name, PortalManager pm, SocketChannel sockChan) {
		this(Name, pm, sockChan, SNRoot.getGlobalMS());
	}

	public Portal(String Name, PortalManager pm, SocketChannel sockChan,
			MessagingSystem ms) {
		super(Name);
		this.PM = pm;
		this.sockChan = sockChan;
		this.setLocalMS(ms);		
		this.SendHostInfo();
	}

	public String getRemoteHostName() {
		return this.RemoteHostName;
	}

	public void SendToRemHost(StdMsg sm) {
		this.PM.send(this.sockChan, sm.Serialize());
	}

	public void SendToMS(StdMsg sm) {
		this.out("Recieved: " + sm.toString(), 2);
		this.out("\n" + sm.ElementsToString(), 3);

		// switch on any internal Message Types
		switch (sm.getMsgType()) {


		case StdMsgTypes.mtPortalSetRemoteHostName:
			this.PortalSetRemoteHostName(sm);
			return;
						
		case StdMsgTypes.mtMSNotMaster:
			this.err("Cannot establish Connection to remote Machine, Remote machine not a Master MS.",0);
			this.finishDisconnect();
			return;

		case StdMsgTypes.mtPortalHostNameNotUnique:
			this.err("Cannot establish Connection to remote Machine, Hostname already connected elsewhere.",0);
			this.finishDisconnect();
			return;

		case StdMsgTypes.mtPortalHostNameAlreadyInUse:
			this.err("Cannot establish Connection to remote machine, Hostname already in use.",0);
			this.finishDisconnect();
			return;

		case StdMsgTypes.mtGoodBye:
			this.out("Recieved Remote Disconnect Request.",1);
			this.finishDisconnect();
			return;

		default:
			break;
		}

		this.getLocalMS().AddMsgToQueue(sm);
	}

	
	private void finishDisconnect() {
		try {
			this.out("Finishing Disconnect.",2);
			StdMsg smout = this.getLocalMS().generateNewMsg(StdMsgTypes.mtGoodBye,"Portal2PortalComms");
			this.Send(smout);
			
			this.PM.disconnectFrom(this.RemoteHostName);

			this.sockChan.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void PortalSetRemoteHostName(StdMsg sm) {
		this.RemoteHostName = sm.getFromHost();
//		this.RemoteHostName = (String)sm.GetElement(0).getField();

		
		
		// Check for Exact Duplicate HostNames
		if (this.RemoteHostName.equals(this.getLocalMS().getHostName())) {
			// the machine attempting to connect has the same Hostname as this
			// one!!!

			StdMsg smout = this.getLocalMS().generateNewMsg(StdMsgTypes.mtPortalHostNameNotUnique,"Portal2PortalComms");
			this.Send(smout);
			return;
		}

		// Check for Multiple connections to the same host
		if (this.getLocalMS().hasRemoteHostOnFile(this.RemoteHostName)) {
			StdMsg smout = this.getLocalMS().generateNewMsg(StdMsgTypes.mtPortalHostNameAlreadyInUse,"Portal2PortalComms");
			this.Send(smout);
			return;
		}

		// else, we can complete the connection

		this.out("Recieved remote Hostname: " + RemoteHostName, 1);
		this.getLocalMS().RegisterPortal(this);
		return;
	}

	public void Send(StdMsg sm) {
		this.PM.send(this.sockChan, sm.Serialize());
		this.out("Sending: " + sm.toString(), 2);
		this.out("\n" + sm.ElementsToString(), 3);
	}

	private void SendHostInfo() {
		// Attempt to set the remote Host name field of the other end's Portal.
		StdMsg sm = this.getLocalMS().generateNewMsg(StdMsgTypes.mtPortalSetRemoteHostName,"Portal2PortalComms");
//		sm.AddElement(new StringFrag(this.getLocalMS().getHostName()));
		this.Send(sm);

	}

	public SocketChannel getSockChan() {
		return sockChan;
	}

}
