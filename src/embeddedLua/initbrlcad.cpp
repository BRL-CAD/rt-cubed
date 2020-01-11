/*                  I N I T B R L C A D . C P P
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
/** @file initbrlcad.cpp
 *
 *  BRL-CAD embedded lua script:
 *      BRL-CAD functions injection into Lua
 */

#include "halfspace.h"
#include "hyperboliccylinder.h"
#include "hyperboloid.h"
#include "sphere.h"
#include "luadatabase.h"
#include "torus.h"
#include "ellipticaltorus.h"
#include "initbrlcad.h"


void InitBrlcad
(
    lua_State*        luaState,
    BRLCAD::Database& database
) {
    InitEllipticalTorus(luaState);
    InitHalfspace(luaState);
    InitHyperbolicCylinder(luaState);
    InitHyperboloid(luaState);
    InitSphere(luaState);
    InitTorus(luaState);

    InitDatabase(luaState, database);
}
