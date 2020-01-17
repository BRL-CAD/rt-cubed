/*                  D A T A B A S E T I T L E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2020 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/** @file databasetitle.cpp
 *
 *  BRL-CAD embedded lua script:
 *      Unit Test with BRL-CAD call test application
 */

#include <iostream>

#include <embeddedlua.h>
#include <brlcad/MemoryDatabase.h>


using namespace BRLCAD;


bool        firstPrint = true;
std::string luaTitle;


void LuaStdOutPrint
(
    const char* text
) {
    if (firstPrint) {
        luaTitle   = text;
        firstPrint = false;
    }
}


int main
(
    int   argc,
    char* argv[]
) {
    int ret = 1;

    if (argc < 2)
        std::cout << "Usage: " << argv[0] << " <BRL-CAD Database>" << std::endl;
    else {
        try {
            MemoryDatabase database;

            if (database.Load(argv[1])) {
                EmbeddedLuaHandle* handle = CreateEmbeddedLuaHandleInstance(database, LuaStdOutPrint, 0);

                if (handle != 0) {
                    handle->Execute("print(BRLCAD.database:Title())", "databasetitle");

                    if (luaTitle == database.Title()) {
                        ret = 0;

                        // some processing info
                        std::cout << "database title: " << luaTitle << std::endl;
                    }
                    else {
                        std::cerr << "database title in Lua is: \"" << luaTitle << "\"" << std::endl;
                        std::cerr << "but it should be        : \"" << database.Title() << "\"" << std::endl;
                    }

                    DestroyEmbeddedLuaHandleInstance(handle);
                }
                else
                    std::cerr << "Could not create BRL-CAD embedded Lua handle" << std::endl;
            }
            else
                std::cerr << "Could not load file: " << argv[1] << std::endl;
        }
        catch(BRLCAD::bad_alloc& e) {
            std::cerr << "Out of memory in: " << e.what() << std::endl;
        }
    }

    return ret;
}
