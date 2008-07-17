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


/*******************************************************************************
 * CameraMode
 ******************************************************************************/
const float CameraMode::DEFAULT_ROTATION_SPEED = (2.0f*PI_NUMBER)/4.0f; // 4s for full revolution
const float CameraMode::DEFAULT_ZOOM_SPEED_RATIO = 4.0f; // 4 times per second
const float CameraMode::RADIUS_MAX_DISTANCE = 10000.0f; // m
const float CameraMode::RADIUS_MIN_DISTANCE = 0.1f; // m

CameraMode::CameraMode(const char* name) :
  _name(name),
  _actionRotateX(NEUTRAL), _actionRotateY(NEUTRAL), _actionRotateZ(NEUTRAL),
  _actionZoom(NEUTRAL),
  _actionRequestToCenter(false),
  _rotationSpeed(DEFAULT_ROTATION_SPEED),
  _zoomSpeedRatio(DEFAULT_ZOOM_SPEED_RATIO),
  _radius(500.0f), _horizontalRot(0.0f), _verticalRot(0.0f)
{
}

const char* CameraMode::getName() const
{
  return _name;
}

void CameraMode::setRequestToCenter(bool b)
{
  _actionRequestToCenter = b;
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


/*******************************************************************************
 * CameraModeOrbital
 ******************************************************************************/
CameraModeOrbital::CameraModeOrbital() :
  CameraMode("Orbital")
{
}

void CameraModeOrbital::updateCamera(Ogre::Camera* camera, double elapsedSeconds)
{
  // apply rotations
  if (_actionRequestToCenter) {
    // center (reset rotation) when requested
    _horizontalRot = 0.0;
    _verticalRot = -PI_NUMBER/24.0f;
    _actionRequestToCenter = false;
  } else {
    // vertical rotation
    if (_actionRotateX == POSITIVE) {
      _verticalRot += _rotationSpeed * elapsedSeconds;
      if (_verticalRot >= PI_NUMBER/2.0f)
	_verticalRot = (PI_NUMBER/2.0f)-0.01f;
    } else if (_actionRotateX == NEGATIVE) {
      _verticalRot -= _rotationSpeed * elapsedSeconds;
      if (_verticalRot <= -PI_NUMBER/2.0f)
	_verticalRot = -(PI_NUMBER/2.0f)+0.01f;
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
    _radius /= 1.0f + (DEFAULT_ZOOM_SPEED_RATIO*elapsedSeconds);
    if (_radius < RADIUS_MIN_DISTANCE)
      _radius = RADIUS_MIN_DISTANCE;
  } else if (_actionZoom == NEGATIVE) {
    _radius *= 1.0f + (DEFAULT_ZOOM_SPEED_RATIO*elapsedSeconds);
    if (_radius > RADIUS_MAX_DISTANCE)
      _radius = RADIUS_MAX_DISTANCE;
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
  if (pos != tmpNode.getPosition()) {
    //Logger::logDEBUG("Camera position (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);

    camera->setPosition(tmpNode.getPosition());
    camera->lookAt(0, 0, 0);
  }
}

bool CameraModeOrbital::injectKeyPressed(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_E:
    setRequestToCenter(true);
    return true;
  case OIS::KC_Z:
    setZoom(CameraMode::POSITIVE);
    return true;
  case OIS::KC_Q:
    setZoom(CameraMode::NEGATIVE);
    return true;
  case OIS::KC_W:
      setRotateX(CameraMode::POSITIVE);
      return true;
  case OIS::KC_S:
    setRotateX(CameraMode::NEGATIVE);
    return true;
  case OIS::KC_A:
    setRotateY(CameraMode::POSITIVE);
    return true;
  case OIS::KC_D:
    setRotateY(CameraMode::NEGATIVE);
    return true;
  default:
    return false;
  }
}

bool CameraModeOrbital::injectKeyReleased(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_Z:
  case OIS::KC_Q:
    setZoom(CameraMode::NEUTRAL);
    return true;
  case OIS::KC_W:
  case OIS::KC_S:
    setRotateX(CameraMode::NEUTRAL);
    return true;
  case OIS::KC_A:
  case OIS::KC_D:
    setRotateY(CameraMode::NEUTRAL);
    return true;
  default:
    return false;
  }
}

bool CameraModeOrbital::injectMouseMotion(int x, int y)
{
  // nothing to do
}

bool CameraModeOrbital::injectMousePressed(OIS::MouseButtonID buttonId, int x, int y)
{
  // nothing to do
}

bool CameraModeOrbital::injectMouseReleased(OIS::MouseButtonID buttonId, int x, int y)
{
  // nothing to do
}


/*******************************************************************************
 * CameraModeBlender
 ******************************************************************************/
CameraModeBlender::CameraModeBlender() :
  CameraMode("Blender"),
  _dragModeEnabled(false), _dragModeLastX(0), _dragModeLastY(0)
{
}

void CameraModeBlender::updateCamera(Ogre::Camera* camera, double elapsedSeconds)
{
  // apply rotations
  if (_actionRequestToCenter) {
    // center (reset rotation) when requested
    _horizontalRot = 0.0;
    _verticalRot = -PI_NUMBER/24.0f;
    _actionRequestToCenter = false;
  } else {
    // vertical rotation
    if (_actionRotateX == POSITIVE) {
      _verticalRot += _rotationSpeed * elapsedSeconds;
      if (_verticalRot >= PI_NUMBER/2.0f)
	_verticalRot = (PI_NUMBER/2.0f)-0.01f;
    } else if (_actionRotateX == NEGATIVE) {
      _verticalRot -= _rotationSpeed * elapsedSeconds;
      if (_verticalRot <= -PI_NUMBER/2.0f)
	_verticalRot = -(PI_NUMBER/2.0f)+0.01f;
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
    _radius /= 1.0f + (DEFAULT_ZOOM_SPEED_RATIO*elapsedSeconds);
    if (_radius < RADIUS_MIN_DISTANCE)
      _radius = RADIUS_MIN_DISTANCE;
  } else if (_actionZoom == NEGATIVE) {
    _radius *= 1.0f + (DEFAULT_ZOOM_SPEED_RATIO*elapsedSeconds);
    if (_radius > RADIUS_MAX_DISTANCE)
      _radius = RADIUS_MAX_DISTANCE;
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
  if (pos != tmpNode.getPosition()) {
    //Logger::logDEBUG("Camera position (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);

    camera->setPosition(tmpNode.getPosition());
    camera->lookAt(0, 0, 0);
  }
}

bool CameraModeBlender::injectKeyPressed(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_E:
    setRequestToCenter(true);
    return true;
  case OIS::KC_Z:
    setZoom(CameraMode::POSITIVE);
    return true;
  case OIS::KC_Q:
    setZoom(CameraMode::NEGATIVE);
    return true;
  case OIS::KC_W:
      setRotateX(CameraMode::POSITIVE);
      return true;
  case OIS::KC_S:
    setRotateX(CameraMode::NEGATIVE);
    return true;
  case OIS::KC_A:
    setRotateY(CameraMode::POSITIVE);
    return true;
  case OIS::KC_D:
    setRotateY(CameraMode::NEGATIVE);
    return true;
  default:
    return false;
  }
}

bool CameraModeBlender::injectKeyReleased(OIS::KeyCode keyCode)
{
  switch (keyCode) {
  case OIS::KC_Z:
  case OIS::KC_Q:
    setZoom(CameraMode::NEUTRAL);
    return true;
  case OIS::KC_W:
  case OIS::KC_S:
    setRotateX(CameraMode::NEUTRAL);
    return true;
  case OIS::KC_A:
  case OIS::KC_D:
    setRotateY(CameraMode::NEUTRAL);
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
