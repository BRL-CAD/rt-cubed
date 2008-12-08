package stractNet.messaging;


import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import stractNet.SNRoot;
import stractNet.messaging.msgs.frags.LongFrag;
import stractNet.messaging.msgs.frags.StringFrag;

public class NetID extends SNRoot {

	private LongFrag ID;
	private StringFrag Host;
	
	/*
	 * Manual Constructor
	 */
	public NetID(long ID, String host) {
		super("");
		this.ID = new LongFrag(ID);
		Host = new StringFrag(host);
	}
	//Copy constructor
	public NetID(NetID addr) {
		super("NetID");
		ID = new LongFrag(addr.getID());
		Host = new StringFrag(addr.getHost());
	}
	
	
	/*
	 * Deserializing Constructor
	 */
//	public NetID(byte[] data) throws IOException {
//		super("SNAddr");
//		
//		// Setup Streams
//		ByteArrayInputStream bais = new ByteArrayInputStream(data);
//		DataInputStream in = new DataInputStream(bais);
//
//		// Deserialize Components
//		this.ID = new LongFrag(in);
//		this.Host = new StringFrag(in);
//	}
	
	public NetID(DataInputStream in) throws IOException {
		super("NetID");
		in.readInt();
		this.ID = new LongFrag(in);
		in.readInt();
		this.Host = new StringFrag(in);
	}
	
	

	public byte[] Serialize() {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		this.Serialize(out);

		return baos.toByteArray();
	}
		
	public void Serialize(DataOutputStream out) {
		try {
			this.ID.Serialize(out);
			this.Host.Serialize(out);

		} catch (IOException ioe) {
			SNRoot.serr("IOException in Serialize()", 0);
		}
		return;
	}
		
	
	
	
	
	
	
	
//	public byte[] Serialize(byte[] prevData) {
//		ByteArrayOutputStream baos = new ByteArrayOutputStream();
//		DataOutputStream out = new DataOutputStream(baos);
//
//		try {
//			// Write in prevdata
//			out.write(prevData);
//			out.write(this.Serialize());
//			
//			return baos.toByteArray();
//		} catch (IOException ioe) {
//			SNRoot.serr("IOException in Serialize()", 0);
//		}
//
//		return null;
//		
//	}
		
	
	/**
	 * @return the msgStopID
	 */
	public long getID() {
		return ID.getField();
	}

	/**
	 * @return the host
	 */
	public String getHost() {
		return Host.getField();
	}
	
	@Override
	public String toString() {
		return Long.toString(this.ID.getField()).concat("@").concat(Host.getField());
	}
	
	

	
}
