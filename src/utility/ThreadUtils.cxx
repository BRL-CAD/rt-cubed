/*                 T H R E A D U T I L S . C X X
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
/** @file ThreadUtils.cxx
 * ThreadUtils.cpp
 *
 *  Created on: Apr 21, 2010
 *      Author: dloman
 */

#include "ThreadUtils.h"

ThreadUtils::ThreadUtils()
{
    // TODO Auto-generated constructor stub

}

ThreadUtils::~ThreadUtils()
{
    // TODO Auto-generated destructor stub
}
void ThreadUtils::sleep(unsigned long secs) {
    QThread::sleep(secs);
}

void ThreadUtils::usleep(unsigned long usecs) {
    QThread::usleep(usecs);
}
// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
