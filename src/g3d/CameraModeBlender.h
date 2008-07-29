/*                C A M E R A M O D E B L E N D E R . H
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

/** @file CameraModeBlender.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Declaration of the Camera mode "Blender" of 3D Geometry Editor
 *	(g3d).
 */

#ifndef __G3D_CAMERAMODEBLENDER_H__
#define __G3D_CAMERAMODEBLENDER_H__


#include "CameraMode.h"


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
  /** @see CameraMode::injectMouseScrolled */
  virtual bool injectMouseScrolled(Direction direction);

private:
  /** Default rotation step */
  static const float ROTATION_STEP; // radians
  /** Default pan distance */
  static const float PAN_FRACTION; // ratio
  /** Default zoom step ratio */
  static const float ZOOM_STEP; // ratio

  /** Mode */
  bool _dragModeEnabled;
  /** Mode helper */
  int _dragModeOriginX;
  /** Mode helper */
  int _dragModeOriginY;

  /** Mode */
  bool _panModeEnabled;


  /** Common functionality for all places needing it */
  void doZoomIn();
  /** Common functionality for all places needing it */
  void doZoomOut();
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
