 /*                  P R I M I T I V E S . C P P
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
/** @file primitives.cpp
 *
 * C++ core interface tests collection
 *
 */

#include <iostream>

#include "brlcad/FileDatabase.h"

#include "primitives.h"


int main
(
    int   argc,
    char* argv[]
) {
    int ret = 0;

    if (argc < 2) {
	std::cout << "Usage: " << argv[0] << " <BRL-CAD Database>";
	ret = 1;
    }
    else {
	try {
	    BRLCAD::FileDatabase database;

	    if (database.Load(argv[1])) {
		test_halfspace(database);
	    } else {
		std::cout << "Could not load file: " << argv[1] << std::endln;
		ret = 2;
	    }
	}
	catch(BRLCAD::bad_alloc& e) {
	    std::cout << "Out of memory in: " << e.what() << std::endln;
	    ret = 3;
	}
    }

    return ret;
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
