/*            G E O M E T R Y C O N V E R S I O N. C X X
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
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

/** @file GeometryConversion.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of conversions between Ogre Geometries from/to
 *	the rest of the program.
 */

#include "GeometryConversion.h"

#include "OGRE/OgreColourValue.h"
#include "OGRE/OgreMesh.h"


SampleTetrahedron::SampleTetrahedron(float scale) :
  _manualObject(Ogre::String("tetrahedron"))
{
  Ogre::Vector3 positionZero(0, 0, 0);
  Ogre::ColourValue colorBlack(0, 0, 0, 1);
  _manualObject.begin("", Ogre::RenderOperation::OT_TRIANGLE_LIST);

  Ogre::Vector3 pos = positionZero;
  Ogre::ColourValue col = colorBlack;
  _manualObject.position(pos);
  _manualObject.colour(col);

  pos.x = 1 * scale;
  col.r = 1.0f;
  _manualObject.position(pos);
  _manualObject.colour(col);

  pos.z = 1 * scale;
  col.g = 1.0f;
  _manualObject.position(pos);
  _manualObject.colour(col);

  pos.y = 1 * scale;
  col.b = 1.0f;
  _manualObject.position(pos);
  _manualObject.colour(col);

  _manualObject.triangle(0, 1, 2); // inferior, looking down
  _manualObject.triangle(0, 2, 3); // front left, looking left
  _manualObject.triangle(1, 3, 2); // front right, looking right
  _manualObject.triangle(0, 3, 1); // back, looking away

  _manualObject.end();

  Ogre::AxisAlignedBox box;
  box.setInfinite();
  _manualObject.setBoundingBox(box);

  _manualObject.convertToMesh("TetrahedronMesh");
}


Ogre::MovableObject* SampleTetrahedron::getMovableObject()
{
  return &_manualObject;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

