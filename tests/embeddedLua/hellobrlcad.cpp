/*                  H E L L O W O R L D . C P P
 * BRL-CAD
 *
 * Copyright (c) 2017 United States Government as represented by
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
/** @file embeddedlua.cpp
 *
 *  BRL-CAD embedded lua script:
 *      Hello World! with BRL-CAD call test appliction
 */

#include <iostream>

#include <embeddedlua.h>
#include <brlcad/MemoryDatabase.h>


using namespace BRLCAD;


const char* const TheLuaScript = R"ESCSEQ(
print("Hello ", database:Title(), "!")
)ESCSEQ";


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
                    handle->Execute(TheLuaScript);
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
