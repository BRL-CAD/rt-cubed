/*                C A M E R A M O D E O R B I T A L . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2010 United States Government as represented by the
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
  virtual bool injectKeyPressed(QKeyEvent *e);
  /** @see CameraMode::injectKeyReleased */
  virtual bool injectKeyReleased(QKeyEvent *e);

  /** @see CameraMode::cameraControlUpPressed */
  virtual void cameraControlUpPressed();
  /** @see CameraMode::cameraControlDownPressed */
  virtual void cameraControlDownPressed();
  /** @see CameraMode::cameraControlLeftPressed */
  virtual void cameraControlLeftPressed();
  /** @see CameraMode::cameraControlRightPressed */
  virtual void cameraControlRightPressed();
  /** @see CameraMode::cameraControlZoomInPressed */
  virtual void cameraControlZoomInPressed();
  /** @see CameraMode::cameraControlZoomOutPressed */
  virtual void cameraControlZoomOutPressed();
  /** @see CameraMode::cameraControlCenterPressed */
  virtual void cameraControlCenterPressed();
  /** @see CameraMode::cameraControlUpReleased */
  virtual void cameraControlUpReleased();
  /** @see CameraMode::cameraControlDownReleased */
  virtual void cameraControlDownReleased();
  /** @see CameraMode::cameraControlLeftReleased */
  virtual void cameraControlLeftReleased();
  /** @see CameraMode::cameraControlRightReleased */
  virtual void cameraControlRightReleased();
  /** @see CameraMode::cameraControlZoomInReleased */
  virtual void cameraControlZoomInReleased();
  /** @see CameraMode::cameraControlZoomOutReleased */
  virtual void cameraControlZoomOutReleased();
  /** @see CameraMode::cameraControlCenterReleased */
  virtual void cameraControlCenterReleased();
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
