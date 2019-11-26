/*                  E M B E D D E D L U A . C P P
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
 *      API declaration
 */

#include <iostream>
#include <cstring>

#include "lua.hpp"

#include "writestring.h"
#include "initbrlcad.h"
#include "embeddedlua.h"


using namespace BRLCAD;


static int EmbeddedLuaErrorHandler
(
    lua_State* luaState
) {
    const char *errorString = lua_tostring(luaState, 1);

    if (errorString == 0) {
        if ((luaL_callmeta(luaState, 1, "__tostring") != 0) && (lua_type(luaState, -1) == LUA_TSTRING))
            return 1; // that generated the error string
        else
            errorString = lua_pushfstring(luaState, "(error object is a %s value)", luaL_typename(luaState, 1));
    }

    luaL_traceback(luaState, luaState, errorString, 1);

    return 1;
}


BRLCAD_EMBEDDEDLUA_EXPORT bool BRLCAD::RunEmbeddedLua
(
    Database&   database,
    const char* script,
    const char* title,
    void        (*stdOut)(const char* text),
    void        (*stdErr)(const char* text)
) {
    bool ret = true;

    if (script != 0) {
        lua_State* luaState = luaL_newstate();

        if (luaState != 0) {
            brlcad_stdoutstream = stdOut;
            brlcad_sterrstream  = stdErr;

            luaL_openlibs(luaState);
            InitBrlcad(luaState, database);
            lua_pushcfunction(luaState, &EmbeddedLuaErrorHandler);

            const char* scriptName = "BRL-CAD";

            if (title != 0)
                scriptName = title;

            int error = luaL_loadbuffer(luaState, script, strlen(script), scriptName);

            if (error == LUA_OK) {
                error = lua_pcall(luaState, 0, 0, 1);

                if (error != LUA_OK) {
                    std::string logMessage = "Call: ";

                    switch (error) {
                    case LUA_ERRRUN:
                        logMessage += "Lua runtime error: ";
                        break;

                    case LUA_ERRMEM:
                        logMessage += "Lua memory allocation error: ";
                        break;

                    case LUA_ERRERR:
                        logMessage += "Lua error handler error: ";
                        break;

                    case LUA_ERRGCMM:
                        logMessage += "Lua garbage collection error: ";
                        break;

                    default:
                        logMessage += "Unknown error code: ";
                        break;
                    }

                    logMessage += lua_tostring(luaState, -1);
                    logMessage += "\n";
                    lua_pop(luaState, 1);

                    if (stdErr != 0)
                        stdErr(logMessage.c_str());
                    else
                        std::cerr << logMessage;

                    ret = false;
                }
            }
            else {
                std::string logMessage = "Load: ";

                switch (error) {
                case LUA_ERRSYNTAX:
                    logMessage += "Lua syntax error: ";
                    break;

                case LUA_ERRMEM:
                    logMessage += "Lua memory allocation error: ";
                    break;

                default:
                    logMessage += "Unknown error code: ";
                    break;
                }

                logMessage += lua_tostring(luaState, -1);
                logMessage += "\n";
                lua_pop(luaState, 1);

                if (stdErr != 0)
                    stdErr(logMessage.c_str());
                else
                    std::cerr << logMessage;

                ret = false;
            }

            lua_close(luaState);
        }
        else {
            if (stdErr != 0)
                stdErr("Could not open Lua\n");
            else
                std::cerr << "Could not open Lua\n";

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
                                    void      (*stdErr)(const char* text)) : EmbeddedLuaHandle(), m_stdOut(stdOut), m_stdErr(stdErr) {
        m_luaState = luaL_newstate();

        if (m_luaState != 0) {
            luaL_openlibs(m_luaState);
            InitBrlcad(m_luaState, database);
        }
        else {
            if (m_stdErr != 0)
                m_stdErr("Could not open Lua\n");
            else
                std::cerr << "Could not open Lua\n";
        }
    }

    virtual ~EmbeddedLuaHandleImplementation(void) {
        if (m_luaState != 0)
            lua_close(m_luaState);
    }

    virtual bool Execute(const char* script,
                         const char* title) {
        bool ret = true;

        if (script != 0) {
            brlcad_stdoutstream = m_stdOut;
            brlcad_sterrstream  = m_stdErr;

            if (m_luaState != 0) {
                lua_pushcfunction(m_luaState, &EmbeddedLuaErrorHandler);

                const char* scriptName = "BRL-CAD";

                if (title != 0)
                    scriptName = title;

                int error = luaL_loadbuffer(m_luaState, script, strlen(script), scriptName);

                if (error == LUA_OK) {
                    lua_pcall(m_luaState, 0, 0, 1);

                    if (error != LUA_OK) {
                        std::string logMessage = "Call: ";

                        switch (error) {
                        case LUA_ERRRUN:
                            logMessage += "Lua runtime error: ";
                            break;

                        case LUA_ERRMEM:
                            logMessage += "Lua memory allocation error: ";
                            break;

                        case LUA_ERRERR:
                            logMessage += "Lua error handler error: ";
                            break;

                        case LUA_ERRGCMM:
                            logMessage += "Lua garbage collection error: ";
                            break;

                        default:
                            logMessage += "Unknown error code: ";
                            break;
                        }

                        logMessage += lua_tostring(m_luaState, -1);
                        logMessage += "\n";
                        lua_pop(m_luaState, 1);

                        if (m_stdErr != 0)
                            m_stdErr(logMessage.c_str());
                        else
                            std::cerr << logMessage;

                        ret = false;
                    }
                }
                else {
                    std::string logMessage = "Load: ";

                    switch (error) {
                    case LUA_ERRSYNTAX:
                        logMessage += "Lua syntax error: ";
                        break;

                    case LUA_ERRMEM:
                        logMessage += "Lua memory allocation error: ";
                        break;

                    default:
                        logMessage += "Unknown error code: ";
                        break;
                    }

                    logMessage += lua_tostring(m_luaState, -1);
                    logMessage += "\n";
                    lua_pop(m_luaState, 1);

                    if (m_stdErr != 0)
                        m_stdErr(logMessage.c_str());
                    else
                        std::cerr << logMessage;

                    ret = false;
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
    lua_State* m_luaState;
    void       (*m_stdOut)(const char* text);
    void       (*m_stdErr)(const char* text);
};


BRLCAD_EMBEDDEDLUA_EXPORT EmbeddedLuaHandle* BRLCAD::CreateEmbeddedLuaHandleInstance
(
    Database& database,
    void      (*stdOut)(const char* text),
    void      (*stdErr)(const char* text)
) {
    return new EmbeddedLuaHandleImplementation(database, stdOut, stdErr);
}


BRLCAD_EMBEDDEDLUA_EXPORT void BRLCAD::DestroyEmbeddedLuaHandleInstance
(
    EmbeddedLuaHandle* handle
) {
    delete handle;
}
