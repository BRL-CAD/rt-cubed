import java.io.ByteArrayOutputStream;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.UUID;

/*                      N E T M S G . J A V A
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/**
 * @file NetMsg.java
 * 
 *       Description -
 * 
 * 
 *       Author - David Loman
 * 
 */

public abstract class AbstractMsg {
	private int msgType;
	private String msgUUID;
	private String reUUID;

	public AbstractMsg() {

	}

	public AbstractMsg(int mType, String mUUID, String rUUID) {
		this.msgType = mType;
		this.msgUUID = mUUID;
		this.reUUID = rUUID;
	}

	public AbstractMsg(byte[] data) {
		this(new DataInputStream(new ByteArrayInputStream(data)));
	}

	public AbstractMsg(DataInputStream dis) {
		this.deserialize(dis);
	}

	// "upgrader" constructor
	public AbstractMsg(NetMsg msg, DataInputStream dis) {
		// Get values from msg
		this.msgType = msg.getMsgType();
		this.msgUUID = msg.getMsgUUID();
		this.reUUID = msg.getReUUID();

		// then call the subclass specific deserializer
		this._deserialize(dis);
	}

	/*
	 * Serialize
	 */
	public byte[] Serialize() {
		ByteArrayOutputStream fullBaos = new ByteArrayOutputStream();
		DataOutputStream fullDos = new DataOutputStream(fullBaos);

		this.serialize(fullDos);

		return fullBaos.toByteArray();
	}

	public void serialize(DataOutputStream fullDos) {
		ByteArrayOutputStream bodyBaos = new ByteArrayOutputStream();
		DataOutputStream bodyDos = new DataOutputStream(bodyBaos);

		try {

			/*
			 * Serialize header elements
			 */
			// msgType
			bodyDos.writeInt(this.getMsgType());

			// MsgUUID
			this.msgUUID = UUID.randomUUID().toString();
			bodyDos.writeInt(this.msgUUID.length());
			// Gotta do this since java Chars are Unicode
			bodyDos.write(this.msgUUID.getBytes("US-ASCII"));

			// ReUUID
			this.reUUID = UUID.randomUUID().toString();
			bodyDos.writeInt(this.reUUID.length());
			// Gotta do this since java Chars are Unicode
			bodyDos.write(this.reUUID.getBytes("US-ASCII"));

			//for (byte b: msgUUID.getBytes("US-ASCII")) { System.out.print(b + " ");}
			//System.out.println();

			/*
			 * Get any subclass Body elements
			 */
			this._serialize(bodyDos);

			byte[] ba = bodyBaos.toByteArray();

			/*
			 * Prepend the MsgLen
			 */

			// Write the length of all the data in the message.
			fullDos.writeInt(ba.length);

			// Write in all the data
			fullDos.write(ba);

			System.out.println("Serialized an AbstractMsg with a length of " + (ba.length + 4));
		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	abstract protected void _serialize(DataOutputStream dos);

	/*
	 * Deserialize
	 */

	public void deserialize(DataInputStream dis) {

		try {
			this.msgType = dis.readInt();

			int msgUUIDlen = dis.readInt();
			byte[] baMsgUUID = new byte[msgUUIDlen];
			dis.read(baMsgUUID, 0, msgUUIDlen);
			this.msgUUID = new String(baMsgUUID);

			int reUUIDlen = dis.readInt();
			byte[] baReUUID = new byte[reUUIDlen];
			dis.read(baReUUID, 0, reUUIDlen);
			
			//for (byte b: baReUUID) { System.out.print(b + " ");}
			//System.out.println();
			
			this.reUUID = new String(baReUUID);

			this._deserialize(dis);

		} catch (IOException e) {
			e.printStackTrace();
		}

	}

	abstract protected void _deserialize(DataInputStream dis);

	/*
	 * Getters n Setters
	 */

	public int getMsgType() {
		return msgType;
	}

	public void setMsgType(int msgType) {
		this.msgType = msgType;
	}

	public String getMsgUUID() {
		return msgUUID;
	}

	public void setMsgUUID(String msgUUID) {
		this.msgUUID = msgUUID;
	}

	public String getReUUID() {
		return reUUID;
	}

	public void setReUUID(String reUUID) {
		this.reUUID = reUUID;
	}
	
	public String toString() {
		String out = "";
		out += this.getClass().getSimpleName() + "\t ";
		out += "msgType: " + this.msgType + "\t ";
		out += "msgUUID: " + this.msgUUID + "\t ";
		out += "reUUID: " + this.reUUID + "\t ";
		
		out += this._toString();
		return out;
	}
	protected abstract String _toString();
	
	public void printMe() {
		System.out.println(this.toString());
	}
	
}

















