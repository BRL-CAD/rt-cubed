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


#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>


namespace Ogre {
  class Camera;
}


/** @brief Base class for camera mode
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Implements the actions asked to the camera, each derived class
 * behaves different according to its own nature (assigns different
 * key/mouse bindings for the actions of translation, rotation, etc).
 *
 * We keep common functionality implemented here.
 */
class CameraMode
{
public:
  /** Direction value: Negative/Neutral/Positive */
  enum Direction {
    NEGATIVE = -1,
    NEUTRAL = 0,
    POSITIVE = 1
  };

  /** Default constructor */
  CameraMode(const char* name);
  /** Destructor */
  virtual ~CameraMode() { }

  /** Get the name */
  const char* getName() const;

  /** Set flag for this camera action */
  void setZoom(Direction direction);
  /** Set flag for this camera action */
  void setRotateX(Direction direction);
  /** Set flag for this camera action */
  void setRotateY(Direction direction);
  /** Set flag for this camera action */
  void setRotateZ(Direction direction);

  /** Set/get value for this camera value */
  void setRotationSpeed(float speed);
  /** Set/get value for this camera value */
  float getRotationSpeed() const;
  /** Set/get value for this camera value */
  void setZoomSpeedRatio(float ratio);
  /** Set/get value for this camera value */
  float getZoomSpeedRatio() const;

  /** Set flag for this camera action */
  void setRequestToCenter(bool b);

  /** Stop all movements and rotations */
  void stop();

  /** Called every frame via camera manager, with the time elapsed
   * since last update, so we move the camera of the engine (depending
   * on camera mode and commands issued by player), and thus control
   * how do we view the scene.  This is where each camera mode behaves
   * different. */
  virtual void updateCamera(Ogre::Camera* camera, double elapsedSeconds) = 0;
  /** Inject input */
  virtual bool injectKeyPressed(OIS::KeyCode keyCode) = 0;
  /** Inject input */
  virtual bool injectKeyReleased(OIS::KeyCode keyCode) = 0;
  /** Inject input */
  virtual bool injectMouseMotion(int x, int y) = 0;
  /** Inject input */
  virtual bool injectMousePressed(OIS::MouseButtonID buttonId, int x, int y) = 0;
  /** Inject input */
  virtual bool injectMouseReleased(OIS::MouseButtonID buttonId, int x, int y) = 0;


protected:
  /** Speed of the rotation */
  static const float DEFAULT_ROTATION_SPEED; // cycles/second
  /** Speed ratio of the zoom */
  static const float DEFAULT_ZOOM_SPEED_RATIO; // times per second
  /** Maximum radius distance */
  static const float RADIUS_MAX_DISTANCE; // m
  /** Minimum radius distance */
  static const float RADIUS_MIN_DISTANCE; // m

  /** Name of the mode */
  const char* _name;

  /** Flag for camera action */
  Direction _actionRotateX;
  /** Flag for camera action */
  Direction _actionRotateY;
  /** Flag for camera action */
  Direction _actionRotateZ;
  /** Flag for camera action */
  Direction _actionZoom;

  /** Flag for camera action */
  bool _actionRequestToCenter;

  /** Basic value for calculation */
  float _rotationSpeed; /// cycles/second
  /** Basic value for calculation */
  float _zoomSpeedRatio; /// times per second
  /** Current radius */
  float _radius;
  /** Current horizontal rotation */
  float _horizontalRot;
  /** Current vertical rotation */
  float _verticalRot;
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
  /** @see CameraMode::injectKeyPressed */
  virtual bool injectKeyPressed(OIS::KeyCode keyCode);
  /** @see CameraMode::injectKeyReleased */
  virtual bool injectKeyReleased(OIS::KeyCode keyCode);
  /** @see CameraMode::injectMouseMotion */
  virtual bool injectMouseMotion(int x, int y);
  /** @see CameraMode::injectMousePressed */
  virtual bool injectMousePressed(OIS::MouseButtonID buttonId, int x, int y);
  /** @see CameraMode::injectMouseReleased */
  virtual bool injectMouseReleased(OIS::MouseButtonID buttonId, int x, int y);
};


/** @brief MGED camera mode
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * The behavior of this camera tries to mimic the behaviour of
 * traditional BRL-CAD program MGED.  The shift-grips bindings are
 * described in:
 * http://brlcad.org/w/images/8/8c/Shift_Grips_Quick_Reference_Guide.pdf
 */


/** @brief Blender camera mode
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * The behavior of this camera tries to mimic the behaviour of
 * Blender modeling program.
 */
class CameraModeBlender : public CameraMode
{
public:
  /** Default constructor */
  CameraModeBlender();

  /** @see CameraMode::updateCamera */
  virtual void updateCamera(Ogre::Camera* camera, double elapsedSeconds);
  /** @see CameraMode::injectKeyPressed */
  virtual bool injectKeyPressed(OIS::KeyCode keyCode);
  /** @see CameraMode::injectKeyReleased */
  virtual bool injectKeyReleased(OIS::KeyCode keyCode);
  /** @see CameraMode::injectMouseMotion */
  virtual bool injectMouseMotion(int x, int y);
  /** @see CameraMode::injectMousePressed */
  virtual bool injectMousePressed(OIS::MouseButtonID buttonId, int x, int y);
  /** @see CameraMode::injectMouseReleased */
  virtual bool injectMouseReleased(OIS::MouseButtonID buttonId, int x, int y);

private:
  /** Mode */
  bool _dragModeEnabled;
  /** Mode helper */
  int _dragModeLastX;
  /** Mode helper */
  int _dragModeLastY;
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
