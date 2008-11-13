/*                      O B J E C T . H
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
/** @file Object.h
 *
 *  BRL-CAD core C++ interface:
 *      database object declaration
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_OBJECT_INCLUDED
#define BRLCAD_OBJECT_INCLUDED

#include <brlcad/common.h>


struct directory;
struct db_i;


namespace BRLCAD {
    class BRLCAD_COREINTERFACE_EXPORT Object {
    public:
        virtual ~Object(void) throw();

        virtual Object*     Clone(void) const = 0;
        virtual void        Delete(void)      = 0;

        // these two functions can be used to determine the type of the object
        static const char*  ClassName(void) throw() {
            return "Object";
        }
        virtual const char* Type(void) const  = 0;

        // for all objects
        const char*         Name(void) const throw();
        void                SetName(const char* name) throw();

    protected:
        directory* m_pDir;
        db_i*      m_dbip;

        Object(directory* m_pDir = 0,
               db_i*      m_dbip = 0) throw();
        Object(const Object& original) throw();
        const Object& operator=(const Object& original) throw();

        friend class Database;

    private:
        // holds Objects's name if not connected to a database
        char* m_name;
    };
}


#endif // BRLCAD_OBJECT_INCLUDED
