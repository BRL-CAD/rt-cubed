/*                C A M E R A M O D E M G E D . C X X
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

/** @file CameraModeMGED.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the Camera mode "MGED" of 3D Geometry Editor
 *	(g3d).
 */

#include <cmath>

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreRay.h>

#include "CameraModeMGED.h"

#include "Logger.h"


/*******************************************************************************
 * CameraModeMGED
 ******************************************************************************/
const float CameraModeMGED::ROTATION_STEP = PI_NUMBER/12.0f; // 15 degrees, in radians
const float CameraModeMGED::PAN_FRACTION = 20.0f; // m
const float CameraModeMGED::ZOOM_STEP = 1.25f; // ratio
const float CameraModeMGED::ZOOM_SCALE = 4.0f; // ratio

CameraModeMGED::CameraModeMGED() :
  CameraMode("MGED"),
  _keyControlPressed(false),
  _keyAltPressed(false),
  _keyShiftPressed(false),
  _translateModeEnabled(false),
  _rotateModeEnabled(false),
  _scaleModeEnabled(false),
  _constrainedSubmodeEnabled(false),
  _constrainedToAxis(NOTSET),
  _mouseButtonsPressed(0),
  _dragOriginX(0), _dragOriginY(0),
  _dragOriginalRadius(0.0f),
  _dragOriginalHorizontalRotation(0.0f), _dragOriginalVerticalRotation(0.0f),
  _dragOriginalCenter(0.0f, 0.0f, 0.0f)
{
}

bool CameraModeMGED::injectKeyPressed(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_NUMPAD5:
    // reset to center
    setResetToCenter(true);
    return true;
  case OIS::KC_LCONTROL:
  case OIS::KC_RCONTROL:
    _keyControlPressed = true;
    setMode();
    return true;
  case OIS::KC_LMENU:
  case OIS::KC_RMENU:
    _keyAltPressed = true;
    setMode();
    return true;
  case OIS::KC_LSHIFT:
  case OIS::KC_RSHIFT:
    _keyShiftPressed = true;
    setMode();
    return true;
  default:
    return false;
  }
}

bool CameraModeMGED::injectKeyReleased(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_LCONTROL:
  case OIS::KC_RCONTROL:
    _keyControlPressed = false;
    setMode();
    return true;
  case OIS::KC_LMENU:
  case OIS::KC_RMENU:
    _keyAltPressed = false;
    setMode();
    return true;
  case OIS::KC_LSHIFT:
  case OIS::KC_RSHIFT:
    _keyShiftPressed = false;
    setMode();
    return true;
  default:
    return false;
  }
}

bool CameraModeMGED::injectMouseMotion(int x, int y)
{
  /// \todo mafm: there are some glitches, depending on the position
  /// when it starts and so on, it's worth investigating when more
  /// complex scenes are in place and it can be diagnosed more easily

  if (_scaleModeEnabled && _mouseButtonsPressed > 0) {
    // calculate the x position normalized between -1.0 and 1.0
    // w.r.t. screen coordinates (inside windows, if mouse goes
    // outside it depends on the windowing system)
    float horizDiffNorm = (x - _dragOriginX)/static_cast<float>(_windowWidth/2.0f);
    float scale = pow(ZOOM_SCALE, horizDiffNorm);
    //Logger::logDEBUG("x diff: %g; scale: %g", horizDiffNorm, scale);

    // zoom freely, left zooms out and right zooms in
    doZoomScale(scale);

    return true;
  } else if (_translateModeEnabled && _mouseButtonsPressed > 0) {
    // pan given amount of screen units
    panScreenRelativeCoords(x - _dragOriginX, y - _dragOriginY);
    return true;
  } else if (_rotateModeEnabled && _mouseButtonsPressed > 0) {
    // mafm: originally copied from blender mode

    // calculate the difference since last update, normalized between
    // -1.0 and 1.0 w.r.t. screen coordinates
    float horizDiffNorm = -(x - _dragOriginX)/(_windowWidth/2.0f);
    float vertDiffNorm = -(y - _dragOriginY)/(_windowHeight/2.0f);
    // Logger::logDEBUG("%.03f %.03f", horizDiffNorm, vertDiffNorm);

    // orbit freely, setting absolute position
    _horizontalRot = _dragOriginalHorizontalRotation + horizDiffNorm*PI_NUMBER;
    _verticalRot = _dragOriginalVerticalRotation + vertDiffNorm*VERTICAL_ROTATION_MAX_LIMIT;

    return true;
  } else {
    return false;
  }
}

bool CameraModeMGED::injectMousePressed(OIS::MouseButtonID buttonId, int x, int y)
{
  // increase the count of mouse buttons pressed, for all purposes
  ++(_mouseButtonsPressed);

  if (_translateModeEnabled || _rotateModeEnabled || _scaleModeEnabled) {
    switch (buttonId) {
    case OIS::MB_Left:
      _constrainedToAxis = X;
      _dragOriginX = x;
      _dragOriginY = y;
      _dragOriginalRadius = _radius;
      _dragOriginalHorizontalRotation = _horizontalRot;
      _dragOriginalVerticalRotation = _verticalRot;
      _dragOriginalCenter = _center;
      break;
    case OIS::MB_Middle:
      _constrainedToAxis = Y;
      _dragOriginX = x;
      _dragOriginY = y;
      _dragOriginalRadius = _radius;
      _dragOriginalHorizontalRotation = _horizontalRot;
      _dragOriginalVerticalRotation = _verticalRot;
      _dragOriginalCenter = _center;
      break;
    case OIS::MB_Right:
      _constrainedToAxis = Z;
      _dragOriginX = x;
      _dragOriginY = y;
      _dragOriginalRadius = _radius;
      _dragOriginalHorizontalRotation = _horizontalRot;
      _dragOriginalVerticalRotation = _verticalRot;
      _dragOriginalCenter = _center;
      break;
    default:
      // nothing
      break;
    }
  } else {
    switch (buttonId) {
    case OIS::MB_Left:
      doZoomOut();
      break;
    case OIS::MB_Middle:
      /// \todo mafm: pan same distance as from point clicked to
      /// center, but in opposite direction
      break;
    case OIS::MB_Right:
      doZoomIn();
      break;
    default:
      // nothing
      break;
    }
  }

  return true;
}

bool CameraModeMGED::injectMouseReleased(OIS::MouseButtonID buttonId, int /* x */, int /* y */)
{
  // decrease the count of mouse buttons pressed, for all purposes
  --(_mouseButtonsPressed);

  if (_translateModeEnabled || _rotateModeEnabled) {
    _constrainedSubmodeEnabled = false;
    switch (buttonId) {
    case OIS::MB_Left:
      _constrainedToAxis = NOTSET;
      break;
    case OIS::MB_Middle:
      _constrainedToAxis = NOTSET;
      break;
    case OIS::MB_Right:
      _constrainedToAxis = NOTSET;
      break;
    default:
      // nothing
      break;
    }
  }

  return true;
}

void CameraModeMGED::setMode()
{
  if (_keyControlPressed 
      && _keyAltPressed 
      && _keyShiftPressed) {
    // all keys active at once: scale mode
    _scaleModeEnabled = true;
    // ...and disable the rest
    _translateModeEnabled = false;
    _rotateModeEnabled = false;
    _constrainedSubmodeEnabled = false;
    //Logger::logDEBUG("set scale mode");
  } else {
    // submode "constrained"?
    if (_keyAltPressed) {
      _constrainedSubmodeEnabled = true;
    } else {
      _constrainedSubmodeEnabled = false;
    }

    // control key: rotation mode
    if (_keyControlPressed) {
      _rotateModeEnabled = true;
      // ...and disable the rest
      _scaleModeEnabled = false;
      _translateModeEnabled = false;

      //Logger::logDEBUG("set rotate mode, constrained=%d", _constrainedSubmodeEnabled);
    } else {
      if (_rotateModeEnabled) {
	//Logger::logDEBUG("unset rotate mode");
	_rotateModeEnabled = false;
      }
    }

    // shift key: translation mode
    if (_keyShiftPressed) {
      _translateModeEnabled = true;
      // ...and disable the rest
      _scaleModeEnabled = false;
      _rotateModeEnabled = false;

      //Logger::logDEBUG("set translate mode, constrained=%d", _constrainedSubmodeEnabled);
    } else {
      if (_translateModeEnabled) {
	//Logger::logDEBUG("unset translate mode");
	_translateModeEnabled = false;
      }
    }
  }
}

void CameraModeMGED::doZoomScale(float scale)
{
  _radius = _dragOriginalRadius / scale; // divide, because it means zoom in
  if (_radius > RADIUS_MAX_DISTANCE) {
    _radius = RADIUS_MAX_DISTANCE;
  } else if (_radius < RADIUS_MIN_DISTANCE) {
    _radius = RADIUS_MIN_DISTANCE;
  } 
  //Logger::logDEBUG("CameraModeMGED scale: radius=%g, scale=%g", _radius, scale);
}

void CameraModeMGED::cameraControlUpPressed()
{
  // nothing
}

void CameraModeMGED::cameraControlDownPressed()
{
  // nothing
}

void CameraModeMGED::cameraControlLeftPressed()
{
  // nothing
}

void CameraModeMGED::cameraControlRightPressed()
{
  // nothing
}

void CameraModeMGED::cameraControlZoomInPressed()
{
  // nothing
}

void CameraModeMGED::cameraControlZoomOutPressed()
{
  // nothing
}

void CameraModeMGED::cameraControlCenterPressed()
{
  // nothing
}

void CameraModeMGED::cameraControlUpReleased()
{
  panUp();
}

void CameraModeMGED::cameraControlDownReleased()
{
  panDown();
}

void CameraModeMGED::cameraControlLeftReleased()
{
  panLeft();
}

void CameraModeMGED::cameraControlRightReleased()
{
  panRight();
}

void CameraModeMGED::cameraControlZoomInReleased()
{
  doZoomIn();
}

void CameraModeMGED::cameraControlZoomOutReleased()
{
  doZoomOut();
}

void CameraModeMGED::cameraControlCenterReleased()
{
  setResetToCenter(true);
}

void CameraModeMGED::doZoomIn()
{
  divideVarWithLimit(_radius, ZOOM_STEP, RADIUS_MIN_DISTANCE);
}

void CameraModeMGED::doZoomOut()
{
  multiplyVarWithLimit(_radius, ZOOM_STEP, RADIUS_MAX_DISTANCE);
}

void CameraModeMGED::panScreenRelativeCoords(int x, int y)
{
  float panWidth = _camera->getOrthoWindowWidth() * (x/static_cast<float>(_windowWidth));
  float panHeight = _camera->getOrthoWindowHeight() * (y/static_cast<float>(_windowHeight));
  pan(panWidth, panHeight, _dragOriginalCenter);
}

void CameraModeMGED::panUp()
{
  pan(0, (_camera->getOrthoWindowHeight()/PAN_FRACTION));
}

void CameraModeMGED::panDown()
{
  pan(0, -(_camera->getOrthoWindowHeight()/PAN_FRACTION));
}

void CameraModeMGED::panLeft()
{
  pan((_camera->getOrthoWindowWidth()/PAN_FRACTION), 0);
}

void CameraModeMGED::panRight()
{
  pan(-(_camera->getOrthoWindowWidth()/PAN_FRACTION), 0);
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
