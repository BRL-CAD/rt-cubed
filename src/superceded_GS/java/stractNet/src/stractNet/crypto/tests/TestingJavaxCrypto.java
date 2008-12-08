package stractNet.crypto.tests;

import java.math.BigInteger;

import javax.crypto.*;
import javax.crypto.spec.*;
import java.security.*;
import java.security.spec.*;

public class TestingJavaxCrypto {
	
	public static void main(String[] args) {
		
		String sp = "FB4656B4BE81A42C37C4A2614AAC659031B6832663940895568D5EBF94105A37B6821A752BF194B77E56C6D1F518E1A5139EC18598B732DB38091AF85CDA4F9F6793728F754F0BBD6961971FEEFB5BB085C4277E4142C2F1DA648F4E28FD2A63";
		BigInteger p = new BigInteger(sp,16);
		
		String sg = "05";	
		BigInteger g = new BigInteger(sg,16);

				
		try {
	        // Use the values to generate a key pair
	        KeyPairGenerator keyGen = KeyPairGenerator.getInstance("DH");
	        DHParameterSpec dhSpec = new DHParameterSpec(p, g);
	        keyGen.initialize(dhSpec);
	        KeyPair keypair = keyGen.generateKeyPair();
	    
	        // Get the generated public and private keys
	        PrivateKey privateKey = keypair.getPrivate();
	        PublicKey publicKey = keypair.getPublic();
	    
	        // Send the public key bytes to the other party...
	        byte[] publicKeyBytes = publicKey.getEncoded();
	    
	        System.out.println(privateKey.toString());
	        System.out.println("\n");
	        System.out.println(publicKey.toString());
	        System.out.println("\n");
	        System.out.println(publicKeyBytes.toString());
	    
	        // Convert the public key bytes into a PublicKey object
	        X509EncodedKeySpec x509KeySpec = new X509EncodedKeySpec(publicKeyBytes);
	        KeyFactory keyFact = KeyFactory.getInstance("DH");
	        publicKey = keyFact.generatePublic(x509KeySpec);
	    
	        // Prepare to generate the secret key with the private key and public key of the other party
	        KeyAgreement ka = KeyAgreement.getInstance("DH");
	        ka.init(privateKey);
	        ka.doPhase(publicKey, true);
	    
	        // Specify the type of key to generate;
	        // see e458 Listing All Available Symmetric Key Generators
	        String algorithm = "DES";
	    
	        // Generate the secret key
	        SecretKey secretKey = ka.generateSecret(algorithm);
	        System.out.println(secretKey.toString());
	        
	        // Use the secret key to encrypt/decrypt data;
	        // see e462 Encrypting a String with DES
	    } catch (java.security.InvalidKeyException e) {
	    } catch (java.security.spec.InvalidKeySpecException e) {
	    } catch (java.security.InvalidAlgorithmParameterException e) {
	    } catch (java.security.NoSuchAlgorithmException e) {
	    }
	
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
}
