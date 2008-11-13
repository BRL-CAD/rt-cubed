/*                      U N K N O W N . H
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
/** @file Unknown.h
 *
 *  BRL-CAD core C++ interface:
 *      yet unknown database object declaration
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_UNKNOWN_INCLUDED
#define BRLCAD_UNKNOWN_INCLUDED

#include <new>

#include <brlcad/Object.h>


namespace BRLCAD {
    class BRLCAD_COREINTERFACE_EXPORT Unknown : public Object {
    public:
        Unknown(const Unknown& original) throw();
        virtual ~Unknown(void) throw();

        const Unknown&      operator=(const Unknown& original) throw();

        virtual Unknown*    Clone(void) const throw(std::bad_alloc);
        virtual void        Delete(void) throw();

        static const char*  ClassName(void) throw() {
            return "Unknown";
        }
        virtual const char* Type(void) const throw();

    protected:
        Unknown(directory* m_pDir,
                db_i*      m_dbip = 0) throw();

        friend class ConstDatabase;

    private:
        Unknown(void); // not implemented
    };
}


#endif // BRLCAD_UNKNOWN_INCLUDED
