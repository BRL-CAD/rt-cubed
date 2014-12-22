 /*                  H A L F S P A C E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2014 United States Government as represented by
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
/** @file halfspace.cpp
 *
 * C++ core interface Halfspce test
 *
 */

#include <iostream>

#include "brlcad/Halfspace.h"

#include "primitives.h"


void test_halfspace(BRLCAD::Database& database) {
    BRLCAD::Halfspace halfspace;

    halfspace.SetName("Halfspace.s");

    if (halfspace.IsValid()) {
	halfspace.SetNormal(BRLCAD::Vector3D(0., 0., 1.));
	halfspace.SetDistanceFromOrigin(0.);

	if (halfspace.IsValid())
	    database.Add(halfspace);
	else
	    std::cout << "Halfspace not valid" << std::endl;
    }
    else
        std::cout << "default Halfspace not valid" << std::endl;
}


/*
 * Local Variables:
 * mode: C
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
