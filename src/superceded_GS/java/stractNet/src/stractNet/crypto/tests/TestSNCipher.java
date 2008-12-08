package stractNet.crypto.tests;

import stractNet.exceptions.NoSecretKeyException;
import stractNet.crypto.SNCipher;

public class TestSNCipher {

	public static void main(String[] args) {

		String sp = "FB4656B4BE81A42C37C4A2614AAC659031B6832663940895568D5EBF94105A37B6821A752BF194B77E56C6D1F518E1A5139EC18598B732DB38091AF85CDA4F9F6793728F754F0BBD6961971FEEFB5BB085C4277E4142C2F1DA648F4E28FD2A63";
		String sg = "05";

		SNCipher Alice = new SNCipher("AliceCihper", sp, sg);
		SNCipher Bob = new SNCipher("BobCihper", sp, sg);

		// Each side Generates a private then public key.
		Alice.GenerateLocalKeys();
		Bob.GenerateLocalKeys();

		// Get Byte arrays of Public Keys
		byte[] AlicesPubKey = Alice.getPublicKey().getEncoded();
		byte[] BobsPubKey = Bob.getPublicKey().getEncoded();

		// Theoretical transfer of public keys across a network here.

		// Now have each side Generate their SecretKeys;
		Alice.GenerateSecretKey(BobsPubKey);
		Bob.GenerateSecretKey(AlicesPubKey);

		try {

			// /Test

			String s1 = "This is a test!!";
			byte[] b1 = s1.getBytes();

			System.out.print(s1.concat(" -> "));
			printByteArray(b1);
			System.out.println();

			byte[] be1 = Alice.Encrypt(b1);
			System.out.print("After Alice Encrypt(bytes): ");
			printByteArray(be1);
			System.out.println("After Alice Encrypt(string): "
					.concat(new String(be1)));
			System.out.println();

			byte[] bd1 = Bob.Decrypt(be1);
			System.out.print("After Bob Decrypt(bytes): ");
			printByteArray(bd1);
			System.out.println("After Bob Decrypt(string): ".concat(new String(
					bd1)));

			System.out.println();
			System.out.println();
			System.out.println();
			System.out.println();

			// Now send it back, modified.

			String s2 = new String(bd1);
			s2 = s2
					.concat("  I have received your test and am replying in kind.");
			byte[] b2 = s2.getBytes();

			System.out.print(s2.concat(" -> "));
			printByteArray(b2);
			System.out.println();

			byte[] be2 = Bob.Encrypt(b2);
			System.out.print("After Bob Encrypt(bytes): ");
			printByteArray(be2);
			System.out.println("After Bob Encrypt(string): ".concat(new String(
					be2)));
			System.out.println();

			byte[] bd2 = Alice.Decrypt(be2);
			System.out.print("After Alice Decrypt(bytes): ");
			printByteArray(bd2);
			System.out.println("After Alice Decrypt(string): "
					.concat(new String(bd2)));
			System.out.println();

		} catch (NoSecretKeyException nske) {
			System.err.println(nske.getMessage());
		}

		return;
	}

	private static void printByteArray(byte[] data) {
		for (byte b : data) {
			System.out.print(b);
			System.out.print(",");
		}
		System.out.println();

	}

}
