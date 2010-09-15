/*                    G S T H R E A D . C X X
 * BRL-CAD
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
/** @file GSThread.cxx
 *
 * Brief description
 *
 */

#include "GSThread.h"

QList<GSThread*> GSThread::threads;

GSThread::GSThread()
{
}

GSThread::~GSThread()
{
}

void
GSThread::sleep(unsigned long secs)
{
  QThread::sleep(secs);
}

void
GSThread::msleep(unsigned long msecs)
{
  QThread::msleep(msecs);
}

void
GSThread::usleep(unsigned long usecs)
{
  QThread::usleep(usecs);
}


void
GSThread::addThread(GSThread* thread)
{
  bool exists = GSThread::threads.contains(thread);

  if (!exists) {
    GSThread::threads.append(thread);
  } else {
    //Todo possible warning for duplicate threads in the list?
  }
}

void
GSThread::remThread(GSThread* thread)
{
  bool exists = GSThread::threads.contains(thread);

  if (exists) {
    GSThread::threads.removeAll(thread);
  } else {
    //Todo possible warning for attempting to remove a thread not in the list?
  }
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
