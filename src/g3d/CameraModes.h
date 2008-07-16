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
 *	Declaration of the Camera modes of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_CAMERAMODES_H__
#define __G3D_CAMERAMODES_H__


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
  CameraMode(const char* name);
  /** Destructor */
  virtual ~CameraMode() { }

  /** Get the name */
  const char* getName() const;

  /** Set flag for this camera action */
  void setZoomingIn(bool b);
  /** Set flag for this camera action */
  void setZoomingOut(bool b);
  /** Set flag for this camera action */
  void setUp(bool b);
  /** Set flag for this camera action */
  void setDown(bool b);
  /** Set flag for this camera action */
  void setLeft(bool b);
  /** Set flag for this camera action */
  void setRight(bool b);
  /** Set flag for this camera action */
  void setRequestToCenter(bool b);

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

  /** @see CameraMode::updateCamera */
  virtual void updateCamera(Ogre::Camera* camera, double elapsedSeconds);

private:
  /** Speed of the zoom in/out per second */
  static const float ZOOM_RATIO; // this times every second
  /** Maximum radius distance */
  static const float RADIUS_MAX_DISTANCE; // m
  /** Minimum radius distance */
  static const float RADIUS_MIN_DISTANCE; // m
  /** Speed of the rotation */
  static const float ROTATION_SPEED; // 4s for full revolution

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
