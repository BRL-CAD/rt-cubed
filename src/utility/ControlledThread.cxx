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

ControlledThread::ControlledThread(QString threadName)
{
  if (threadName.length() <= 0)
    {
      this->threadName = "DEFAULT_THREAD_NAME";
    }
  else
    {
      this->threadName = threadName;
    }
  this->runCmd = false;
  this->runStatus = false;
  this->internalThread = new GSThread();
}

ControlledThread::~ControlledThread()
{
  delete this->internalThread;
}

bool
ControlledThread::startup()
{
  bool preRetVal = this->preStartupHook();
  this->runCmd = true;
  bool postRetVal = this->preStartupHook();
}

bool
ControlledThread::shutdown()
{
  bool preRetVal = this->preShutdownHook();
  this->runCmd = false;
  bool postRetVal = this->preShutdownHook();
}

void
ControlledThread::run()
{
  this->preRunHook();
  this->runStatus = true;

  this->_run();

  this->postRunHook();
  this->runStatus = true;
}

void
ControlledThread::_run()
{
  while (this->runCmd)
    {
      this->_runLoopPass();
    }
}

void
ControlledThread::_runLoopPass()
{
  //DOES NOTHING BY DEFAULT
  GSThread::msleep(123);
}

/**
 * User hook.  Called immediately after ControlledThread::startup() is called but prior to 'runCmd' being set to true;
 */
bool
ControlledThread::preStartupHook()
{
  return true;
}

/**
 * User hook.  Called immediately after 'runCmd' is set to true;
 */
bool
ControlledThread::postStartupHook()
{
  return true;
}

bool
ControlledThread::preRunHook()
{
  return true;
}

bool
ControlledThread::postRunHook()
{
  return true;
}

bool
ControlledThread::preShutdownHook()
{
  return true;
}

bool
ControlledThread::postShutdownHook()
{
  return true;
}


// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
