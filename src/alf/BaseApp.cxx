/*                       B A S E A P P . C X X
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
/** @file BaseApp.cxx
 *
 * Brief description
 *
 */

#include "BaseApp.h"
#include "AppLauncher.h"

BaseApp::BaseApp() : QThread()
{
    //Make sure the logger is initialized
    this->log = Logger::getInstance();
}

BaseApp::~BaseApp()
{
}

void BaseApp::run()
{
    this->log->logINFO("BaseApp", "Run CMD received.");
    this->_run();
    //this->exec();
    AppLauncher::exit(0);
}

void BaseApp::stop(int exitCode)
{
    this->log->logINFO("BaseApp", "Stop CMD received.");
    this->exit(exitCode);
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
