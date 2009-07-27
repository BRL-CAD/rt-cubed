/*                C A M E R A M O D E B L E N D E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by the
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

#include <OGRE/OgreCamera.h>

#include "CameraModeBlender.h"

#include "Logger.h"


/*******************************************************************************
 * CameraModeBlender
 ******************************************************************************/
const float CameraModeBlender::ROTATION_STEP = M_PI/12.0f; // 15 degrees, in radians
const float CameraModeBlender::PAN_FRACTION = 20.0f; // m
const float CameraModeBlender::ZOOM_STEP = 1.25f; // ratio

CameraModeBlender::CameraModeBlender() :
  CameraMode("Blender"),
  _dragModeEnabled(false),
  _dragModeOriginX(0), _dragModeOriginY(0),
  _dragOriginalHorizontalRotation(0.0f), _dragOriginalVerticalRotation(0.0f),
  _panModeEnabled(false)
{
}

bool CameraModeBlender::injectKeyPressed(QKeyEvent *e)
{
  if(e->modifiers() & Qt::KeypadModifier) {
    switch (e->key()) {
    case Qt::Key_5:
      // reset to center
      setResetToCenter(true);
      return true;
    case Qt::Key_Plus:
      // zoom in
      doZoomIn();
      return true;
    case Qt::Key_Minus:
      // zoom out
      doZoomOut();
      return true;
    case Qt::Key_Enter:
      // reset zoom
      _radius = RADIUS_DEFAULT_DISTANCE;
      return true;
    case Qt::Key_8:
      if (_panModeEnabled) {
	panUp();
      } else {
	// orbit up
	circularIncrement(_verticalRot, -ROTATION_STEP);
      }
      return true;
    case Qt::Key_2:
      if (_panModeEnabled) {
	panDown();
      } else {
	// orbit down
	circularIncrement(_verticalRot, ROTATION_STEP);
      }
      return true;
    case Qt::Key_4:
      if (_panModeEnabled) {
	panLeft();
      } else {
	// orbit left
	circularIncrement(_horizontalRot, -ROTATION_STEP);
      }
      return true;
    case Qt::Key_6:
      if (_panModeEnabled) {
	panRight();
      } else {
	// orbit right
	circularIncrement(_horizontalRot, ROTATION_STEP);
      }
      return true;
    }
  } else {
    switch(e->key()) {
    case Qt::Key_Control:
      // enable pan mode
      _panModeEnabled = true;
      return true;
    default:
      return false;
    }
  }
  
  return false;
}

bool CameraModeBlender::injectKeyReleased(QKeyEvent *e)
{
  switch (e->key()) {
  case Qt::Key_Control:
    // disable pan mode
    _panModeEnabled = false;
    return true;
  default:
    return false;
  }
}

bool CameraModeBlender::injectMouseMotion(QMouseEvent *e)
{
  if (_dragModeEnabled) {
    // calculate the difference since last update, normalized between
    // -1.0 and 1.0 w.r.t. screen coordinates
    float horizDiffNorm = -(e->x() - _dragModeOriginX)/(_windowWidth/2.0f);
    float vertDiffNorm = -(e->y() - _dragModeOriginY)/(_windowHeight/2.0f);
    // Logger::logDEBUG("%.03f %.03f", horizDiffNorm, vertDiffNorm);

    // orbit freely, setting absolute position
    _horizontalRot = _dragOriginalHorizontalRotation + horizDiffNorm*M_PI;
    _verticalRot = _dragOriginalVerticalRotation + vertDiffNorm*M_PI;

    // Protect against overflows without causing viewjumping.
    circularIncrement(_horizontalRot, 0);
    circularIncrement(_verticalRot, 0);

    return true;
  } else {
    return false;
  }
}

bool CameraModeBlender::injectMousePressed(QMouseEvent *e)
{
  if (e->button() == Qt::MidButton) {
    _dragModeEnabled = true;
    _dragModeOriginX = e->x();
    _dragModeOriginY = e->y();
    _dragOriginalHorizontalRotation = _horizontalRot;
    _dragOriginalVerticalRotation = _verticalRot;

    return true;
  } else {
    return false;
  }
}

bool CameraModeBlender::injectMouseReleased(QMouseEvent *e)
{
  if (e->button() == Qt::MidButton) {
    _dragModeEnabled = false;
    return true;
  } else {
    return false;
  }
}


bool CameraModeBlender::injectMouseScrolled(Direction direction)
{
  switch (direction) {
  case POSITIVE:
    // zoom in
    divideVarWithLimit(_radius, ZOOM_STEP, RADIUS_MIN_DISTANCE);
    return true;
  case NEGATIVE:
    // zoom out
    multiplyVarWithLimit(_radius, ZOOM_STEP, RADIUS_MAX_DISTANCE);
    return true;
  default:
    return false;
  }
}

void CameraModeBlender::cameraControlUpPressed()
{
  // nothing
}

void CameraModeBlender::cameraControlDownPressed()
{
  // nothing
}

void CameraModeBlender::cameraControlLeftPressed()
{
  // nothing
}

void CameraModeBlender::cameraControlRightPressed()
{
  // nothing
}

void CameraModeBlender::cameraControlZoomInPressed()
{
  // nothing
}

void CameraModeBlender::cameraControlZoomOutPressed()
{
  // nothing
}

void CameraModeBlender::cameraControlCenterPressed()
{
  // nothing
}

void CameraModeBlender::cameraControlUpReleased()
{
  panUp();
}

void CameraModeBlender::cameraControlDownReleased()
{
  panDown();
}

void CameraModeBlender::cameraControlLeftReleased()
{
  panLeft();
}

void CameraModeBlender::cameraControlRightReleased()
{
  panRight();
}

void CameraModeBlender::cameraControlZoomInReleased()
{
  doZoomIn();
}

void CameraModeBlender::cameraControlZoomOutReleased()
{
  doZoomOut();
}

void CameraModeBlender::cameraControlCenterReleased()
{
  setResetToCenter(true);
}

void CameraModeBlender::panUp()
{
  pan(0, (_camera->getOrthoWindowHeight()/PAN_FRACTION));
}

void CameraModeBlender::panDown()
{
  pan(0, -(_camera->getOrthoWindowHeight()/PAN_FRACTION));
}

void CameraModeBlender::panLeft()
{
  pan((_camera->getOrthoWindowWidth()/PAN_FRACTION), 0);
}

void CameraModeBlender::panRight()
{
  pan(-(_camera->getOrthoWindowWidth()/PAN_FRACTION), 0);
}

void CameraModeBlender::doZoomIn()
{
  divideVarWithLimit(_radius, ZOOM_STEP, RADIUS_MIN_DISTANCE);
}

void CameraModeBlender::doZoomOut()
{
  multiplyVarWithLimit(_radius, ZOOM_STEP, RADIUS_MAX_DISTANCE);
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
