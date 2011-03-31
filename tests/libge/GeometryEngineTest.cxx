/*          G E O M E T R Y E N G I N E T E S T . C X X
 * BRL-CAD
 *
 * Copyright (c) 2011 United States Government as represented by
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
/** @file GeometryEngineTest.cxx
 *
 * Brief description
 *
 */

#include "MinimalDatabase.h"
#include "MinimalObject.h"
#include "brlcad/Arb8.h"

using namespace BRLCAD;

MinimalDatabase*
makeDbForTesting()
{
	MinimalDatabase* md = new MinimalDatabase();

	Arb8 prim01;
	prim01.SetName("prim01.s");
	md->Add(prim01);

	Arb8 prim02;
	prim02.SetName("prim02.s");
	md->Add(prim02);

	Arb8 prim03;
	prim03.SetName("prim03.s");
	md->Add(prim03);

	return md;
}



int main (int   argc, char* argv[])
{
	MinimalDatabase* md = makeDbForTesting();

	MinimalObject* mob01 = md->getObjectByName("prim01.s");



}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
