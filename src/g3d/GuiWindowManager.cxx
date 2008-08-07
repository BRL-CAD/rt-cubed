/*              G U I W I N D O W M A N A G E R . C X X
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

/** @file GuiWindowManager.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the GuiWindowManager class of 3D Geometry
 *	Editor (g3d), along with some internal classes.
 */

#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreWindowEventUtilities.h>
#include <RBGui/Core.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/Window.h>
#include <RBGui/Widgets/ButtonWidget.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "GuiWindowManager.h"

#include "Logger.h"
#include "Application.h"
#include "CameraManager.h"
#include "GuiBaseWindow.h"


/*******************************************************************************
 * GuiWindowManager
 ******************************************************************************/
GuiWindowManager* GuiWindowManager::INSTANCE = 0;

const float GuiWindowManager::TASKBAR_HEIGHT = 16.0f;
const float GuiWindowManager::TOPBAR_HEIGHT = 16.0f;

GuiWindowManager& GuiWindowManager::instance()
{
  if (!INSTANCE)
    INSTANCE = new GuiWindowManager();
  return *INSTANCE;
}

GuiWindowManager::GuiWindowManager() :
  _renderWindow(0), _guiManager(0), _taskbar(0), _topbar(0)
{
  Ogre::WindowEventUtilities::addWindowEventListener(&Application::instance().getRenderWindow(),
						     this);
  CameraManager::instance().attach(this);
}

void GuiWindowManager::setGuiManager(RBGui::GuiManager* guiManager)
{
  _guiManager = guiManager;

  // creating topbar
  {
    _topbar = _guiManager->createWindow();
    _topbar->setName("Topbar");
    _topbar->setText("Topbar");
    _topbar->setCloseable(false);
    _topbar->setMovable(false);
    _topbar->setResizeable(false);
    _topbar->setBorderVisible(false);
    _topbar->show();

    RBGui::ButtonWidget* b = 0;

    // "quit" button
    b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("Quit Button");
    b->setText("Quit");
    b->setCallback(&GuiWindowManager::callbackQuitMouseReleased, this, "onMouseReleased");

    // "fullscreen" button (toggle)
    b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("Fullscreen Button");
    b->setText("Fullscreen");
    b->setCallback(&GuiWindowManager::callbackFullscreenMouseReleased, this, "onMouseReleased");

    // "camera control" button (manipulate rotations, etc)
    b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("ControlCamera Button");
    b->setText("Cam. Control");
    b->setCallback(&GuiWindowManager::callbackControlCameraMouseReleased, this, "onMouseReleased");

    // "camera" button (cycle between modes)
    std::string camMode = CameraManager::instance().getActiveCameraMode().getName();
    b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("CycleCamera Button");
    b->setText(camMode + " Mode");
    b->setCallback(&GuiWindowManager::callbackCycleCameraMouseReleased, this, "onMouseReleased");

    // "projection" button (set projection types)
    std::string projType = CameraManager::instance().getProjectionTypeName();
    b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("CameraProjection Button");
    b->setText(projType.substr(0, 5) + ". Proj.");
    b->setCallback(&GuiWindowManager::callbackCameraProjectionMouseReleased, this, "onMouseReleased");

    // "command overlay" button (toggle visibility)
    b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("Command Overlay Button");
    b->setText("Command");
    b->setCallback(&GuiWindowManager::callbackCommandMouseReleased, this, "onMouseReleased");

    // "console" button (toggle visibility)
    b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("Console Button");
    b->setText("Console");
    b->setCallback(&GuiWindowManager::callbackConsoleMouseReleased, this, "onMouseReleased");
  }

  // creating taskbar
  {
    _taskbar = _guiManager->createWindow();
    _taskbar->setName("Taskbar");
    _taskbar->setText("Taskbar");
    _taskbar->setCloseable(false);
    _taskbar->setMovable(false);
    _taskbar->setResizeable(false);
    _taskbar->setBorderVisible(false);
    _taskbar->show();

    // "empty" text entry
    RBGui::ButtonWidget* b = static_cast<RBGui::ButtonWidget*>(_taskbar->createWidget("Button"));
    b->setName("<Empty>");
    b->setText("<Empty>");
    b->setVisible(false);
    b->setSink(false);
    b->setEnabled(false);
  }
}

void GuiWindowManager::registerWindow(GuiBaseWindow* w)
{
  _windowList.push_back(w);
  const char* name = w->getName().c_str();
  /* Logger::logDEBUG("GuiWindowManager::registerWindow(%s), in taskbar? %s",
     name, w->getPresentInTaskbar() ? "yes" : "no");
  */
  
  // create new button in the "taskbar"
  if (w->getPresentInTaskbar()) {
    RBGui::ButtonWidget* b = static_cast<RBGui::ButtonWidget*>(_taskbar->createWidget("Button"));
    b->setObject(w->getGUIWindow());
    b->setText(name);
    b->setCallback(&GuiWindowManager::callbackButtonMouseReleased, this, "onMouseReleased");
    _taskbarButtons.push_back(b);
    Mocha::Vector2 buttonSize(_taskbar->getClientRectangle().getSize());
    if (_taskbarButtons.size() > 0) {
      buttonSize.x /= _taskbarButtons.size();
    }
    Mocha::Vector2 buttonPosition(_taskbarButtons.size()*buttonSize.x, 0);
    b->setPosition(buttonPosition);
    b->setSize(buttonSize);
  }

  /// \note mafm: for some reason the program hangs if done in most
  /// places except here
  // provoke fake event to paint window initially
  windowResized(&Application::instance().getRenderWindow());
}

RBGui::Theme* GuiWindowManager::getDefaultTheme() const
{
  return RBGui::Core::Get().getThemeManager().getDefaultTheme();
}

const std::vector<GuiBaseWindow*>& GuiWindowManager::getWindowList() const
{
  return _windowList;
}

void GuiWindowManager::toggleWindowVisibilityAndFocus(const char* name)
{
  RBGui::Window* w = _guiManager->findWindow(name);
  if (w) {
    // toggle visibility
    if (w->getState() == RBGui::WINDOWSTATE_HIDDEN) {
      w->show();
      _guiManager->setFocused(w);
    } else {
      w->hide();
    }

    // update taskbar according with active windows
    updateTaskbar();
  } else {
    Logger::logERROR("'%s' window not found", name);
  }
}

void GuiWindowManager::windowResized(Ogre::RenderWindow* rw)
{
  //Logger::logDEBUG("GuiWindowManager::windowResized()");
  if (!_guiManager)
    return;
  _renderWindow = rw;

  // get size as float
  const float rwWidth = static_cast<float>(_renderWindow->getWidth());
  const float rwHeight = static_cast<float>(_renderWindow->getHeight());
  const float contentWidth = rwWidth;
  const float contentHeight = rwHeight - TASKBAR_HEIGHT - TOPBAR_HEIGHT;

  // topbar panel
  {
    _topbar->setPosition(Mocha::Vector2(0.0f, 0.0f));
    _topbar->setSize(Mocha::Vector2(rwWidth, TOPBAR_HEIGHT));

    const RBGui::WidgetList& children = _topbar->getRoot()->getChildren();

    Mocha::Vector2 buttonSize(_topbar->getClientRectangle().getSize());
    if (children.size() > 0)
      buttonSize.x /= children.size();

    for (size_t i = 0; i < children.size(); ++i) {
      RBGui::Widget& child = *(children[i].get());
      //Logger::logDEBUG("_topbar child: '%s':'%s'", child.getName().c_str(), child.getText().c_str());
      child.setPosition(Mocha::Vector2(buttonSize.x*i, 0.0f));
      child.setSize(buttonSize);
    }
  }

  // "taskbar" panel
  updateTaskbar();

  // propagate to all registered windows
  for (size_t i = 0; i < _windowList.size(); ++i) {
    GuiBaseWindow* w = _windowList[i];
    w->resize(0.0f, TOPBAR_HEIGHT, contentWidth, contentHeight);
  }
}

void GuiWindowManager::updateTaskbar()
{
  if (!_guiManager || !_renderWindow)
    return;

  // sizes
  const float rwWidth = static_cast<float>(_renderWindow->getWidth());
  const float rwHeight = static_cast<float>(_renderWindow->getHeight());
  _taskbar->setPosition(Mocha::Vector2(0.0f, rwHeight - TASKBAR_HEIGHT));
  _taskbar->setSize(Mocha::Vector2(rwWidth, TASKBAR_HEIGHT));

  // get visible buttons, according to their windows, and show/hide
  // them
  Mocha::Vector2 buttonSize(_taskbar->getClientRectangle().getSize());
  int visibleButtons = 0;
  for (size_t i = 0; i < _taskbarButtons.size(); ++i) {
    RBGui::ButtonWidget* b = _taskbarButtons[i];
    RBGui::Window* w = dynamic_cast<RBGui::Window*>(b->getObject());
    if (w->getState() == RBGui::WINDOWSTATE_NORMAL) {
      b->setVisible(true);
      ++visibleButtons;
    } else {
      b->setVisible(false);
    }
  }

  // set button sizes and positions
  if (visibleButtons > 0) {
    // hide "empty" button
    _taskbar->findWidget("<Empty>")->setVisible(false);

    // set dimensions and positions of active buttons
    buttonSize.x /= visibleButtons;
    for (size_t i = 0; i < _taskbarButtons.size(); ++i) {
      RBGui::ButtonWidget* b = _taskbarButtons[i];
      b->setPosition(Mocha::Vector2(buttonSize.x*i, 0.0f));
      b->setSize(buttonSize);
    }
  } else {
    //Logger::logDEBUG("Taskbar with no items...");
    RBGui::Widget* b = _taskbar->findWidget("<Empty>");
    b->setVisible(true);
    b->setSize(_taskbar->getSize());
  }
}

void GuiWindowManager::update(const ObserverEvent& event)
{
  try {
    // camera events
    {
      const CameraObserverEvent* e = dynamic_cast<const CameraObserverEvent*>(&event);
      RBGui::Widget* widget = 0;
      if (e) {
	switch (e->_actionId) {
	case CameraObserverEvent::MODE_CHANGED:
	  widget = _topbar->findWidget("CycleCamera Button");
	  if (widget) {
	    widget->setText(e->_content + " Mode");
	  } else {
	    throw "CycleCamera button not found";
	  }
	  break;
	case CameraObserverEvent::PROJECTION_CHANGED:
	  widget = _topbar->findWidget("CameraProjection Button");
	  if (widget) {
	    widget->setText(e->_content.substr(0, 5) + ". Proj.");
	  } else {
	    throw "CameraProjection button not found";
	  }
	  break;
	case CameraObserverEvent::UPDATED:
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
    Logger::logWARNING("GuiWindowManager: '%s' event: %s", event._className.c_str(), error);
  }
}

void GuiWindowManager::callbackQuitMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  Application::instance().quit();
}

void GuiWindowManager::callbackFullscreenMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  Application::instance().toggleFullscreen();
}

void GuiWindowManager::callbackControlCameraMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  const char* name = "Camera";
  toggleWindowVisibilityAndFocus(name);
}

void GuiWindowManager::callbackCycleCameraMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  CameraManager::instance().cycleCameraMode();
}

void GuiWindowManager::callbackCameraProjectionMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  bool toggle = !CameraManager::instance().isProjectionOrthogonal();
  CameraManager::instance().setProjectionOrthogonal(toggle);
}

void GuiWindowManager::callbackCommandMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  const char* name = "Command Overlay";
  toggleWindowVisibilityAndFocus(name);
}

void GuiWindowManager::callbackConsoleMouseReleased(RBGui::GuiElement& /* element */, const Mocha::ValueList& /* data */)
{
  const char* name = "Console";
  toggleWindowVisibilityAndFocus(name);
}

void GuiWindowManager::callbackButtonMouseReleased(RBGui::GuiElement& element, const Mocha::ValueList& /* data */)
{
  RBGui::ButtonWidget* activeButton = static_cast<RBGui::ButtonWidget*>(&element);
  //Logger::logDEBUG("button clicked: '%s'", activeButton->getText().c_str());
  for (size_t i = 0; i < _taskbarButtons.size(); ++i) {
    RBGui::ButtonWidget* button = _taskbarButtons[i];
    if (button == activeButton) {
      toggleWindowVisibilityAndFocus(activeButton->getText().c_str());
      updateTaskbar();
    } else {
      //activeButton->setEnabled(true);
    }
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
