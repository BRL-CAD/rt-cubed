/*                C A M E R A M O D E O R B I T A L . H
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by the
 * U.S. Army Research Laboratory.
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

/** @file CameraModeOrbital.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Declaration of the Camera mode "Orbital" of 3D Geometry Editor
 *	(g3d).
 */

#ifndef __G3D_CAMERAMODEORBITAL_H__
#define __G3D_CAMERAMODEORBITAL_H__


#include "CameraMode.h"


/** @brief Orbital camera mode
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * The behavior of this camera mode is that it orbits the center, with
 * zoom to control the radius and the keys to go up/down/left/right
 * controlling movement from "pole to pole" and "equator".
 */
class CameraModeOrbital : public CameraMode
{
public:
  /** Default constructor */
  CameraModeOrbital();

  /** @see CameraMode::injectKeyPressed */
  virtual bool injectKeyPressed(OIS::KeyCode keyCode);
  /** @see CameraMode::injectKeyReleased */
  virtual bool injectKeyReleased(OIS::KeyCode keyCode);
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
