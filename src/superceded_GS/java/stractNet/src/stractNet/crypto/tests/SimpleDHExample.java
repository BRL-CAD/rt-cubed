package stractNet.crypto.tests;
import java.math.BigInteger;

public class SimpleDHExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		String sp = "FB4656B4BE81A42C37C4A2614AAC659031B6832663940895568D5EBF94105A37B6821A752BF194B77E56C6D1F518E1A5139EC18598B732DB38091AF85CDA4F9F6793728F754F0BBD6961971FEEFB5BB085C4277E4142C2F1DA648F4E28FD2A63";
		BigInteger p = new BigInteger(sp,16);
		
		String sg = "05";	
		BigInteger g = new BigInteger(sg,16);
		
		//p and g are hard coded into Alice and Bob
		
		//Alice picks a number
		BigInteger a = new BigInteger("8",10);
		
		//Bob picks a number
		BigInteger b = new BigInteger("9",10);
		
		//Alice calculates A
		BigInteger A = g.modPow(a, p);		
		
		//Bob calculates B
		BigInteger B = g.modPow(b, p);		
		
		
		//A and B are sent in the clear!!!!!
		System.out.println("Data in the clear (A): " + A.toString());
		System.out.println("Data in the clear (B): " + B.toString());
		
		//Alice Calculates K
		BigInteger AliceK = B.modPow(a, p);		
		
		//Bob Calculates K
		BigInteger BobK = A.modPow(b, p);		
			
		System.out.println("\n");
		System.out.println("Alice: " + AliceK.toString());
		System.out.println("Bob:   " + BobK.toString());
		
		
	}

}








