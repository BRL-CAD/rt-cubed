package stractNet.util;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Random;

import stractNet.SNRoot;

public class SNUtilities extends SNRoot {

	public SNUtilities() {
		super("SNUtilities");
	}

	public static byte[] intToByteArray(int i) {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		try {
			out.writeInt(i);
			return baos.toByteArray();
		} catch (IOException ioe) {
			SNRoot.serr("IOException in intToByteArray()",0);
		}

		return null;
	}

	public static byte[] intArrayToByteArray(int[] ia) {

		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		try {
			for (int i : ia) {
				out.writeInt(i);
			}
			return baos.toByteArray();
		} catch (IOException ioe) {
			SNRoot.serr("IOException in intArrayToByteArray()",0);
		}

		return null;
	}


	public static byte[] longToByteArray(long l) {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		try {
			out.writeLong(l);
			return baos.toByteArray();
		} catch (IOException ioe) {
			SNRoot.serr("IOException in longToByteArray()",0);
		}

		return null;
	}

	public static byte[] longArrayToByteArray(long[] la) {

		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream out = new DataOutputStream(baos);

		try {
			for (long l : la) {
				out.writeLong(l);
			}
			return baos.toByteArray();
		} catch (IOException ioe) {
			SNRoot.serr("IOException in longArrayToByteArray()",0);
		}

		return null;
	}


	
	
	
	
	
	
	public static int byteArrayToInt(byte[] b) {

		ByteArrayInputStream bais = new ByteArrayInputStream(b);
		DataInputStream in = new DataInputStream(bais);

		try {
			return in.readInt();
		} catch (IOException ioe) {
			SNRoot.serr("IOException in byteArrayToInt()",0);
		}

		return 0;
	}

	
	public static int[] byteArrayToIntArray(byte[] b) {

		ByteArrayInputStream bais = new ByteArrayInputStream(b);
		DataInputStream in = new DataInputStream(bais);

		int[] out = new int[b.length / 4];
		
		try {
			for (int cnt = 0; cnt < out.length; cnt++) {
				out[cnt] = in.readInt();
			}
			return out;
		} catch (IOException ioe) {
			SNRoot.serr("IOException in byteArrayToInt()",0);
		}

		return null;
	}

	
	
	
	
	public static long byteArrayToLong(byte[] b) {

		ByteArrayInputStream bais = new ByteArrayInputStream(b);
		DataInputStream in = new DataInputStream(bais);

		try {
			return in.readLong();
		} catch (IOException ioe) {
			SNRoot.serr("IOException in byteArrayToLong()",0);
		}

		return 0L;
	}

	
	public static long[] byteArrayToLongArray(byte[] b) {

		ByteArrayInputStream bais = new ByteArrayInputStream(b);
		DataInputStream in = new DataInputStream(bais);

		long[] out = new long[b.length / 8];
		
		try {
			for (int cnt = 0; cnt < out.length; cnt++) {
				out[cnt] = in.readLong();
			}
			return out;
		} catch (IOException ioe) {
			SNRoot.serr("IOException in byteArrayToInt()",0);
		}

		return null;
	}

	
	public static byte[] randomByteArrayGenerator() {
		Random r = new Random(); //random size?
		return randomByteArrayGenerator(r.nextInt(100));		
	}
	public static byte[] randomByteArrayGenerator(int length) {
		byte[] ba = new byte [length];
		Random r = new Random();
		r.nextBytes(ba);
		return ba;
	}
	
}
