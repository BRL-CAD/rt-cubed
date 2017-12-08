/*                  L U A D A T A B A S E . C P P
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


static int GetTitle
(
    lua_State* luaState
) {
    Database* database = GetDatabase(luaState);

    lua_pushstring(luaState, database->Title());

    return 1;
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

    lua_pushcfunction(luaState, GetTitle);
    lua_setfield(luaState, -2, "Title");

    lua_pop(luaState, 1);

    // register a global "database" variable
    Database** pDatabase = static_cast<Database**>(lua_newuserdata(luaState, sizeof(Database*)));
    *pDatabase = &database;
    luaL_getmetatable(luaState, "Database");
    lua_setmetatable(luaState, -2);
    lua_setglobal(luaState, "database");
}
