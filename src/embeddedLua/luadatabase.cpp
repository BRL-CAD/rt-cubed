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
    Database** database = static_cast<Database**>(luaL_checkudata(luaState, 1, "BRLCAD.Database"));

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


static int BoundingBoxMinima
(
    lua_State* luaState
) {
    Database* database          = GetDatabase(luaState);
    Vector3D  boundingBoxMinima = database->BoundingBoxMinima();

    lua_pushnumber(luaState, boundingBoxMinima.coordinates[0]);
    lua_pushnumber(luaState, boundingBoxMinima.coordinates[1]);
    lua_pushnumber(luaState, boundingBoxMinima.coordinates[2]);

    return 3;
}


static int BoundingBoxMaxima
(
    lua_State* luaState
) {
    Database* database          = GetDatabase(luaState);
    Vector3D  boundingBoxMaxima = database->BoundingBoxMaxima();

    lua_pushnumber(luaState, boundingBoxMaxima.coordinates[0]);
    lua_pushnumber(luaState, boundingBoxMaxima.coordinates[1]);
    lua_pushnumber(luaState, boundingBoxMaxima.coordinates[2]);

    return 3;
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
    lua_getglobal(luaState, "BRLCAD");

    if (!lua_istable(luaState, -1)) {
        lua_pop(luaState, 1);
        lua_newtable(luaState);
        lua_setglobal(luaState, "BRLCAD");
        lua_getglobal(luaState, "BRLCAD");
    }

    // register a global "database" variable
    Database** pDatabase = static_cast<Database**>(lua_newuserdata(luaState, sizeof(Database*)));
    *pDatabase = &database;

    luaL_newmetatable(luaState, "BRLCAD.Database");
    lua_pushvalue(luaState, -1);
    lua_setfield(luaState, -2, "__index");

    lua_pushstring(luaState, "Title");
    lua_pushcfunction(luaState, Title);
    lua_settable(luaState, -3);

    lua_pushstring(luaState, "Select");
    lua_pushcfunction(luaState, Select);
    lua_settable(luaState, -3);

    lua_pushstring(luaState, "UnSelectAll");
    lua_pushcfunction(luaState, UnSelectAll);
    lua_settable(luaState, -3);

    lua_pushstring(luaState, "BoundingBoxMinima");
    lua_pushcfunction(luaState, BoundingBoxMinima);
    lua_settable(luaState, -3);

    lua_pushstring(luaState, "BoundingBoxMaxima");
    lua_pushcfunction(luaState, BoundingBoxMaxima);
    lua_settable(luaState, -3);

    lua_setmetatable(luaState, -2);

    lua_setfield(luaState, -2, "database");
    lua_pop(luaState, 1);
}
