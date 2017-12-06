/*                  H E L L O W O R L D . C P P
 * BRL-CAD
 *
 * Copyright (c) 2017 United States Government as represented by
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
/** @file embeddedlua.cpp
 *
 *  BRL-CAD embedded lua script:
 *      Hello World! test appliction
 */

#include <iostream>

#include <embeddedlua.h>
#include <brlcad/MemoryDatabase.h>


using namespace BRLCAD;


int main
(
    int   argc,
    char* argv[]
) {
    int ret = 0;
    
    MemoryDatabase     database;
    EmbeddedLuaHandle* handle = CreateEmbeddedLuaHandleInstance(database, 0, 0);

    if (handle != 0) {
        handle->Execute("print(\"Hello World!\")");
        DestroyEmbeddedLuaHandleInstance(handle);
    }
    else {
        std::cerr << "Could not create BRL-CAD embedded Lua handle" << std::endl;
        ret = 1;
    }

    return ret;
}
