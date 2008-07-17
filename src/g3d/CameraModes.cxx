/*                C A M E R A M O D E S . C X X
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

/** @file CameraModes.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the Camera modes of 3D Geometry Editor
 *	(g3d).
 */

#include "CameraModes.h"

#include "Logger.h"

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneNode.h>
#include <OIS/OISKeyboard.h>


/** Pi constant */
#define PI_NUMBER 3.14159265358979323846


/** Limit for vertical rotations */
const float VERTICAL_ROTATION_MAX_LIMIT = (PI_NUMBER/2.0f)-0.01f;
/** Limit for vertical rotations */
const float VERTICAL_ROTATION_MIN_LIMIT = -(PI_NUMBER/2.0f)+0.01f;


/*******************************************************************************
 * CameraMode
 ******************************************************************************/
const float CameraMode::ROTATION_DEFAULT_SPEED = (2.0f*PI_NUMBER)/4.0f; // 4s for full revolution
const float CameraMode::ZOOM_DEFAULT_SPEED_RATIO = 4.0f; // 4 times per second
const float CameraMode::RADIUS_MAX_DISTANCE = 10000.0f; // m
const float CameraMode::RADIUS_MIN_DISTANCE = 0.1f; // m
const float CameraMode::RADIUS_DEFAULT_DISTANCE = 500.0f; // m

CameraMode::CameraMode(const char* name) :
  _name(name),
  _actionRotateX(NEUTRAL), _actionRotateY(NEUTRAL), _actionRotateZ(NEUTRAL),
  _actionZoom(NEUTRAL),
  _actionResetToCenter(false),
  _rotationSpeed(ROTATION_DEFAULT_SPEED),
  _zoomSpeedRatio(ZOOM_DEFAULT_SPEED_RATIO),
  _radius(RADIUS_DEFAULT_DISTANCE), _horizontalRot(0.0f), _verticalRot(0.0f),
  _center(0, 0, 0)
{
}

void CameraMode::updateCamera(Ogre::Camera* camera, double elapsedSeconds)
{
  // apply rotations
  if (_actionResetToCenter) {
    // center (reset rotation) when requested
    _horizontalRot = 0.0f;
    _verticalRot = 0.0f;
    _center = Vector3(0.0f, 0.0f, 0.0f);
    _radius = RADIUS_DEFAULT_DISTANCE;
    _actionResetToCenter = false;
  } else {
    // vertical rotation
    if (_actionRotateX == POSITIVE) {
      increaseVarWithLimit(_verticalRot,
			   _rotationSpeed * elapsedSeconds,
			   VERTICAL_ROTATION_MAX_LIMIT);
    } else if (_actionRotateX == NEGATIVE) {
      decreaseVarWithLimit(_verticalRot,
			   _rotationSpeed * elapsedSeconds,
			   VERTICAL_ROTATION_MIN_LIMIT);
    }

    // horizontal rotation
    if (_actionRotateY == POSITIVE) {
      _horizontalRot += _rotationSpeed * elapsedSeconds;
    } else if (_actionRotateY == NEGATIVE) {
      _horizontalRot -= _rotationSpeed * elapsedSeconds;
    }
  }

  // radius
  if (_actionZoom == POSITIVE) {
    divideVarWithLimit(_radius,
		       1.0f + (ZOOM_DEFAULT_SPEED_RATIO*elapsedSeconds),
		       RADIUS_MIN_DISTANCE);
  } else if (_actionZoom == NEGATIVE) {
    multiplyVarWithLimit(_radius,
			 1.0f + (ZOOM_DEFAULT_SPEED_RATIO*elapsedSeconds),
			 RADIUS_MAX_DISTANCE);
  }

  Ogre::SceneNode tmpNode(0);

  // rotations
  tmpNode.yaw(Ogre::Radian(_horizontalRot));
  tmpNode.pitch(Ogre::Radian(_verticalRot));

  // position -- push back given radius
  Ogre::Vector3 radiusDistance(0, 0, _radius);
  tmpNode.translate(radiusDistance, Ogre::SceneNode::TS_LOCAL);

  // set the resulting position to the camera
  Ogre::Vector3 pos(camera->getPosition());
  pos.x += _center.x;
  pos.y += _center.y;
  pos.z += _center.z;
  if (pos != tmpNode.getPosition()) {
    //Logger::logDEBUG("Camera position (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);

    camera->setPosition(tmpNode.getPosition());
    camera->lookAt(_center.x, _center.y, _center.z);
  }
}

const char* CameraMode::getName() const
{
  return _name;
}

void CameraMode::setResetToCenter(bool b)
{
  _actionResetToCenter = b;
}

void CameraMode::setZoom(Direction direction)
{
  _actionZoom = direction;
}

void CameraMode::setRotateX(Direction direction)
{
  _actionRotateX = direction;
}

void CameraMode::setRotateY(Direction direction)
{
  _actionRotateY = direction;
}

void CameraMode::setRotateZ(Direction direction)
{
  _actionRotateZ = direction;
}

void CameraMode::setRotationSpeed(float speed)
{
  _rotationSpeed = speed;
}

float CameraMode::getRotationSpeed() const
{
  return _rotationSpeed;
}

void CameraMode::setZoomSpeedRatio(float ratio)
{
  _zoomSpeedRatio = ratio;
}

float CameraMode::getZoomSpeedRatio() const
{
  return _zoomSpeedRatio;
}

void CameraMode::stop()
{
  _actionRotateX = NEUTRAL;
  _actionRotateY = NEUTRAL;
  _actionRotateZ = NEUTRAL;
  _actionZoom = NEUTRAL;
}

float CameraMode::degreesToRadians(float degrees)
{
  return (degrees*2.0f*PI_NUMBER)/360.0f;
}

void CameraMode::increaseVarWithLimit(float& rotation, float incrValue, float limit)
{
  rotation += incrValue;
  if (rotation > limit) {
    rotation = limit;
  }
}

void CameraMode::decreaseVarWithLimit(float& rotation, float incrValue, float limit)
{
  rotation -= incrValue;
  if (rotation < limit) {
    rotation = limit;
  }
}

void CameraMode::multiplyVarWithLimit(float& rotation, float incrValue, float limit)
{
  rotation *= incrValue;
  if (rotation > limit) {
    rotation = limit;
  }
}

void CameraMode::divideVarWithLimit(float& rotation, float incrValue, float limit)
{
  rotation /= incrValue;
  if (rotation < limit) {
    rotation = limit;
  }
}


/*******************************************************************************
 * CameraModeOrbital
 ******************************************************************************/
CameraModeOrbital::CameraModeOrbital() :
  CameraMode("Orbital")
{
}

bool CameraModeOrbital::injectKeyPressed(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_NUMPAD5:
    // reset to center
    setResetToCenter(true);
    return true;
  case OIS::KC_ADD:
    // zoom in
    setZoom(CameraMode::POSITIVE);
    return true;
  case OIS::KC_SUBTRACT:
    // zoom out
    setZoom(CameraMode::NEGATIVE);
    return true;
  case OIS::KC_NUMPAD8:
    // orbit up
    setRotateX(CameraMode::POSITIVE);
    return true;
  case OIS::KC_NUMPAD2:
    // orbit down
    setRotateX(CameraMode::NEGATIVE);
    return true;
  case OIS::KC_NUMPAD4:
    // orbit left
    setRotateY(CameraMode::POSITIVE);
    return true;
  case OIS::KC_NUMPAD6:
    // orbit right
    setRotateY(CameraMode::NEGATIVE);
    return true;
  default:
    return false;
  }
}

bool CameraModeOrbital::injectKeyReleased(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_ADD:
  case OIS::KC_SUBTRACT:
    // zoom
    setZoom(CameraMode::NEUTRAL);
    return true;
  case OIS::KC_NUMPAD8:
  case OIS::KC_NUMPAD2:
    // orbit up/down
    setRotateX(CameraMode::NEUTRAL);
    return true;
  case OIS::KC_NUMPAD4:
  case OIS::KC_NUMPAD6:
    // orbit left/right
    setRotateY(CameraMode::NEUTRAL);
    return true;
  default:
    return false;
  }
}


/*******************************************************************************
 * CameraModeBlender
 ******************************************************************************/
const float CameraModeBlender::ROTATION_STEP = PI_NUMBER/12.0f; // 15 degrees, in radians
const float CameraModeBlender::PAN_STEP = 50.0f; // m
const float CameraModeBlender::ZOOM_STEP = 1.25f; // ratio

CameraModeBlender::CameraModeBlender() :
  CameraMode("Blender"),
  _dragModeEnabled(false), _dragModeLastX(0), _dragModeLastY(0),
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
  if (_dragModeEnabled) {
    float horizontalDiff = x - _dragModeLastX;
    float verticalDiff = y - _dragModeLastY;

    _horizontalRot -= horizontalDiff/100.0f;
    _verticalRot -= verticalDiff/100.0f;
    if (_verticalRot >= PI_NUMBER/2.0f)
      _verticalRot = (PI_NUMBER/2.0f)-0.01f;
    if (_verticalRot <= -PI_NUMBER/2.0f)
      _verticalRot = -(PI_NUMBER/2.0f)+0.01f;

    _dragModeLastX = x;
    _dragModeLastY = y;

    Logger::logDEBUG("mouse moved in drag mode, relative positions: %g %g, rot: %g %g",
		     horizontalDiff, verticalDiff,
		     _horizontalRot, _verticalRot);
  }
}

bool CameraModeBlender::injectMousePressed(OIS::MouseButtonID buttonId, int x, int y)
{
  if (buttonId == OIS::MB_Middle) {
    _dragModeEnabled = true;
    _dragModeLastX = x;
    _dragModeLastY = y;
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
