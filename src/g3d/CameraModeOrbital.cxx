/*                C A M E R A M O D E O R B I T A L . C X X
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

/** @file CameraModeMGED.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the Camera mode "Orbital" of 3D Geometry
 *	Editor (g3d).
 */

#include "CameraModeOrbital.h"

#include "Logger.h"


/*******************************************************************************
 * CameraModeOrbital
 ******************************************************************************/
CameraModeOrbital::CameraModeOrbital() :
  CameraMode("Orbital")
{
}

bool CameraModeOrbital::injectKeyPressed(QKeyEvent *e)
{
  if(e->modifiers() & Qt::KeypadModifier) {
    switch (e->key()) {
    case Qt::Key_5:
      // reset to center
      setResetToCenter(true);
      return true;
    case Qt::Key_Plus:
      // zoom in
      setZoom(CameraMode::POSITIVE);
      return true;
    case Qt::Key_Minus:
      // zoom out
      setZoom(CameraMode::NEGATIVE);
      return true;
    case Qt::Key_8:
      // orbit up
      setRotateX(CameraMode::POSITIVE);
      return true;
    case Qt::Key_2:
      // orbit down
      setRotateX(CameraMode::NEGATIVE);
      return true;
    case Qt::Key_4:
      // orbit left
      setRotateY(CameraMode::POSITIVE);
      return true;
    case Qt::Key_6:
      // orbit right
      setRotateY(CameraMode::NEGATIVE);
      return true;
    default:
      return false;
    }
  }
  return false;
}

bool CameraModeOrbital::injectKeyReleased(QKeyEvent *e)
{
  if(e->modifiers() & Qt::KeypadModifier) {
    switch (e->key()) {
    case Qt::Key_Plus:
    case Qt::Key_Minus:
      // zoom
      setZoom(CameraMode::NEUTRAL);
      return true;
    case Qt::Key_8:
    case Qt::Key_2:
      // orbit up/down
      setRotateX(CameraMode::NEUTRAL);
      return true;
    case Qt::Key_4:
    case Qt::Key_6:
      // orbit left/right
      setRotateY(CameraMode::NEUTRAL);
      return true;
    default:
      return false;
    }
  }
  return false;
}

void CameraModeOrbital::cameraControlUpPressed()
{
  setRotateX(CameraMode::POSITIVE);
}

void CameraModeOrbital::cameraControlDownPressed()
{
  setRotateX(CameraMode::NEGATIVE);
}

void CameraModeOrbital::cameraControlLeftPressed()
{
  setRotateY(CameraMode::POSITIVE);
}

void CameraModeOrbital::cameraControlRightPressed()
{
  setRotateY(CameraMode::NEGATIVE);
}

void CameraModeOrbital::cameraControlZoomInPressed()
{
  setZoom(CameraMode::POSITIVE);
}

void CameraModeOrbital::cameraControlZoomOutPressed()
{
  setZoom(CameraMode::NEGATIVE);
}

void CameraModeOrbital::cameraControlCenterPressed()
{
  setResetToCenter(true);
}

void CameraModeOrbital::cameraControlUpReleased()
{
  setRotateX(CameraMode::NEUTRAL);
}

void CameraModeOrbital::cameraControlDownReleased()
{
  setRotateX(CameraMode::NEUTRAL);
}

void CameraModeOrbital::cameraControlLeftReleased()
{
  setRotateY(CameraMode::NEUTRAL);
}

void CameraModeOrbital::cameraControlRightReleased()
{
  setRotateY(CameraMode::NEUTRAL);
}

void CameraModeOrbital::cameraControlZoomInReleased()
{
  setZoom(CameraMode::NEUTRAL);
}

void CameraModeOrbital::cameraControlZoomOutReleased()
{
  setZoom(CameraMode::NEUTRAL);
}

void CameraModeOrbital::cameraControlCenterReleased()
{
  setResetToCenter(true);
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
