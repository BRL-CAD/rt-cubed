/*                        D A T E . C X X
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
/** @file Date.cxx
 *
 * Brief description
 *
 */

// interface header
#include "Utility/Date.h"

// implementation system headers
#include <time.h>


using namespace Utility;

Date::Date()
{
}


Date::Date(int year, unsigned month, unsigned day)
{
}


Date::Date(const Date& date)
{
}


Date::Date(const std::string date)
{
}


Date::~Date()
{
}


std::string Date::string()
{
  return std::string("");
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
