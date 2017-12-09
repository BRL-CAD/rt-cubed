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
