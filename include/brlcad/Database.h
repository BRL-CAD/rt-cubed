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


namespace BRLCAD {
    class Database : public ConstDatabase {
    };
}


#endif // BRLCAD_DATABASE_INCLUDED
