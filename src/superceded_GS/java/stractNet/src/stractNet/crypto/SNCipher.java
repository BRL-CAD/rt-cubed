package stractNet.crypto;

import java.math.BigInteger;
import javax.crypto.*;
import javax.crypto.spec.*;

import stractNet.SNRoot;
import stractNet.exceptions.NoSecretKeyException;

import java.security.*;
import java.security.spec.*;



public class SNCipher extends SNRoot {
	private BigInteger p;
	private	BigInteger g;
	private SecretKey secretKey;
	private PrivateKey privateKey;
	private PublicKey publicKey;
    private Cipher ecipher;
    private Cipher dcipher;

	
	public SNCipher(String Name, String sp, String sg) {
		super(Name);
		this.p = new BigInteger(sp,16);
		this.g = new BigInteger(sg,16);
	}

	public SNCipher(String Name, BigInteger sp, BigInteger sg) {
		super(Name);
		this.p = sp;
		this.g = sg;
	}

	
	public boolean GenerateLocalKeys() {
		try {
	        // Use the values to generate a key pair
			
			//Get instance of KeyPairGeneratro from factory
	        KeyPairGenerator keyGen = KeyPairGenerator.getInstance("DH");
	        
	        //Define the DH parameters I want.
	        DHParameterSpec dhSpec = new DHParameterSpec(this.p, this.g);
	        
	        //Initialize the KeyGen to the DH parameters
	        keyGen.initialize(dhSpec);
	        
	        //Generate my Keypair
	        KeyPair keypair = keyGen.generateKeyPair();
	    
	        // Get the generated public and private keys
	        this.privateKey = keypair.getPrivate();
	        this.publicKey = keypair.getPublic();
	    
	    } catch (java.security.InvalidAlgorithmParameterException e) {
	    	return false;
	    } catch (java.security.NoSuchAlgorithmException e) {
	    	return false;
	    }
	    return true;
	}

	public boolean GenerateSecretKey (byte[] otherGuysPublicKey) {
		try {
	       	    
	        // Convert the public key bytes into a PublicKey object
	        X509EncodedKeySpec x509KeySpec = new X509EncodedKeySpec(otherGuysPublicKey);
	        KeyFactory keyFact = KeyFactory.getInstance("DH");
	        PublicKey othersPublicKey = keyFact.generatePublic(x509KeySpec);
	    
	        // Prepare to generate the secret key with the private key and public key of the other party
	        KeyAgreement ka = KeyAgreement.getInstance("DH");
	        ka.init(privateKey);
	        ka.doPhase(othersPublicKey, true);
	    
	        // Generate the secret key
	        this.secretKey = ka.generateSecret("DES"); //DH?
	    

	    } catch (java.security.InvalidKeyException e) {
	    	return false;
	    } catch (java.security.spec.InvalidKeySpecException e) {
	    	return false;
	    } catch (java.security.NoSuchAlgorithmException e) {
	    	return false;
	    }
	
	    //initialize Ciphers
	    
	    try {
            ecipher = Cipher.getInstance("DES");
            dcipher = Cipher.getInstance("DES");
            ecipher.init(Cipher.ENCRYPT_MODE, this.secretKey);
            dcipher.init(Cipher.DECRYPT_MODE, this.secretKey);

        } catch (javax.crypto.NoSuchPaddingException e) {
	    	return false;
        } catch (java.security.NoSuchAlgorithmException e) {
	    	return false;
        } catch (java.security.InvalidKeyException e) {
	    	return false;
        }

	    
		return true;
	}


	public PublicKey getPublicKey() {
		return publicKey;
	}	
	
	
	public byte[] Encrypt (byte[] data) throws NoSecretKeyException {
		
		if (!this.hasSecretKey()) {throw new NoSecretKeyException("No Secret Key.");}
		if (data == null) {return null;}
		
		try {
			return this.ecipher.doFinal(data);
		} catch (javax.crypto.BadPaddingException e) {
	       return new byte[0];
        } catch (IllegalBlockSizeException e) {
           return new byte[0];
        }
	}
	
	public byte[] Decrypt (byte[] data) throws NoSecretKeyException {
		
		if (!this.hasSecretKey()) {throw new NoSecretKeyException("No Secret Key.");}
		if (data == null) {return null;}
		
		try {
             // Decrypt
            return dcipher.doFinal(data);
        } catch (javax.crypto.BadPaddingException e) {
            return new byte[0];
        } catch (IllegalBlockSizeException e) {
            return new byte[0];
        }
	}
	
	public boolean hasSecretKey() {
		if (this.secretKey == null) {
			return false;
		}
		return true;
	}
	
	public boolean hasPrivateKey() {
		if (this.privateKey == null) {
			return false;
		}
		return true;
	}
	
	public boolean hasPublicKey() {
		if (this.publicKey == null) {
			return false;
		}
		return true;
	}
	
}
