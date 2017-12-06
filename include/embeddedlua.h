/*                  E M B E D D E D L U A . H
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
        void        (*stdOut)(const char* text),
        void        (*stdErr)(const char* text)
    );


    /// advanced script execution
    class EmbeddedLuaHandle {
    public:
        virtual ~EmbeddedLuaHandle(void) {}

        virtual bool Execute(const char* script) = 0;

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
