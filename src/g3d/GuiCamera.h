/*                  G U I C A M E R A . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by
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


#include <Mocha/Value.h>

#include "GuiBaseWindow.h"
#include "Observer.h"


class GuiWidgetRotation;
namespace RBGui {
  class ButtonWidget;
  class GuiElement;
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


  /** Callback for "MousePressed" in the control buttons */
  void callbackButtonUpMousePressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MousePressed" in the control buttons */
  void callbackButtonDownMousePressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MousePressed" in the control buttons */
  void callbackButtonLeftMousePressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MousePressed" in the control buttons */
  void callbackButtonRightMousePressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MousePressed" in the control buttons */
  void callbackButtonZoomInMousePressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MousePressed" in the control buttons */
  void callbackButtonZoomOutMousePressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MousePressed" in the control buttons */
  void callbackButtonCenterMousePressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MouseReleased" in the control buttons */
  void callbackButtonUpMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MouseReleased" in the control buttons */
  void callbackButtonDownMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MouseReleased" in the control buttons */
  void callbackButtonLeftMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MouseReleased" in the control buttons */
  void callbackButtonRightMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MouseReleased" in the control buttons */
  void callbackButtonZoomInMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MouseReleased" in the control buttons */
  void callbackButtonZoomOutMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "MouseReleased" in the control buttons */
  void callbackButtonCenterMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& data);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
