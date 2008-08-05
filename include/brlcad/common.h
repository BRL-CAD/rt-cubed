/*                      C O M M O N . H
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
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
/** @file Common.h
 *
 *  BRL-CAD core C++ interface:
 *      declares common understanding
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_COMMON_INCLUDED
#define BRLCAD_COMMON_INCLUDED

/// a define for the interface's binding
/** Meaningful values are for example __declspec(dllexport), __declspec(dllimport) or virtual.
    It has to be defined by the build environment (Makefile, *.vcproj etc.).
    The default is no special declaration. */
#ifndef BRLCAD_COREINTERFACE_EXPORT
#   define BRLCAD_COREINTERFACE_EXPORT
#endif


struct Vector3D {
    double coordinates[3];
};


namespace BRLCAD {
    class StringCalback {
    public:
        virtual ~StringCalback(void) {}

        /** return true: go on; false: stop
            The return value gives the calling function the possibility to optimize.
            However be aware the return value may be ignored. */
        virtual bool operator()(const char* string) = 0;

    protected:
        StringCalback(void) {}
        StringCalback(const StringCalback&) {}
        const StringCalback& operator=(const StringCalback&) {return *this;}
    };
}


#endif // BRLCAD_COMMON_INCLUDED
