/*                       G M A I N . C X X
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file gsmain.cxx
 *
 * Brief description
 *
 */

#include "GS/GeometryService.h"
#include "alf/BaseApp.h"
#include <iostream>

int main(int argc, char* argv[])
{

    //TODO Configure system loads stuff here



    GeometryService gs(argc, argv, "ToBeDeterminedName");

    return gs.exec();
}
