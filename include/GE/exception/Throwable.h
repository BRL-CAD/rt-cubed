/*                     T H R O W A B L E . H
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
/** @file Throwable.h
 *
 * Brief description
 *
 */

#ifndef __THROWABLE_H__
#define __THROWABLE_H__

#include "GS/GSCommon.h"
#include <string>


class Throwable
{
private:
  std::string _msg;

public:
  Throwable() throw ();
  Throwable(const std::string& message) throw ();
  Throwable(const Throwable& cause) throw ();
  virtual ~Throwable() throw () {};

  const std::string& getMessage() const throw ();
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
