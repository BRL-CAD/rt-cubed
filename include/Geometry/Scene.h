/*                         S C E N E . H
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
/** @file Scene.h
 *
 * Brief description
 *
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#include <iostream>
#include <vector>

#include "Geometry/Triangle.h"
#include "Geometry/View.h"

namespace Geometry {

  class Scene
  {
  private:
  protected:
    std::vector<Triangle*> _geometry;
    std::vector<View*> _views;
  public:
    Scene();
    ~Scene();

    void add(Scene& scene);
    void add(std::vector<Triangle*> geometry);
    void add(std::vector<View*> views);
    std::vector<Triangle*> getGeometry() const;
    std::vector<View*> getViews() const;
  };

}

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
