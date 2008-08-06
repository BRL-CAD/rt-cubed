///////////////////////////////////////////////////////////
//  SNCipher.h
//  Implementation of the Class SNCipher
//  Created on:      06-Aug-2008 7:49:25 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#if !defined(EA_430D9FBE_246B_4804_882D_CD6B526E2FBA__INCLUDED_)
#define EA_430D9FBE_246B_4804_882D_CD6B526E2FBA__INCLUDED_

#include "SNRoot.java"

class SNCipher : public SNRoot
{

public:
	SNCipher();
	virtual ~SNCipher();

	SNCipher(String Name, String sp, String sg);
	SNCipher(String Name, BigInteger sp, BigInteger sg);
	byte Decrypt(byte[] data) throw NoSecretKeyException;
	byte Encrypt(byte[] data) throw NoSecretKeyException;
	boolean GenerateLocalKeys();
	boolean GenerateSecretKey(byte[] otherGuysPublicKey);
	PublicKey getPublicKey();
	boolean hasPrivateKey();
	boolean hasPublicKey();
	boolean hasSecretKey();

private:
	Cipher dcipher;
	Cipher ecipher;
	BigInteger g;
	BigInteger p;
	PrivateKey privateKey;
	PublicKey publicKey;
	SecretKey secretKey;

};
#endif // !defined(EA_430D9FBE_246B_4804_882D_CD6B526E2FBA__INCLUDED_)
