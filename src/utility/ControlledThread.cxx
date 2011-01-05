/*            C O N T R O L L E D T H R E A D . C X X
 * BRLCAD
 *
 * Copyright (c) 2010 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file ControlledThread.cxx
 *
 */

#include "ControlledThread.h"
#include "Logger.h"
#include <QtCore/QMutexLocker>

ControlledThread::ControlledThread(QString threadName) {
	if (threadName.length() <= 0) {
		this->threadName = "DEFAULT_THREAD_NAME";
	} else {
		this->threadName = threadName;
	}
	this->setRunCmd(false);
	this->setRunStatus(false);
}

ControlledThread::~ControlledThread() {}

void ControlledThread::start() {
	bool preRetVal = this->preStartupHook();
	this->setRunCmd(true);
	GSThread::start(); /* call super class start */
	bool postRetVal = this->postStartupHook();
}

void
ControlledThread::shutdown() {
	this->terminate();
}

void
ControlledThread::terminate() {
	this->terminate(true);
}

void ControlledThread::terminate(bool block) {

	bool preRetVal = this->preShutdownHook();
	this->setRunCmd(false);

	quint64 maxFailsafeTimeMS = 5 * 1000;

	if (block) {

		quint64 startT = Logger::getCurrentTime();
		quint64 stopT = 0;
		while (this->getRunStatus()) {
			GSThread::msleep(100); //TODO need a failsafe here.
			stopT = Logger::getCurrentTime();

			if ((stopT - startT) >= maxFailsafeTimeMS) {
				Logger::getInstance()->logWARNING("ControlledThread", "terminate(block=true) reached failsafe.  Forcefully stopping thread.");
				GSThread::terminate();
				break;
			}
		}
	}

	bool postRetVal = this->postShutdownHook();
}

void ControlledThread::run() {
	if(!this->preRunHook())
		return;

	this->setRunCmd(true);
	this->setRunStatus(true);
	this->_run();
	this->setRunStatus(false);

	if(!this->postRunHook())
		return;
}

void ControlledThread::_run() {
	while (this->getRunCmd()) {
		this->_runLoopPass();
	}
}

void ControlledThread::_runLoopPass() {
	//DOES NOTHING BY DEFAULT
	GSThread::msleep(1);
}

/**
 * User hook.  Called immediately after ControlledThread::startup() is called but prior to 'runCmd' being set to true;
 */
bool ControlledThread::preStartupHook() {
	return true;
}

/**
 * User hook.  Called immediately after 'runCmd' is set to true;
 */
bool ControlledThread::postStartupHook() {
	return true;
}

bool ControlledThread::preRunHook() {
	return true;
}

bool ControlledThread::postRunHook() {
	return true;
}

bool ControlledThread::preShutdownHook() {
	return true;
}

bool ControlledThread::postShutdownHook() {
	return true;
}

QString
ControlledThread::getThreadName()
{
	return this->threadName;
}

bool
ControlledThread::getRunCmd()
{
	QMutexLocker(&this->runCmdLock);
	return this->runCmd;
}

bool
ControlledThread::getRunStatus()
{
	QMutexLocker(&this->runStatusLock);
	return this->runStatus;
}

void
ControlledThread::setRunCmd(bool newVal) {
	QMutexLocker(&this->runCmdLock);
	this->runCmd = newVal;
}

void
ControlledThread::setRunStatus(bool newVal) {
	QMutexLocker(&this->runStatusLock);
	this->runStatus = newVal;
}

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
