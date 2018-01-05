/*                      B O U N D I N G B O X . C P P
 * BRL-CAD
 *
 * Copyright (c) 2018 United States Government as represented by
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
/** @file boundingbox.cpp
 *
 *  BRL-CAD embedded lua script:
 *      BoundingBoxMinima/BoundingBoxMaxima test application
 */


#include <iostream>
#include <sstream>

#include <embeddedlua.h>
#include <brlcad/MemoryDatabase.h>


using namespace BRLCAD;

int main
(
    int   argc,
    char* argv[]
) {
    int ret = 0;

    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <BRL-CAD Database> <objectToSelect>" << std::endl;
        ret = 1;
    }
    else {
        try {
        	std::stringstream TheLuaScript;
            MemoryDatabase database;

            if (database.Load(argv[1])) {
                EmbeddedLuaHandle* handle = CreateEmbeddedLuaHandleInstance(database, 0, 0);

                if (handle != 0) {
                    database.Select(argv[2]);
                    if (!database.SelectionIsEmpty())
                        std::cout << "Selected \"" << argv[2] << "\""<< std::endl;
                    else {
                        std::cerr << "Could not select object \"" << argv[2] << "\"" << std::endl;
                        ret = 5;
                    }

                    TheLuaScript << "print(\"BoundingBoxMinima: \")\n"
                                 << "print(database:BoundingBoxMinima())\n";
                    handle->Execute(TheLuaScript.str().c_str());

                    TheLuaScript.clear();
                    TheLuaScript.str("");

                    TheLuaScript << "print(\"BoundingBoxMaxima: \")\n"
                                 << "print(database:BoundingBoxMaxima())\n";
                    handle->Execute(TheLuaScript.str().c_str());

                    if (ret == 0)
                        std::cout << "Successfully executed BoundingBoxMinima() and BoundingBoxMaxima()" << std::endl;

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
