/*                      G L O B A L S . H
 * BRL-CAD
 *
 * Copyright (c) 2011 United States Government as represented by
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
/** @file globals.h
 *
 *  BRL-CAD core C++ interface:
 *      declares global functions which influence the behavior
 *      of the BRL-CAD core
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_GLOBALS_INCLUDED
#define BRLCAD_GLOBALS_INCLUDED

#include <brlcad/cicommon.h>


namespace BRLCAD {
    /// @name get BRL-CAD version information
    //@{
    int BRLCAD_COREINTERFACE_EXPORT  MajorVersion(void);
    int BRLCAD_COREINTERFACE_EXPORT  MinorVersion(void);
    int BRLCAD_COREINTERFACE_EXPORT  PatchVersion(void);
    //@}


    /// @name capturing the logging output
    //@{
    /// log handler (to be implemented by the caller)
    class LogHandler {
    public:
        virtual ~LogHandler(void) {}

        virtual void operator()(const char* logString) = 0;

    protected:
        LogHandler(void) {}
        LogHandler(const LogHandler&) {}
        const LogHandler& operator=(const LogHandler&) {return *this;}
    };

    void BRLCAD_COREINTERFACE_EXPORT RegisterLogHandler(LogHandler& logHandler);
    void BRLCAD_COREINTERFACE_EXPORT DeRegisterLogHandler(LogHandler& logHandler);
    //@}
}


#endif // BRLCAD_GLOBALS_INCLUDED
