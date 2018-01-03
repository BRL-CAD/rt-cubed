/*                  L U A D A T A B A S E . C P P
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
/** @file luadatabase.cpp
 *
 *  BRL-CAD embedded lua script:
 *      BRLCAD::Database functions
 */

#include <cassert>

#include "luadatabase.h"


using namespace BRLCAD;


static Database* GetDatabase
(
    lua_State* luaState
) {
    Database** database = static_cast<Database**>(luaL_checkudata(luaState, 1, "Database"));

    assert(database != 0);
    assert(*database != 0);

    return *database;
}


static int Title
(
    lua_State* luaState
) {
    Database* database = GetDatabase(luaState);

    lua_pushstring(luaState, database->Title());

    return 1;
}


static int Select
(
    lua_State* luaState
) {
    Database*   database   = GetDatabase(luaState);
    const char* objectName = luaL_checkstring(luaState, -1);

    database->Select(objectName);

    return 0;
}


static int UnSelectAll
(
    lua_State* luaState
) {
    Database* database = GetDatabase(luaState);

    database->UnSelectAll();

    return 0;
}


void InitDatabase
(
    lua_State*        luaState,
    BRLCAD::Database& database
) {
    lua_newtable(luaState);
    int methodtable = lua_gettop(luaState);
    luaL_newmetatable(luaState, "Database");
    int metatable   = lua_gettop(luaState);

    lua_pushliteral(luaState, "__metatable");
    lua_pushvalue(luaState, methodtable);
    lua_settable(luaState, metatable);

    lua_pushliteral(luaState, "__index");
    lua_pushvalue(luaState, methodtable);
    lua_settable(luaState, metatable);

    lua_pop(luaState, 1);

    lua_pushcfunction(luaState, Title);
    lua_setfield(luaState, -2, "Title");

    lua_pushcfunction(luaState, Select);
    lua_setfield(luaState, -2, "Select");

    lua_pushcfunction(luaState, UnSelectAll);
    lua_setfield(luaState, -2, "UnSelectAll");

    lua_pop(luaState, 1);

    // register a global "database" variable
    Database** pDatabase = static_cast<Database**>(lua_newuserdata(luaState, sizeof(Database*)));
    *pDatabase = &database;
    luaL_getmetatable(luaState, "Database");
    lua_setmetatable(luaState, -2);
    lua_setglobal(luaState, "database");
}
