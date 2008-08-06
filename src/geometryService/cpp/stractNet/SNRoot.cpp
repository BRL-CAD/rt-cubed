///////////////////////////////////////////////////////////
//  SNRoot.cpp
//  Implementation of the Class SNRoot
//  Created on:      06-Aug-2008 7:50:22 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "SNRoot.h"


SNRoot::SNRoot(){

}



SNRoot::~SNRoot(){

}





SNRoot::SNRoot(String Name){

}


void SNRoot::err(String message, int vLevel){

}


MessagingSystem SNRoot::getGlobalMS(){

	return  NULL;
}


MessagingSystem SNRoot::getLocalMS(){

	return  NULL;
}


/**
 * Quick & Dirty getter'n'setters -> simplifies inclusion into Strings
 */
String SNRoot::gON(){

	return  NULL;
}


String SNRoot::gOT(){

	return  NULL;
}


void SNRoot::out(String message, int vLevel){

}


void SNRoot::serr(String message, int vLevel){

}


void SNRoot::setGlobalMS(MessagingSystem ms){

}


void SNRoot::setLocalMS(MessagingSystem ms){

}


void SNRoot::sON(String name){

}


/**
 * TODO Clean up out,err,sout,err routing.
 */
void SNRoot::sout(String message, int vLevel){

}