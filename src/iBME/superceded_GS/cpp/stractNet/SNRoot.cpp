///////////////////////////////////////////////////////////
//  SNRoot.cpp
//  Implementation of the Class SNRoot
//  Created on:      06-Aug-2008 7:50:22 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "SNRoot.h"

///////////////////////////////////////////////////////////////////////
/*
 *
 * xSTRUCTORS
 *
 */
///////////////////////////////////////////////////////////////////////

SNRoot::SNRoot(String Name) {
	this->ObjName = Name;
	this->MS_local = SNRoot::MS_Global;
}

SNRoot::~SNRoot() {

}

///////////////////////////////////////////////////////////////////////
/*
 *
 * METHODS
 *
 */
///////////////////////////////////////////////////////////////////////

MessagingSystem& SNRoot::getLocalMS() {
	return this->MS_Local;
}

void SNRoot::setLocalMS(MessagingSystem& ms) {
	this->MS_Local = ms;
}

/**
 * Quick & Dirty getter'n'setters -> simplifies inclusion into Strings
 */
String SNRoot::gON() {
	return this->ObjName;
}
void SNRoot::sON(String name) {
	this->ObjName = name;
}

//TODO clean up the internal STDOUT and STDERR
void SNRoot::err(String message) {
	SNRoot::serr(this->gON() + ":\t" + message + "\n");
}

void SNRoot::out(String message) {
	SNRoot::sout(this->gON() + ":\t" + message + "\n");
}

///////////////////////////////////////////////////////////////////////
/*
 *
 * STATICS
 *
 */
///////////////////////////////////////////////////////////////////////


//TODO Eliminate the local and global MS passing via statics. Possible setup Singleton config
void SNRoot::setGlobalMS(MessagingSystem& ms) {
	SNRoot::MS_Global = ms;
}

void SNRoot::serr(String message) {
	cerr << message;
}

void SNRoot::sout(String message) {
	cout << message;
}

MessagingSystem& SNRoot::getGlobalMS() {
	return SNRoot::MS_Global;
}
