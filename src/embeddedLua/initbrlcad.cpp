/*                  I N I T B R L C A D . C P P
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
/** @file initbrlcad.cpp
 *
 *  BRL-CAD embedded lua script:
 *      BRL-CAD functions injection into Lua
 */

#include "luadatabase.h"
#include "initbrlcad.h"


void InitBrlcad
(
    lua_State*        luaState,
    BRLCAD::Database& database
) {
    InitDatabase(luaState, database);
}
