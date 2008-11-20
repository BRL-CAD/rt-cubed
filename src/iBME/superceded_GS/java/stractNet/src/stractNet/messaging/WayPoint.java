package stractNet.messaging;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Date;

import stractNet.SNRoot;

public class WayPoint extends SNRoot {

	private long time;
	private String Host;

	/*
	 * Manual Constructor
	 */
	public WayPoint(long time, String host) {
		super("WayPoint");
		this.time = time;
		Host = host;
	}


	public WayPoint(String host) {
		this(new Date().getTime(), host);
	}


	/*
	 * Deserializing Constructor
	 */
	public WayPoint(byte[] data) throws IOException {
		this(new DataInputStream(new ByteArrayInputStream(data)));
	}

	public WayPoint(DataInputStream in) throws IOException {
		super("WayPoint");

		// Deserialize Header Components
		this.time = in.readLong();
		int strLen = in.readInt();
		char[] c = new char[strLen];

		for (int i = 0; i < strLen; i++) {
			c[i] = in.readChar();
		}
		this.Host = new String(c);

	}

	public byte[] Serialize() {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		try {
			// Write in Header
			out.writeLong(this.time);
			out.writeInt(this.Host.length()); // chars are 2 bytes
			out.writeChars(this.Host);

			return baos.toByteArray();
		} catch (IOException ioe) {
			SNRoot.serr("IOException in Serialize()", 0);
		}

		return null;

	}

	/**
	 * @return the host
	 */
	public String getHost() {
		return Host;
	}

	/**
	 * @return the time
	 */
	public long getTime() {
		return time;
	}

	@Override
	public String toString() {
		return Host.concat("@").concat(Long.toString(this.time));
	}

}
