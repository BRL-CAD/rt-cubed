/*                  E M B E D D E D L U A . H
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
/** @file embeddedlua.h
 *
 *  BRL-CAD embedded lua script:
 *      API declaration
 *      a Lua based scripting language considered to be used embedded in other BRL-CAD applications
 *      it's not a full stack scripting language as it's e.g. not possible to load or save BRL-CAD databases
 */

#ifndef BRLCAD_EMBEDDEDLUA_INCLUDED
#define BRLCAD_EMBEDDEDLUA_INCLUDED

#ifndef BRLCAD_EMBEDDEDLUA_EXPORT
#   define BRLCAD_EMBEDDEDLUA_EXPORT
#endif


#include "brlcad/Database.h"


namespace BRLCAD {
    /// simple script execution
    BRLCAD_EMBEDDEDLUA_EXPORT bool RunEmbeddedLua
    (
        Database&   database,
        const char* script,
        const char* title,
        void        (*stdOut)(const char* text),
        void        (*stdErr)(const char* text)
    );


    /// advanced script execution
    class EmbeddedLuaHandle {
    public:
        virtual ~EmbeddedLuaHandle(void) {}

        virtual bool Execute(const char* script,
                             const char* title) = 0;

    protected:
        EmbeddedLuaHandle(void) {}
        EmbeddedLuaHandle(const EmbeddedLuaHandle&) {}
        const EmbeddedLuaHandle& operator=(const EmbeddedLuaHandle&) {return *this;}
    };


    BRLCAD_EMBEDDEDLUA_EXPORT EmbeddedLuaHandle* CreateEmbeddedLuaHandleInstance
    (
        Database& database,
        void      (*stdOut)(const char* text),
        void      (*stdErr)(const char* text)
    );


    BRLCAD_EMBEDDEDLUA_EXPORT void DestroyEmbeddedLuaHandleInstance
    (
        EmbeddedLuaHandle* handle
    );
}


#endif // BRLCAD_EMBEDDEDLUA_INCLUDED
