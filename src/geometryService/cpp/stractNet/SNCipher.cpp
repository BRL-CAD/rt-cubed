///////////////////////////////////////////////////////////
//  SNCipher.cpp
//  Implementation of the Class SNCipher
//  Created on:      06-Aug-2008 7:49:25 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "SNCipher.h"


SNCipher::SNCipher(){

}



SNCipher::~SNCipher(){

}





SNCipher::SNCipher(String Name, String sp, String sg){

}


SNCipher::SNCipher(String Name, BigInteger sp, BigInteger sg){

}


byte SNCipher::Decrypt(byte[] data) throw NoSecretKeyException{

	return  NULL;
}


byte SNCipher::Encrypt(byte[] data) throw NoSecretKeyException{

	return  NULL;
}


boolean SNCipher::GenerateLocalKeys(){

	return  NULL;
}


boolean SNCipher::GenerateSecretKey(byte[] otherGuysPublicKey){

	return  NULL;
}


PublicKey SNCipher::getPublicKey(){

	return  NULL;
}


boolean SNCipher::hasPrivateKey(){

	return  NULL;
}


boolean SNCipher::hasPublicKey(){

	return  NULL;
}


boolean SNCipher::hasSecretKey(){

	return  NULL;
}