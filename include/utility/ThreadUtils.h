/*                   T H R E A D U T I L S . H
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
/** @file ThreadUtils.h
 * ThreadUtils.h
 *
 */

#ifndef __THREADUTILS_H__
#define __THREADUTILS_H__

#include <QThread>

class ThreadUtils: public QThread
{
public:
    virtual ~ThreadUtils();

    void static sleep(unsigned long secs);
    void static usleep(unsigned long usecs);

private:
    ThreadUtils();
};

#endif /* __THREADUTILS_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
