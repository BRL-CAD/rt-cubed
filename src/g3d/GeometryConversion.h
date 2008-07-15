/*            G E O M E T R Y C O N V E R S I O N. H
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

/** @file GeometryConversion.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header file for creating and translating from Ogre Geometries
 *	to the rest of the program.
 */

#ifndef __G3D_GEOMETRYCONVERSION_H__
#define __G3D_GEOMETRYCONVERSION_H__


#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreManualObject.h"
#include "OGRE/OgreString.h"


/** @brief Tetrahedron geometry
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class SampleTetrahedron
{
public:
  /* Default constructor
  *
  * @param scale Scale to relative units (basic object is created with
  * 1 unit) */
  SampleTetrahedron(float scale = 1.0f);

  /** Get pointer to movable object */
  Ogre::MovableObject* getMovableObject();

private:
  /** Ogre object created manually */
  Ogre::ManualObject _manualObject;
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8

