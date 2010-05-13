/*                A P P L A U N C H E R . C X X
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
/** @file AppLauncher.cxx
 *
 * Launchpad for applications.
 *
 */

#include <iostream>
#include "AppLauncher.h"

AppLauncher::AppLauncher(int& argc, char** argv, BaseApp* app) :
QCoreApplication(argc, argv), _app(app)
{
}

AppLauncher::~AppLauncher()
{
}

int AppLauncher::exec()
{
    /* Fire off the thread prior to entering the event loop */
    this->_app->start();
    return QCoreApplication::exec();
}

void AppLauncher::exit(int exitCode)
{
    Logger::getInstance()->logINFO("AppLauncher", "Stop CMD received.");
    QCoreApplication::exit(exitCode);
}
// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
