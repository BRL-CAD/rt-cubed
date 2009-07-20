/*                C A M E R A M O D E . C X X
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

/** @file CameraMode.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the base class for Camera modes of 3D
 *	Geometry Editor (g3d).
 */

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneNode.h>
#include <OGRE/OgreViewport.h>

#include "CameraMode.h"

#include "Logger.h"


/*******************************************************************************
 * CameraMode
 ******************************************************************************/
const float CameraMode::ROTATION_DEFAULT_SPEED = (2.0f*M_PI)/4.0f; // 4s for full revolution
const float CameraMode::ZOOM_DEFAULT_SPEED_RATIO = 4.0f; // 4 times per second
const float CameraMode::RADIUS_MAX_DISTANCE = 10000.0f; // m
const float CameraMode::RADIUS_MIN_DISTANCE = 0.1f; // m
const float CameraMode::RADIUS_DEFAULT_DISTANCE = 500.0f; // m

CameraMode::CameraMode(const char* name) :
  _name(name),
  _camera(0),
  _windowWidth(0), _windowHeight(0),
  _orthoWindowDefaultWidth(0.0f), _orthoWindowDefaultHeight(0.0f),
  _actionRotateX(NEUTRAL), _actionRotateY(NEUTRAL), _actionRotateZ(NEUTRAL),
  _actionZoom(NEUTRAL),
  _actionPan(0, 0, 0),
  _actionResetToCenter(false),
  _rotationSpeed(ROTATION_DEFAULT_SPEED),
  _zoomSpeedRatio(ZOOM_DEFAULT_SPEED_RATIO),
  _radius(RADIUS_DEFAULT_DISTANCE), _previousRadius(_radius),
  _horizontalRot(0.0f), _verticalRot(0.0f),
  _center(0, 0, 0)
{
}

void CameraMode::updateCamera(Ogre::Camera* camera, double elapsedSeconds)
{
  _camera = camera;
  _windowWidth = camera->getViewport()->getActualWidth();
  _windowHeight = camera->getViewport()->getActualHeight();
  if (_orthoWindowDefaultWidth == 0.0f) {
    _orthoWindowDefaultWidth = _camera->getOrthoWindowWidth();
    _orthoWindowDefaultHeight = _camera->getOrthoWindowHeight(); 
  }

  // apply rotations
  if (_actionResetToCenter) {
    // center (reset rotation) when requested
    _horizontalRot = 0.0f;
    _verticalRot = 0.0f;
    _center = SimpleVector3(0.0f, 0.0f, 0.0f);
    _radius = RADIUS_DEFAULT_DISTANCE;
    _previousRadius = _radius;
    _camera->setOrthoWindowWidth(_orthoWindowDefaultWidth);
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

  // set the resulting position to the camera
  if (_actionPan != SimpleVector3(0, 0, 0)) {
    //Logger::logDEBUG("panning: %g %g %g", _actionPan.x, _actionPan.y, _actionPan.z);

    // get center relative to camera
    Ogre::Vector3 cameraPos = camera->getPosition();
    Ogre::Vector3 difference(_center.x, _center.y, _center.z);
    difference -= cameraPos;
    // pan camera (relative to its position)
    camera->moveRelative(Ogre::Vector3(-_actionPan.x, _actionPan.y, 0));
    cameraPos = camera->getPosition();
    //Logger::logDEBUG(" - pos: %g %g %g", cameraPos.x, cameraPos.y, cameraPos.z);
    // restore center
    _center.x = cameraPos.x + difference.x;
    _center.y = cameraPos.y + difference.y;
    _center.z = cameraPos.z + difference.z;
    //Logger::logDEBUG(" - center: %g %g %g", _center.x, _center.y, _center.z);
    camera->lookAt(_center.x, _center.y, _center.z);

    // stop panning
    _actionPan = SimpleVector3(0, 0, 0);
  } else {
    Ogre::SceneNode tmpNode(0);

    // set initial center
    Ogre::Vector3 centerTranslation(_center.x, _center.y, _center.z);
    tmpNode.translate(centerTranslation, Ogre::SceneNode::TS_LOCAL);

    // rotations
    tmpNode.yaw(Ogre::Radian(_horizontalRot));
    tmpNode.pitch(Ogre::Radian(_verticalRot));

    // position -- push back given radius
    Ogre::Vector3 radiusDistance(0, 0, _radius);
    tmpNode.translate(radiusDistance, Ogre::SceneNode::TS_LOCAL);

    if (camera->getPosition() != tmpNode.getPosition()) {
      //Logger::logDEBUG("Camera position (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);

      camera->setPosition(tmpNode.getPosition());
      camera->lookAt(_center.x, _center.y, _center.z);
    }

    // zoom for orthogonal mode
    if (_camera->getProjectionType() == Ogre::PT_ORTHOGRAPHIC
	&& _previousRadius != _radius) {
      float orthoRatio = _radius/_previousRadius;
      _camera->setOrthoWindowWidth(orthoRatio * _camera->getOrthoWindowWidth());
      //Logger::logDEBUG("Orthogonal ratio: %g", orthoRatio);
      //Logger::logDEBUG("window width: %g", _camera->getOrthoWindowWidth());
    } else if (_camera->getProjectionType() == Ogre::PT_PERSPECTIVE) {
      _camera->setOrthoWindowWidth(_orthoWindowDefaultWidth);
    }

    // update _previousRadius variable, for next time
    _previousRadius = _radius;
  }
}

const char* CameraMode::getName() const
{
  return _name;
}

float CameraMode::getXRotation() const
{
  // vertical rotation is only half
  float radians = getVarWithinLimits(2.0f*(_camera->getRealOrientation().getPitch().valueRadians() + M_PI/2.0f),
				     0.0f,
				     2*M_PI);
  return radians;
}

float CameraMode::getYRotation() const
{
  float radians = getVarWithinLimits(_camera->getRealOrientation().getYaw().valueRadians() + M_PI,
				     0.0f,
				     2*M_PI);
  return radians;
}

float CameraMode::getZRotation() const
{
  float radians = getVarWithinLimits(_camera->getRealOrientation().getRoll().valueRadians() + M_PI,
				     0.0f,
				     2*M_PI);
  return radians;
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

void CameraMode::pan(float x, float y, SimpleVector3 originalCenter)
{
  _actionPan = SimpleVector3(x, y, 0);
  _center = originalCenter;
}

void CameraMode::pan(float x, float y)
{
  _actionPan = SimpleVector3(x, y, 0);
  //Logger::logDEBUG("panning: %g %g", _actionPan.x, _actionPan.y);
}

float CameraMode::degreesToRadians(float degrees)
{
  return (degrees*M_PI)/180.0f;
}

void CameraMode::increaseVarWithLimit(float& var, float value, float limit)
{
  var += value;
  if (var > limit) {
    var = limit;
  }
}

void CameraMode::decreaseVarWithLimit(float& var, float value, float limit)
{
  var -= value;
  if (var < limit) {
    var = limit;
  }
}

void CameraMode::multiplyVarWithLimit(float& var, float value, float limit)
{
  var *= value;
  if (var > limit) {
    var = limit;
  }
}

void CameraMode::divideVarWithLimit(float& var, float value, float limit)
{
  var /= value;
  if (var < limit) {
    var = limit;
  }
}

float CameraMode::getVarWithinLimits(float var, float min, float max)
{
  if (var < min) {
    return min;
  } else if (var > max) {
    return max;
  } else {
    return var;
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
