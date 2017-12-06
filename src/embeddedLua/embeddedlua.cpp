/*                  E M B E D D E D L U A . C P P
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
 *      API declaration
 */

#include <cstring>

#include "lua.hpp"

#include "writestring.h"
#include "embeddedlua.h"


using namespace BRLCAD;


BRLCAD_EMBEDDEDLUA_EXPORT bool RunEmbeddedLua
(
    Database&   database,
    const char* script,
    void        (*stdOut)(const char* text),
    void        (*stdErr)(const char* text)
) {
    bool ret = true;

    if (script != 0) {
        brlcad_stdoutstream = stdOut;
        brlcad_sterrstream  = stdErr;

        lua_State* luaState = luaL_newstate();

        if (luaState != 0) {
            luaL_openlibs(luaState);
            //InitBrlcad(luaState, engine);

            int error = luaL_loadbuffer(luaState, script, strlen(script), "BRL-CAD");

            if (error == 0)
                lua_call(luaState, 0, 0);
            else {
                ret = false;

                switch (error) {
                case LUA_ERRSYNTAX:
                    if (stdErr != 0)
                        stdErr("Lua syntax error: ");

                    break;

                case LUA_ERRMEM:
                    if (stdErr != 0)
                        stdErr("Lua memory allocation error: ");

                    break;

                default:
                    if (stdErr != 0)
                        stdErr("Unknown lua_load return code: ");

                    break;
                }

                const char* logMessage = lua_tostring(luaState, -1);

                stdErr(logMessage);
                stdErr("\n");
                lua_pop(luaState, 1);
            }

            lua_close(luaState);
        }
        else {
            if (stdErr != 0)
                stdErr("Could not open Lua\n");

            ret = false;
        }

        brlcad_stdoutstream = 0;
        brlcad_sterrstream  = 0;
    }

    return ret;
}


class EmbeddedLuaHandleImplementation : public EmbeddedLuaHandle {
public:
    EmbeddedLuaHandleImplementation(Database& database,
                                    void      (*stdOut)(const char* text),
                                    void      (*stdErr)(const char* text)) : EmbeddedLuaHandle(), m_database(database), m_stdOut(stdOut), m_stdErr(stdErr) {
        m_luaState = luaL_newstate();

        if (m_luaState != 0) {
            luaL_openlibs(m_luaState);
            //InitBrlcad(m_luaState, m_engine);
        }
        else if (stdErr != 0)
            stdErr("Could not open Lua\n");
    }

    virtual ~EmbeddedLuaHandleImplementation(void) {
        if (m_luaState != 0)
            lua_close(m_luaState);
    }

    virtual bool Execute(const char* script) {
        bool ret = true;

        if (script != 0) {
            brlcad_stdoutstream = m_stdOut;
            brlcad_sterrstream  = m_stdErr;

            if (m_luaState != 0) {
                int error = luaL_loadbuffer(m_luaState, script, strlen(script), "BRL-CAD");

                if (error == 0)
                    lua_call(m_luaState, 0, 0);
                else {
                    ret = false;

                    switch (error) {
                    case LUA_ERRSYNTAX:
                        if (m_stdErr != 0)
                            m_stdErr("Lua syntax error: ");

                        break;

                    case LUA_ERRMEM:
                        if (m_stdErr != 0)
                            m_stdErr("Lua memory allocation error: ");

                        break;

                    default:
                        if (m_stdErr != 0)
                            m_stdErr("Unknown lua_load return code: ");

                        break;
                    }

                    const char* logMessage = lua_tostring(m_luaState, -1);

                    m_stdErr(logMessage);
                    m_stdErr("\n");
                    lua_pop(m_luaState, 1);
                }
            }
            else
                ret = false;

            brlcad_stdoutstream = 0;
            brlcad_sterrstream  = 0;
        }

        return ret;
    }

private:
    Database&  m_database;
    lua_State* m_luaState;
    void       (*m_stdOut)(const char* text);
    void       (*m_stdErr)(const char* text);
};


BRLCAD_EMBEDDEDLUA_EXPORT EmbeddedLuaHandle* CreateEmbeddedLuaHandleInstance
(
    Database& database,
    void      (*stdOut)(const char* text),
    void      (*stdErr)(const char* text)
) {
    return new EmbeddedLuaHandleImplementation(database, stdOut, stdErr);
}


BRLCAD_EMBEDDEDLUA_EXPORT void DestroyEmbeddedLuaHandleInstance
(
    EmbeddedLuaHandle* handle
) {
    delete handle;
}
