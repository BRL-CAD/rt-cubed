/*                  L O G G E R T E S T . C X X
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
/** @file loggerTest.cxx
 *
 * Brief description
 *
 */

#include "utility/Logger.h"

int main(int argc, char* argv[])
{
    Logger* log = Logger::getInstance();

    log->disableVerbose();
    log->logDEBUG("Testing DEBUG with Verbose OFF");
    log->logINFO("Testing INFO with Verbose OFF");
    log->logWARNING("Testing WARNING with Verbose OFF");
    log->logERROR("Testing ERROR with Verbose OFF");
    log->logFATAL("Testing FATAL with Verbose OFF");

    log->enableVerbose();
    log->logDEBUG("Testing DEBUG with Verbose ON");
    log->logINFO("Testing INFO with Verbose ON");
    log->logWARNING("Testing WARNING with Verbose ON");
    log->logERROR("Testing ERROR with Verbose ON");
    log->logFATAL("Testing FATAL with Verbose ON");


    return 0;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
