/*              C O N T R O L L E D T H R E A D . H
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
/** @file ControlledThread.h
 *
 */

#ifndef __CONTROLLEDTHREAD_H__
#define __CONTROLLEDTHREAD_H__

#include "GSThread.h"

#include <QtCore/QString>
#include <QtCore/QMutex>

class ControlledThread : public GSThread
{
public:
	ControlledThread(QString threadname = "");
	virtual ~ControlledThread();

	void start();
	void run();

	void shutdown();
	void terminate();
	void terminate(bool block);
	QString getThreadName();

	bool getRunStatus();
	bool getRunCmd();

protected:
	virtual bool preStartupHook();
	virtual bool postStartupHook();

	virtual bool preRunHook();
	virtual void _run();
	virtual void _runLoopPass();
	virtual bool postRunHook();

	virtual bool preShutdownHook();
	virtual bool postShutdownHook();

	void setRunCmd(bool newVal);
	void setRunStatus(bool newVal);

private:

	/* fields */
	QString threadName;

	QMutex runCmdLock;
	bool runCmd;

	QMutex runStatusLock;
	bool runStatus;

	/* Disable copy cstr and =operator */
	ControlledThread(ControlledThread const&){};
	ControlledThread& operator=(ControlledThread const&){};
};

#endif /* __CONTROLLEDTHREAD_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
