/*                C A M E R A M O D E S . H
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

/** @file CameraModes.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Declaration and implementation of the Camera modes of 3D
 *	Geometry Editor (g3d).
 */

#ifndef __G3D_CAMERAMODES_H__
#define __G3D_CAMERAMODES_H__


#include <OGRE/OgreCamera.h>
#include <OGRE/OgreSceneNode.h>

#include "Logger.h"


/** Pi constant */
#define PI_NUMBER 3.14159265358979323846


/** @brief Base class for camera mode
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Implements the actions asked to the camera, each derived class
 * behaves different according to its own nature.  We keep common
 * functionality implemented here, like the node that all cameras
 * follow (they will calculate the offset and looking-at with the
 * target node as base).
 */
class CameraMode
{
public:
  /** Default constructor */
  CameraMode(const char* name) :
    _name(name),
    _actionZoomingIn(false), _actionZoomingOut(false),
    _actionUp(false), _actionDown(false),
    _actionLeft(false), _actionRight(false),
    _actionRequestToCenter(false)
    { }
  /** Destructor */
  virtual ~CameraMode() { }

  /** Get the name */
  const char* getName() const {
    return _name;
  }

  /** Set flag for this camera action */
  void setZoomingIn(bool b) {
    _actionZoomingIn = b;
  }
  /** Set flag for this camera action */
  void setZoomingOut(bool b) {
    _actionZoomingOut = b;
  }
  /** Set flag for this camera action */
  void setUp(bool b) {
    _actionUp = b;
  }
  /** Set flag for this camera action */
  void setDown(bool b) {
    _actionDown = b;
  }
  /** Set flag for this camera action */
  void setLeft(bool b) {
    _actionLeft = b;
  }
  /** Set flag for this camera action */
  void setRight(bool b) {
    _actionRight = b;
  }
  /** Set flag for this camera action */
  void setRequestToCenter(bool b) {
    _actionRequestToCenter = b;
  }

  /** Called every frame via camera manager, with the time elapsed
   * since last update, so we move the camera of the engine (depending
   * on camera mode and commands issued by player), and thus control
   * how do we view the scene.  This is where each camera mode behaves
   * different. */
  virtual void updateCamera(Ogre::Camera* camera, double elapsedSeconds) = 0;

protected:
  /** Name of the mode */
  const char* _name;

  /** Flag for camera action */
  bool _actionZoomingIn;
  /** Flag for camera action */
  bool _actionZoomingOut;
  /** Flag for camera action */
  bool _actionUp;
  /** Flag for camera action */
  bool _actionDown;
  /** Flag for camera action */
  bool _actionLeft;
  /** Flag for camera action */
  bool _actionRight;
  /** Flag for camera action */
  bool _actionRequestToCenter;
};


/** @brief Base class for camera mode
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Orbital camera mode.  The behavior of this camera mode is that it
 * orbits the center, with zoom to control the radius and the keys to
 * go up/down/left/right controlling movement from "pole to pole" and
 * "equator".
 */
class CameraModeOrbital : public CameraMode
{
public:
  /** Default constructor */
  CameraModeOrbital() :
    CameraMode("Orbital"), 
    _horizontalRot(0.0), _verticalRot(-PI_NUMBER/24.0f), _radius(100.0f)
    { }

  /** @see CameraMode::updateCamera */
  virtual void updateCamera(Ogre::Camera* camera, double elapsedSeconds) {
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

private:
  /** Speed of the zoom in/out per second */
  static const float ZOOM_RATIO = 4.0f; // this times every second
  /** Maximum radius distance */
  static const float RADIUS_MAX_DISTANCE = 10000.0f; // m
  /** Minimum radius distance */
  static const float RADIUS_MIN_DISTANCE = 0.1f; // m
  /** Speed of the rotation */
  static const float ROTATION_SPEED = PI_NUMBER/2.0f; // 4s for full revolution

  /** Current horizontal rotation */
  float _horizontalRot;
  /** Current vertical rotation */
  float _verticalRot;
  /** Current radius */
  float _radius;
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
