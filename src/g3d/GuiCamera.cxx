/*                  G U I C A M E R A . C X X
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

/** @file GuiCamera.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the GUI Camera class of 3D Geometry Editor
 *	(g3d).
 */

#include <OIS/OISKeyboard.h>
#include <OGRE/OgreRenderWindow.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/Texture.h>
#include <RBGui/Window.h>
#include <RBGui/Widgets/ButtonWidget.h>
#include <RBGui/Widgets/ImageWidget.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "GuiCamera.h"

#include "Logger.h"
#include "CameraManager.h"
#include "GuiWindowManager.h"
#include "GuiWidgetRotation.h"


/*******************************************************************************
 * GuiCamera
 ******************************************************************************/
GuiCamera::GuiCamera(RBGui::GuiManager& guiMgr) :
  GuiBaseWindow(guiMgr, "Camera", "Camera", true),
  _xRotation(0), _yRotation(0), _zRotation(0),
  _up(0), _down(0), _left(0), _right(0),
  _zoomIn(0), _zoomOut(0), _center(0)
{
  // creating windows and widgets
  _mainWindow->setCloseable(true);
  _mainWindow->setMovable(true);
  _mainWindow->setResizeable(false);
  _mainWindow->setBorderVisible(true);
  _mainWindow->setHideOnClose(true);
  show();

  RBGui::Texture* img = 0;

  _xRotation = static_cast<GuiWidgetRotation*>(_mainWindow->createWidget("GuiWidgetRotation"));
  _xRotation->setName("X Rotation");
  _xRotation->setLabel("X rot");
  _yRotation = static_cast<GuiWidgetRotation*>(_mainWindow->createWidget("GuiWidgetRotation"));
  _yRotation->setName("Y Rotation");
  _yRotation->setLabel("Y rot");
  _zRotation = static_cast<GuiWidgetRotation*>(_mainWindow->createWidget("GuiWidgetRotation"));
  _zRotation->setName("Z Rotation");
  _zRotation->setLabel("Z rot");

  _up = static_cast<RBGui::ButtonWidget*>(_mainWindow->createWidget("Button"));
  _up->setName("CameraUp button");
  img = GuiWindowManager::instance().getDefaultTheme()->getTexture("BrlcadCameraUp");
  _up->setImage(img);
  _down = static_cast<RBGui::ButtonWidget*>(_mainWindow->createWidget("Button"));
  _down->setName("CameraDown button");
  img = GuiWindowManager::instance().getDefaultTheme()->getTexture("BrlcadCameraDown");
  _down->setImage(img);
  _left = static_cast<RBGui::ButtonWidget*>(_mainWindow->createWidget("Button"));
  _left->setName("CameraLeft button");
  img = GuiWindowManager::instance().getDefaultTheme()->getTexture("BrlcadCameraLeft");
  _left->setImage(img);
  _right = static_cast<RBGui::ButtonWidget*>(_mainWindow->createWidget("Button"));
  _right->setName("CameraRight button");
  img = GuiWindowManager::instance().getDefaultTheme()->getTexture("BrlcadCameraRight");
  _right->setImage(img);
  _zoomIn = static_cast<RBGui::ButtonWidget*>(_mainWindow->createWidget("Button"));
  _zoomIn->setName("CameraZoomIn button");
  img = GuiWindowManager::instance().getDefaultTheme()->getTexture("BrlcadCameraZoomIn");
  _zoomIn->setImage(img);
  _zoomOut = static_cast<RBGui::ButtonWidget*>(_mainWindow->createWidget("Button"));
  _zoomOut->setName("CameraZoomOut button");
  img = GuiWindowManager::instance().getDefaultTheme()->getTexture("BrlcadCameraZoomOut");
  _zoomOut->setImage(img);
  _center = static_cast<RBGui::ButtonWidget*>(_mainWindow->createWidget("Button"));
  _center->setName("CameraCenter button");
  img = GuiWindowManager::instance().getDefaultTheme()->getTexture("BrlcadCameraCenter");
  _center->setImage(img);

  _up->setCallback(&GuiCamera::callbackButtonUpMouseReleased, this, "onMouseReleased");
  _down->setCallback(&GuiCamera::callbackButtonDownMouseReleased, this, "onMouseReleased");
  _left->setCallback(&GuiCamera::callbackButtonLeftMouseReleased, this, "onMouseReleased");
  _right->setCallback(&GuiCamera::callbackButtonRightMouseReleased, this, "onMouseReleased");
  _zoomIn->setCallback(&GuiCamera::callbackButtonZoomInMouseReleased, this, "onMouseReleased");
  _zoomOut->setCallback(&GuiCamera::callbackButtonZoomOutMouseReleased, this, "onMouseReleased");
  _center->setCallback(&GuiCamera::callbackButtonCenterMouseReleased, this, "onMouseReleased");

  GuiWindowManager::instance().registerWindow(this);
  CameraManager::instance().attach(this);
}

GuiCamera::~GuiCamera()
{
  CameraManager::instance().detach(this);

  delete _xRotation; _xRotation = 0;
  delete _yRotation; _yRotation = 0;
  delete _zRotation; _zRotation = 0;
  delete _up; _up = 0;
  delete _down; _down = 0;
  delete _left; _left = 0;
  delete _right; _right = 0;
  delete _zoomIn; _zoomIn = 0;
  delete _zoomOut; _zoomOut = 0;
  delete _center; _center = 0;
}

void GuiCamera::resize(float contentLeft, float contentTop, float contentWidth, float contentHeight)
{
  // main window
  _mainWindow->setPosition(Mocha::Vector2(contentLeft + (contentWidth*0.5f),
					  contentTop));
  _mainWindow->setSize(Mocha::Vector2(contentWidth*0.5f, contentHeight));

  // widgets
  Mocha::Vector2 rotControlSize = _mainWindow->getClientRectangle().getSize();
  rotControlSize.x /= 3.0f;
  rotControlSize.y = 32.0f;

  _xRotation->setPosition(Mocha::Vector2(rotControlSize.x*0.0f, 0.0f));
  _xRotation->setSize(rotControlSize);
  _yRotation->setPosition(Mocha::Vector2(rotControlSize.x*1.0f, 0.0f));
  _yRotation->setSize(rotControlSize);
  _zRotation->setPosition(Mocha::Vector2(rotControlSize.x*2.0f, 0.0f));
  _zRotation->setSize(rotControlSize);

  Mocha::Vector2 arrowControlSize = _mainWindow->getClientRectangle().getSize();
  arrowControlSize.x /= 3.0f;
  arrowControlSize.y /= 10.0f;
  _up->setPosition(Mocha::Vector2(arrowControlSize.x*1.0f, arrowControlSize.y*7.0f));
  _up->setSize(arrowControlSize);
  _down->setPosition(Mocha::Vector2(arrowControlSize.x*1.0f, arrowControlSize.y*9.0f));
  _down->setSize(arrowControlSize);
  _left->setPosition(Mocha::Vector2(arrowControlSize.x*0.0f, arrowControlSize.y*8.0f));
  _left->setSize(arrowControlSize);
  _right->setPosition(Mocha::Vector2(arrowControlSize.x*2.0f, arrowControlSize.y*8.0f));
  _right->setSize(arrowControlSize);
  _zoomIn->setPosition(Mocha::Vector2(arrowControlSize.x*0.0f, arrowControlSize.y*7.0f));
  _zoomIn->setSize(arrowControlSize);
  _zoomOut->setPosition(Mocha::Vector2(arrowControlSize.x*2.0f, arrowControlSize.y*7.0f));
  _zoomOut->setSize(arrowControlSize);
  _center->setPosition(Mocha::Vector2(arrowControlSize.x, arrowControlSize.y*8.0f));
  _center->setSize(arrowControlSize);
}

void GuiCamera::update(const ObserverEvent& event)
{
  try {
    // camera events
    {
      float xRot = 0.0f, yRot = 0.0f, zRot = 0.0f;
      const CameraObserverEvent* e = dynamic_cast<const CameraObserverEvent*>(&event);
      if (e) {
	switch (e->_actionId) {
	case CameraObserverEvent::MODE_CHANGED:
	case CameraObserverEvent::PROJECTION_CHANGED:
	  break;
	case CameraObserverEvent::UPDATED:
	  xRot = CameraManager::instance().getActiveCameraMode().getXRotation();
	  yRot = CameraManager::instance().getActiveCameraMode().getYRotation();
	  zRot = CameraManager::instance().getActiveCameraMode().getZRotation();
	  //Logger::logDEBUG("xRot=%.03f, yRot=%.03f, zRot=%.03f", xRot, yRot, zRot);
	  _xRotation->setProgress(xRot / (2*PI_NUMBER));
	  _yRotation->setProgress(yRot / (2*PI_NUMBER));
	  _zRotation->setProgress(zRot / (2*PI_NUMBER));
	  break;
	default:
	  throw "Action not understood by Observer";
	}
	return;
      }
    }

    // event not processed before
    throw "Event type not expected by Observer";
  } catch (const char* error) {
    Logger::logWARNING("GuiCamera: '%s' event: %s", event._className.c_str(), error);
  }
}

void GuiCamera::callbackButtonUpMousePressed(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlUpPressed();
}

void GuiCamera::callbackButtonDownMousePressed(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlDownPressed();
}

void GuiCamera::callbackButtonLeftMousePressed(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlLeftPressed();
}

void GuiCamera::callbackButtonRightMousePressed(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlRightPressed();
}

void GuiCamera::callbackButtonZoomInMousePressed(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlZoomInPressed();
}

void GuiCamera::callbackButtonZoomOutMousePressed(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlZoomOutPressed();
}

void GuiCamera::callbackButtonCenterMousePressed(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlCenterPressed();
}

void GuiCamera::callbackButtonUpMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlUpReleased();
}

void GuiCamera::callbackButtonDownMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlDownReleased();
}

void GuiCamera::callbackButtonLeftMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlLeftReleased();
}

void GuiCamera::callbackButtonRightMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlRightReleased();
}

void GuiCamera::callbackButtonZoomInMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlZoomInReleased();
}

void GuiCamera::callbackButtonZoomOutMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlZoomOutReleased();
}

void GuiCamera::callbackButtonCenterMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().getActiveCameraMode().cameraControlCenterReleased();
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
