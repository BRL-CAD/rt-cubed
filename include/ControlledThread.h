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

#include <QtCore/QString>
#include "GSThread.h"

class ControlledThread: public GSThread {
public:
	ControlledThread(QString threadname = "");
	virtual ~ControlledThread();

	void start();

	void shutdown();
	void terminate();
	void terminate(bool block);
	QString getThreadName();

protected:
	virtual bool preStartupHook();
	virtual bool postStartupHook();

	virtual bool preRunHook();
	void run();
	virtual void _run();
	virtual void _runLoopPass();
	virtual bool postRunHook();

	virtual bool preShutdownHook();
	virtual bool postShutdownHook();

	/* fields */
	QString threadName;
	bool runCmd;
	bool runStatus;
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
