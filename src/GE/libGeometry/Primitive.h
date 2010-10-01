/*                     P R I M I T I V E . H
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
/** @file Primitive.h
 *
 * Brief description
 *
 */

#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__

#include <iostream>

namespace Geometry {
  class Primitive
  {
  private:
  protected:
    /*    Primitive() {};
    virtual ~Primitive() = 0;
    */
  public:
    virtual bool intersect(double position[3], double direction[3], double *t, double *u, double *v) = 0;
  };
}

#endif /* __PRIMITIVE_H__ */

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
