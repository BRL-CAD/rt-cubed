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
    Database** pDatabase = static_cast<Database**>(lua_newuserdata(luaState, sizeof(Database*)));
    *pDatabase = &database;

    lua_getfield(luaState, LUA_REGISTRYINDEX, "Database");

    if (!lua_istable(luaState, -1)) { // already created?
        lua_pop(luaState, 1);
        lua_newtable(luaState);       // create metatable
        lua_pushvalue(luaState, -1);
        lua_setfield(luaState, LUA_REGISTRYINDEX, "Database");  // registry.name = metatable

        lua_pushvalue(luaState, -1);
        lua_setfield(luaState, -2, "__index");

        lua_pushstring(luaState, "Title");
        lua_pushcfunction(luaState, &GetTitle);
        lua_settable(luaState, -3);
    }

    lua_setmetatable(luaState, -2);
}
