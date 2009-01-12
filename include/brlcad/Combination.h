/*                      C O M B I N A T I O N . H
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
/** @file Combination.h
 *
 *  BRL-CAD core C++ interface:
 *      combination (ID_COMBINATION) database object declaration
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_COMBINATION_INCLUDED
#define BRLCAD_COMBINATION_INCLUDED

#include <brlcad/Object.h>


struct rt_comb_internal;


namespace BRLCAD {
    class BRLCAD_COREINTERFACE_EXPORT Combination : public Object {
    public:
        Combination(void);
        Combination(const Combination& original) throw();
        virtual ~Combination(void) throw();

        const Combination&  operator=(const Combination& original) throw();

        // inherited from BRLCAD::Object
        static const char*  ClassName(void) throw();
        virtual const char* Type(void) const throw();

    protected:
        Combination(resource*       resp,
                    directory*      pDir,
                    rt_db_internal* ip,
                    db_i*           dbip = 0) throw();

        friend class ConstDatabase;

    private:
        // holds Objects's content if not connected to a database
        rt_comb_internal* m_internalp;
    };
}


#endif // BRLCAD_COMBINATION_INCLUDED
