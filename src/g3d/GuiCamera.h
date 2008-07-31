/*                  G U I C A M E R A . H
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
 * the U.S. Army Research Laboratory.
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

/** @file GuiCamera.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header of the GuiCamera class of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_GUICAMERA_H__
#define __G3D_GUICAMERA_H__


#include "GuiBaseWindow.h"
#include "Observer.h"

#include <Mocha/Value.h>


class GuiWidgetRotation;
namespace RBGui {
  class ButtonWidget;
  class ImageWidget;
}


/**
 * @brief GUI Camera class of the 3D Geometry Editor.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * This class implements the Camera control for the application.
 */
class GuiCamera : public GuiBaseWindow, public Observer
{
public:
  /**
   * Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiCamera(RBGui::GuiManager& guiMgr);

  /** Destructor */
  ~GuiCamera();

  /** @see GuiBaseWindow::resize */
  virtual void resize(float contentLeft, float contentTop, float contentWidth, float contentHeight);

  /** @see Observer::update */
  virtual void update(const ObserverEvent& event);

private:
  /** Widgets for rotation */
  GuiWidgetRotation* _xRotation;
  /** Widgets for rotation */
  GuiWidgetRotation* _yRotation;
  /** Widgets for rotation */
  GuiWidgetRotation* _zRotation;
  /** Widgets for rotation */
  RBGui::ButtonWidget* _up;
  /** Widgets for rotation */
  RBGui::ButtonWidget* _down;
  /** Widgets for rotation */
  RBGui::ButtonWidget* _left;
  /** Widgets for rotation */
  RBGui::ButtonWidget* _right;
  /** Widgets for rotation */
  RBGui::ButtonWidget* _zoomIn;
  /** Widgets for rotation */
  RBGui::ButtonWidget* _zoomOut;
  /** Widgets for rotation */
  RBGui::ButtonWidget* _center;
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
