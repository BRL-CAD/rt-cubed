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

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneNode.h>

#include "Logger.h"
#include "CameraModes.h"


/** Pi constant */
#define PI_NUMBER 3.14159265358979323846


/*******************************************************************************
 * CameraMode
 ******************************************************************************/
CameraMode::CameraMode(const char* name) :
  _name(name),
  _actionZoomingIn(false), _actionZoomingOut(false),
  _actionUp(false), _actionDown(false),
  _actionLeft(false), _actionRight(false),
  _actionRequestToCenter(false)
{
}

const char* CameraMode::getName() const
{
  return _name;
}

void CameraMode::setZoomingIn(bool b)
{
  _actionZoomingIn = b;
}

void CameraMode::setZoomingOut(bool b)
{
  _actionZoomingOut = b;
}

void CameraMode::setUp(bool b)
{
  _actionUp = b;
}

void CameraMode::setDown(bool b)
{
  _actionDown = b;
}

void CameraMode::setLeft(bool b)
{
  _actionLeft = b;
}

void CameraMode::setRight(bool b)
{
  _actionRight = b;
}

void CameraMode::setRequestToCenter(bool b)
{
  _actionRequestToCenter = b;
}


/*******************************************************************************
 * CameraModeOrbital
 ******************************************************************************/
const float CameraModeOrbital::ZOOM_RATIO = 4.0f; // this times every second
const float CameraModeOrbital::RADIUS_MAX_DISTANCE = 10000.0f; // m
const float CameraModeOrbital::RADIUS_MIN_DISTANCE = 0.1f; // m
const float CameraModeOrbital::ROTATION_SPEED = PI_NUMBER/2.0f; // 4s for full revolution

CameraModeOrbital::CameraModeOrbital() :
  CameraMode("Orbital"), 
  _horizontalRot(0.0), _verticalRot(-PI_NUMBER/24.0f), _radius(100.0f)
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
    if (_actionUp) {
      _verticalRot += ROTATION_SPEED * elapsedSeconds;
    } else if (_actionDown) {
      _verticalRot -= ROTATION_SPEED * elapsedSeconds;
    }

    // horizontal rotation
    if (_actionLeft) {
      _horizontalRot += ROTATION_SPEED * elapsedSeconds;
    } else if (_actionRight) {
      _horizontalRot -= ROTATION_SPEED * elapsedSeconds;
    }
  }

  // radius
  if (_actionZoomingIn) {
    _radius /= 1.0f + (ZOOM_RATIO*elapsedSeconds);
    if (_radius < RADIUS_MIN_DISTANCE)
      _radius = RADIUS_MIN_DISTANCE;
  } else if (_actionZoomingOut) {
    _radius *= 1.0f + (ZOOM_RATIO*elapsedSeconds);
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
    Logger::logINFO("Camera position (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);

    camera->setPosition(tmpNode.getPosition());
    camera->lookAt(0, 0, 0);
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
