/*                        T I M E . C X X
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
/** @file Time.cxx
 *
 * Brief description
 *
 */

// interface header
#include "utility/Time.h"

// implementation system headers
#include <time.h>


using namespace Utility;

Time::Time()
{
}


Time::Time(int hour, int minute, int second)
{
}


Time::Time(const Time& time)
{
}


Time::Time(const std::string time)
{
}


Time::~Time()
{
}


std::string Time::string()
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
