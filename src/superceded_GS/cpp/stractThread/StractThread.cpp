///////////////////////////////////////////////////////////
//  StractThread.cpp
//  Implementation of the Class StractThread
//  Created on:      17-Sep-2008 8:02:25 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "StractThread.h"


StractThread::StractThread(){

}



StractThread::~StractThread(){

}





void StractThread::out(String message){

}


void StractThread::err(String message){

}


/**
 * TODO Clean up out,err,sout,err routing.
 */
void StractThread::sout(String message){

}


void StractThread::serr(String message){

}


/**
 * Quick & Dirty getters -> simplifies inclusion into Strings
 */
String StractThread::gON(){

	return  NULL;
}


String StractThread::gOT(){

	return  NULL;
}


boolean StractThread::Implements(Object object, String Interface){

	return  NULL;
}


boolean StractThread::waitForThreadRunStatusChange(STRunnable stru, boolean toStatus){

	return  NULL;
}


boolean StractThread::waitForThreadRunStatusChange(STRunnable stru, boolean toStatus, long timeOutInMS){

	return  NULL;
}


boolean StractThread::waitForThreadEnableStatusChange(STPauseable stp, boolean toStatus){

	return  NULL;
}


boolean StractThread::waitForThreadEnableStatusChange(STPauseable stp, boolean toStatus, long timeOutInMS){

	return  NULL;
}