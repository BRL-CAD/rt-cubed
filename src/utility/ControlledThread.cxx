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

ControlledThread::ControlledThread()
{
  this->threadName = "DEFAULT_THREAD_NAME";
  this->runCmd = false;
  this->runStatus = false;
}

ControlledThread::~ControlledThread()
{
}

bool ControlledThread::startup(){
  bool preRetVal = this->preStartupHook();


  bool postRetVal = this->preStartupHook();
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
