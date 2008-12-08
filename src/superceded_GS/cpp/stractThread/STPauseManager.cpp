///////////////////////////////////////////////////////////
//  STPauseManager.cpp
//  Implementation of the Class STPauseManager
//  Created on:      17-Sep-2008 8:02:24 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "STPauseManager.h"


STPauseManager::STPauseManager(){

}



STPauseManager::~STPauseManager(){

}





/**
 * Constructors
 */
STPauseManager::STPauseManager(String Name){

}


/**
 * Utilities
 */
int STPauseManager::getNumRunnables(){

	return 0;
}


int STPauseManager::getNumPauseables(){

	return 0;
}


int STPauseManager::getNumEnabled(){

	return 0;
}


int STPauseManager::getNumDisabled(){

	return 0;
}


/**
 * getStatus
 */
boolean STPauseManager::areAllEnabled(){

	return  NULL;
}


boolean STPauseManager::areAnyEnabled(){

	return  NULL;
}


/**
 * set Status -> ENABLE
 */
void STPauseManager::enableAll(){

}


void STPauseManager::enableAll(boolean block){

}


boolean STPauseManager::enable(String name){

	return  NULL;
}


boolean STPauseManager::enable(String name, boolean block){

	return  NULL;
}


/**
 * set Status -> DISABLE
 */
void STPauseManager::disableAll(){

}


void STPauseManager::disableAll(boolean block){

}


boolean STPauseManager::disable(String name){

	return  NULL;
}


boolean STPauseManager::disable(String name, boolean block){

	return  NULL;
}


/**
 * Internals
 */
void STPauseManager::_ModThreadEnableStatus_All(boolean status, boolean block){

}


boolean STPauseManager::_ModThreadEnableStatus(STRunnable stru, boolean status, boolean block){

	return  NULL;
}


boolean STPauseManager::_enable(STPauseable stp, boolean block){

	return  NULL;
}


boolean STPauseManager::_disable(STPauseable stp, boolean block){

	return  NULL;
}


long STPauseManager::getTimeOut(){

	return 0;
}


void STPauseManager::setTimeOut(long timeOut){

}