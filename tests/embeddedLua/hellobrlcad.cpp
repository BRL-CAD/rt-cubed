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
 *      Hello World! with BRL-CAD call test appliction
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

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <BRL-CAD Database>" << std::endl;
        ret = 1;
    }
    else {
        try {
            MemoryDatabase database;

            if (database.Load(argv[1])) {
                EmbeddedLuaHandle* handle = CreateEmbeddedLuaHandleInstance(database, 0, 0);

                if (handle != 0) {
                    handle->Execute("print(\"Hello \", Database.Title(), \"!\")");
                    DestroyEmbeddedLuaHandleInstance(handle);
                }
                else {
                    std::cerr << "Could not create BRL-CAD embedded Lua handle" << std::endl;
                    ret = 2;
                }
            }
            else {
                std::cerr << "Could not load file: " << argv[1] << std::endl;
                ret = 3;
            }
        }
        catch(BRLCAD::bad_alloc& e) {
            std::cerr << "Out of memory in: " << e.what() << std::endl;
            ret = 4;
        }
    }

    return ret;
}
