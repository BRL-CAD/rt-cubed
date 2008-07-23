/*                C A M E R A M O D E M G E D . H
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

/** @file CameraModeMGED.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Declaration of the Camera mode "MGED" of 3D Geometry Editor
 *	(g3d).
 */

#ifndef __G3D_CAMERAMODEMGED_H__
#define __G3D_CAMERAMODEMGED_H__


#include "CameraMode.h"


/** @brief MGED camera mode
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * The behavior of this camera tries to mimic the behaviour of
 * traditional BRL-CAD program MGED.  The shift-grips bindings are
 * described in:
 * http://brlcad.org/w/images/8/8c/Shift_Grips_Quick_Reference_Guide.pdf
 */
class CameraModeMGED : public CameraMode
{
public:
  /** Default constructor */
  CameraModeMGED();

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
  /** Default rotation step */
  static const float ROTATION_STEP; // radians
  /** Default pan distance */
  static const float PAN_STEP; // m
  /** Default zoom step ratio */
  static const float ZOOM_STEP; // ratio
  /** Default zoom scale ratio */
  static const float ZOOM_SCALE; // ratio

  /** Key state */
  bool _keyControlPressed;
  /** Key state */
  bool _keyAltPressed;
  /** Key state */
  bool _keyShiftPressed;

  /** Mode */
  bool _translateModeEnabled;
  /** Mode */
  bool _rotateModeEnabled;
  /** Mode */
  bool _scaleModeEnabled;
  /** Submode */
  bool _constrainedSubmodeEnabled;
  /** Mode helper */
  Axis _constrainedToAxis;
  /** Mode helper */
  int _mouseButtonsPressed;
  /** Mode helper */
  int _dragOriginX;
  /** Mode helper */
  int _dragOriginY;
  /** Mode helper */
  float _dragOriginalRadius;
  /** Mode helper */
  SimpleVector3 _dragOriginalCenter;
  

  /** Common functionality for all places needing it */
  void setMode();
  /** Common functionality for all places needing it */
  void doZoomScale(float scale);
  /** Common functionality for all places needing it */
  void doZoomIn();
  /** Common functionality for all places needing it */
  void doZoomOut();
  /** Common functionality for all places needing it */
  void panScreenRelativeCoords(int x, int y);
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
