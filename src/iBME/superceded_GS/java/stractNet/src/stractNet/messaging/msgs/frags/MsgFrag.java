package stractNet.messaging.msgs.frags;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

import stractNet.SNRoot;

public abstract class MsgFrag<E> extends SNRoot {
	protected E field;
	protected int MFType;

	
	protected MsgFrag(String name, E in, int mfType){
		super(name);
		this.field = in;
		this.MFType = mfType;
	}

	
	protected MsgFrag(String name, DataInputStream in, int mfType) {
		super(name);
		this.Deserialize(in);
		this.MFType = mfType;
	}

	/*
	 * Abstracts
	 */

	protected abstract void Serialize_Specific(DataOutputStream out);

	protected abstract void Deserialize(DataInputStream in);

	public byte[] Serialize() {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		try {
			this.Serialize(out);
			return baos.toByteArray();
		} catch (IOException e) {
			this.err("IOException in Serialize()", 0);
		}
		return null;
	}

	public void Serialize(DataOutputStream out) throws IOException {
		out.writeInt(this.MFType);
		this.Serialize_Specific(out);
	}

	public E getField() {
		return this.field;
	}

	public void setField(E val) {
		this.field = val;
	}
	
	/**
	 * @return the mFType
	 */
	public int getMFType() {
		return MFType;
	}


	@Override
	public String toString() {
		return (this.field + "(" + this.getClass().getSimpleName() + ")");
	}





	public static final int mftBoolean = 0;
	public static final int mftDouble = 1;
	public static final int mftFloat = 2;
	public static final int mftInteger = 3;
	public static final int mftLong = 4;
	public static final int mftShort = 5;
	public static final int mftString = 6;
	public static final int mftWaypoint = 7;
	public static final int mftByteArray = 8;

	
	
}
