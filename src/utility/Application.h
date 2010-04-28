/*                   A P P L I C A T I O N . H
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
/** @file Application.h
 *
 * Brief description
 *
 */

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

// system headers
#include <string>

// interface headers
#include "Date.h"
#include "Time.h"

/** Application is responsible for defining and handling command-line options
 * and, more importantly, for actually doing something.
 */
class Application
{
protected:
    Date _runDate;
    Time _runTime;

public:
    Application(int argc = 0, char *argv[] = 0);
    ~Application();

    /** main routine for an application, should only return when the
     * application is completed.
     */
    bool run();

    /** date when the application was compiled */
    Date buildDate() const;
    /** time of day when the application was compiled */
    Time buildTime() const;

    /** date when the application run-loop was started */
    Date runDate() const;
    /** time when the application run-loop was started */
    Time runTime() const;

    /** status message of how long app has been running */
    std::string uptime() const;

};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
