/*                      O B J E C T . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by
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


struct resource;
struct directory;
struct rt_db_internal;
struct db_i;


namespace BRLCAD {
    class BRLCAD_COREINTERFACE_EXPORT Object {
    public:
        virtual ~Object(void) throw();

        // these two functions can be used to determine the type of the object
        static const char*  ClassName(void) throw();
        virtual const char* Type(void) const  = 0;

        // for all objects
        const char*         Name(void) const throw();
        void                SetName(const char* name) throw();

    protected:
        resource*       m_resp;
        directory*      m_pDir;
        rt_db_internal* m_ip;
        db_i*           m_dbip;

        Object(void) throw();
        Object(resource*       resp,
               directory*      pDir,
               rt_db_internal* ip,
               db_i*           dbip) throw();
        Object(const Object& original) throw();
        const Object& operator=(const Object& original) throw();

        friend class Database;

    private:
        // holds Objects's name if not connected to a database
        char* m_name;
    };
}


#endif // BRLCAD_OBJECT_INCLUDED
