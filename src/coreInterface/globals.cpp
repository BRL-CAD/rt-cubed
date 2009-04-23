/*                      G L O B A L S . C P P
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file globals.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implementats global functions which influence the behavior
 *      of the BRL-CAD core
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include "bu.h"

#include <brlcad/globals.h>


using namespace BRLCAD;


static int Logger
(
    genptr_t data,
    genptr_t string
) {
    if (data != 0) {
        LogHandler* logHandler = static_cast<LogHandler*>(data);
        const char* logString  = static_cast<const char*>(string);

        (*logHandler)(logString);
    }

    return 0;
}


void BRLCAD_COREINTERFACE_EXPORT RegisterLogHandler
(
    LogHandler& logHandler
) throw(bad_alloc) {
    if (!BU_SETJUMP)
        bu_log_add_hook(Logger, &logHandler);
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::RegisterLogHandler");
    }

    BU_UNSETJUMP;
}


void BRLCAD_COREINTERFACE_EXPORT DeRegisterLogHandler
(
    LogHandler& logHandler
) throw() {
    if (!BU_SETJUMP)
        bu_log_delete_hook(Logger, &logHandler);

    BU_UNSETJUMP;
}
