/*                C A M E R A M O D E B L E N D E R . C X X
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

/** @file CameraModeBlender.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the Camera mode "Blender" of 3D Geometry
 *	Editor (g3d).
 */

#include "CameraModeBlender.h"

#include "Logger.h"


/*******************************************************************************
 * CameraModeBlender
 ******************************************************************************/
const float CameraModeBlender::ROTATION_STEP = PI_NUMBER/12.0f; // 15 degrees, in radians
const float CameraModeBlender::PAN_STEP = 50.0f; // m
const float CameraModeBlender::ZOOM_STEP = 1.25f; // ratio

CameraModeBlender::CameraModeBlender() :
  CameraMode("Blender"),
  _dragModeEnabled(false), _dragModeOriginX(0), _dragModeOriginY(0),
  _panModeEnabled(false)
{
}

bool CameraModeBlender::injectKeyPressed(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_NUMPAD5:
    // reset to center
    setResetToCenter(true);
    return true;
  case OIS::KC_ADD:
    // zoom in
    divideVarWithLimit(_radius, ZOOM_STEP, RADIUS_MIN_DISTANCE);
    return true;
  case OIS::KC_SUBTRACT:
    // zoom out
    multiplyVarWithLimit(_radius, ZOOM_STEP, RADIUS_MAX_DISTANCE);
    return true;
  case OIS::KC_NUMPADENTER:
    // reset zoom
    _radius = RADIUS_DEFAULT_DISTANCE;
    return true;
  case OIS::KC_NUMPAD8:
    if (_panModeEnabled) {
      // pan up
      _center.y += PAN_STEP;
    } else {
      // orbit up
      decreaseVarWithLimit(_verticalRot,
			   ROTATION_STEP,
			   VERTICAL_ROTATION_MIN_LIMIT);
    }
    return true;
  case OIS::KC_NUMPAD2:
    if (_panModeEnabled) {
      // pan down
      _center.y -= PAN_STEP;
    } else {
      // orbit down
      increaseVarWithLimit(_verticalRot,
			   ROTATION_STEP,
			   VERTICAL_ROTATION_MAX_LIMIT);
    }
    return true;
  case OIS::KC_NUMPAD4:
    if (_panModeEnabled) {
      // pan left
      _center.x -= PAN_STEP;
    } else {
      // orbit left
      _horizontalRot -= ROTATION_STEP;
    }
    return true;
  case OIS::KC_NUMPAD6:
    if (_panModeEnabled) {
      // pan right
      _center.x += PAN_STEP;
    } else {
      // orbit right
      _horizontalRot += ROTATION_STEP;
    }
    return true;
  case OIS::KC_LCONTROL:
  case OIS::KC_RCONTROL:
    // enable pan mode
    _panModeEnabled = true;
    return true;
  default:
    return false;
  }
}

bool CameraModeBlender::injectKeyReleased(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_LCONTROL:
  case OIS::KC_RCONTROL:
    // disable pan mode
    _panModeEnabled = false;
    return true;
  default:
    return false;
  }
}

bool CameraModeBlender::injectMouseMotion(int x, int y)
{
  /// \todo mafm: there are some glitches, depending on the position
  /// when it starts and so on, it's worth investigating when more
  /// complex scenes are in place and it can be diagnosed more easily

  if (_dragModeEnabled) {
    // calculate the difference since last update, normalized between
    // -1.0 and 1.0 w.r.t. screen coordinates
    float horizDiffNorm = -(x - _dragModeOriginX)/(_windowWidth/2.0f);
    float vertDiffNorm = -(y - _dragModeOriginY)/(_windowHeight/2.0f);
    // Logger::logDEBUG("%.03f %.03f", horizDiffNorm, vertDiffNorm);

    // orbit freely, setting absolute position
    _horizontalRot = horizDiffNorm*PI_NUMBER;
    _verticalRot = vertDiffNorm*VERTICAL_ROTATION_MAX_LIMIT;
  }
}

bool CameraModeBlender::injectMousePressed(OIS::MouseButtonID buttonId, int x, int y)
{
  if (buttonId == OIS::MB_Middle) {
    _dragModeEnabled = true;
    _dragModeOriginX = x;
    _dragModeOriginY = y;
  }
}

bool CameraModeBlender::injectMouseReleased(OIS::MouseButtonID buttonId, int x, int y)
{
  if (buttonId == OIS::MB_Middle) {
    _dragModeEnabled = false;
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
