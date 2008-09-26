/*                      D A T A B A S E . H
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
/** @file Database.h
 *
 *  BRL-CAD core C++ interface:
 *      declares a handle on a writable database
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_DATABASE_INCLUDED
#define BRLCAD_DATABASE_INCLUDED

#include <brlcad/ConstDatabase.h>


struct rt_wdb;


namespace BRLCAD {
    class Database : public ConstDatabase {
    public:
        /// creates a new in-memory database with default _GLOBAL object
        Database(void) throw();
        virtual ~Database(void) throw();

        /// loads a BRL-CAD database file (*.g) into the memory
        /** The old content of the in-memory database will be discarded.
            The file will be opened for reading only and closed after finishing the operation. */
        virtual bool                            Load(const char* fileName) throw();
        bool                                    Save(const char* fileName) throw();

        BRLCAD_COREINTERFACE_EXPORT void        SetTitle(const char* title) throw();

    private:
        rt_wdb* m_wdbp;

        Database(const Database&) throw();                  // not implemented
        const Database& operator=(const Database&) throw(); // not implemented
    };
}


#endif // BRLCAD_DATABASE_INCLUDED
