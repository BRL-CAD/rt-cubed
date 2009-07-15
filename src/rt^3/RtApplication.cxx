/*               R T A P P L I C A T I O N . C X X
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file RtApplication.cxx
 *
 * Brief description
 *
 */

#include "RtApplication.h"

#include <iostream>


RtApplication::RtApplication(int argc, char *argv[]) : Utility::Application(argc, argv)
{
  std::cout << "starting the rtapplication" << std::endl;
}


RtApplication::~RtApplication() 
{
  std::cout << "destroying the rtapplication" << std::endl;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
