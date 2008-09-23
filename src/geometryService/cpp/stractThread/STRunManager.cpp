///////////////////////////////////////////////////////////
//  STRunManager.cpp
//  Implementation of the Class STRunManager
//  Created on:      17-Sep-2008 8:02:25 AM
//  Original author: david.h.loman
///////////////////////////////////////////////////////////

#include "STRunManager.h"


STRunManager::STRunManager(){

}



STRunManager::~STRunManager(){

}





/**
 * Constructors
 */
STRunManager::STRunManager(String Name){

}


/**
 * Utilities
 */
int STRunManager::getNumThreads(){

	return 0;
}


int STRunManager::getNumRunning(){

	return 0;
}


int STRunManager::getNumNotRunning(){

	return 0;
}


/**
 * Add-ers and Rem-ers
 */
void STRunManager::addDoNotExecute(String name, STRunnableI stru){

}


boolean STRunManager::addExecute(String name, STRunnableI stru){

	return  NULL;
}


STRunnableI STRunManager::rem(String name){

	return  NULL;
}


/**
 * getStatus
 */
boolean STRunManager::areAllThreadsRunning(){

	return  NULL;
}


boolean STRunManager::areAnyThreadsRunning(){

	return  NULL;
}


boolean STRunManager::areAllStatusRunning(){

	return  NULL;
}


boolean STRunManager::areAnyStatusRunning(){

	return  NULL;
}


/**
 * set Status -> RUN
 */
void STRunManager::executeAll(){

}


void STRunManager::executeAll(boolean block){

}


boolean STRunManager::execute(String name){

	return  NULL;
}


boolean STRunManager::execute(String name, boolean block){

	return  NULL;
}


/**
 * set Status -> STOP
 */
void STRunManager::stopAll(){

}


void STRunManager::stopAll(boolean block){

}


boolean STRunManager::stop(String name){

	return  NULL;
}


boolean STRunManager::stop(String name, boolean block){

	return  NULL;
}


boolean STRunManager::stop_int(STRunnableI stru, boolean block){

	return  NULL;
}


/**
 * private void _ModThreadRunStatus_All(boolean status, boolean block) {
 * ArrayList<String> toRem = new ArrayList<String>();  synchronized (this.Pool) {
 * for (String s : this.Pool.keySet()) {  STRunnableI stru = this.Pool.get(s);  if
 * (stru.getRunStatus() != status) { this._ModThreadRunStatus(stru, status, block);
 * } if (status == false) { toRem.add(s); } }  for (String s : toRem) { this.Pool.
 * remove(s); }  }  for (STRunnableI stru : this.Pool.values()) { this.
 * _ModThreadRunStatus(stru, status, block); } }  private boolean
 * _ModThreadRunStatus(STRunnableI stru, boolean status, boolean block) {  null
 * check if (stru == null) { return false; }  if ((stru.getThread() == null) &&
 * (status == false)) { null thread, but Stop requested. return true; } else if
 * ((stru.getThread() == null) && (status == true)) { null thread, Start requested.
 * return this._start(stru, block); }  if (stru.getThread().isAlive() != status) {
 * if (status == false) { return this._stop(stru, block); } else { return this.
 * _start(stru, block); } }  return stru.getThread().isAlive(); } private boolean
 * _start(STRunnableI stru, boolean block) { null check if (stru == null) { return
 * false; }  stru.start(); // call start() not run() !!!!!!  if (block) {
 * StractThread.waitForThreadRunStatusChange(stru, true, timeOut); }  return stru.
 * getThread().isAlive(); }  private boolean _stop(STRunnableI stru, boolean block)
 * { null check if (stru == null) { return false; }  stru.stop();  if (block) {
 * StractThread.waitForThreadRunStatusChange(stru, false, timeOut); }  return stru.
 * getThread().isAlive(); }
 */
long STRunManager::getTimeOut(){

	return 0;
}


void STRunManager::setTimeOut(long timeOut){

}
