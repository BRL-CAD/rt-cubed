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

#include "GuiWindowManager.h"

#include "Logger.h"
#include "Application.h"
#include "CameraManager.h"
#include "GuiBaseWindow.h"

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


/*******************************************************************************
 * GuiWindowManager
 ******************************************************************************/
GuiWindowManager* GuiWindowManager::INSTANCE = 0;

GuiWindowManager& GuiWindowManager::instance()
{
  if (!INSTANCE)
    INSTANCE = new GuiWindowManager();
  return *INSTANCE;
}

GuiWindowManager::GuiWindowManager() :
  _guiManager(0), _taskbar(0), _topbar(0)
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
  }
}

void GuiWindowManager::registerWindow(GuiBaseWindow* w)
{
  const char* name = w->getName().c_str();
  Logger::logDEBUG("GuiWindowManager::registerWindow(%s), in taskbar? %s",
		   name, w->getPresentInTaskbar() ? "yes" : "no");

//  if (w->getPresentInTaskbar()) {
    _windowList.push_back(w);

    Logger::logDEBUG("smee");

    // create new button in the "taskbar"
    RBGui::ButtonWidget* b = static_cast<RBGui::ButtonWidget*>(_taskbar->createWidget("Button"));
    b->setText(name);
    b->setCallback(&GuiWindowManager::callbackButtonMouseReleased, this, "onMouseReleased");
    _taskbarButtons.push_back(b);
//  }

  // set size initially -- have to recalculate everything due to
  // static panels and so on, better than duplicate code here
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
  } else {
    Logger::logERROR("'%s' window not found", name);
  }
}

void GuiWindowManager::windowResized(Ogre::RenderWindow* rw)
{
  Logger::logDEBUG("GuiWindowManager::windowResized()");
  if (!_guiManager)
    return;

  const float taskbarHeight = 16.0f;
  const float topbarHeight = 16.0f;

  // get size as float
  const float rwWidth = static_cast<float>(rw->getWidth());
  const float rwHeight = static_cast<float>(rw->getHeight());
  const float contentWidth = rwWidth;
  const float contentHeight = rwHeight - taskbarHeight - topbarHeight;

  // topbar panel
  {
    _topbar->setPosition(Mocha::Vector2(0.0f, 0.0f));
    _topbar->setSize(Mocha::Vector2(rwWidth, topbarHeight));

    const RBGui::WidgetList& children = _topbar->getRoot()->getChildren();

    Mocha::Vector2 buttonSize(_topbar->getClientRectangle().getSize());
    if (children.size() > 0)
      buttonSize.x /= children.size();

    for (size_t i = 0; i < children.size(); ++i) {
      /*
      Logger::logDEBUG("_topbar children: '%s':'%s'",
		       children[i]->getName().c_str(),
		       children[i]->getText().c_str());
      */

      children[i]->setPosition(Mocha::Vector2(buttonSize.x*i, 0.0f));
      children[i]->setSize(buttonSize);
    }
  }

  // "taskbar" panel
  {
    _taskbar->setPosition(Mocha::Vector2(0.0f, rwHeight - taskbarHeight));
    _taskbar->setSize(Mocha::Vector2(rwWidth, taskbarHeight));

    Mocha::Vector2 buttonSize(_taskbar->getClientRectangle().getSize());
    if (_taskbarButtons.size() > 0) {
      buttonSize.x /= _taskbarButtons.size();
      for (size_t i = 0; i < _taskbarButtons.size(); ++i) {
	RBGui::ButtonWidget* b = _taskbarButtons[i];
	b->setPosition(Mocha::Vector2(buttonSize.x*i, 0.0f));
	b->setSize(buttonSize);
      }
    } else {
      Logger::logDEBUG("Taskbar with no items...");
    }
  }

  // propagate to all registered windows
  for (size_t i = 0; i < _windowList.size(); ++i) {
    GuiBaseWindow* w = _windowList[i];
    w->resize(0.0f, topbarHeight, contentWidth, contentHeight);
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
	    widget->setText(e->_content + ". Mode");
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

void GuiWindowManager::callbackQuitMouseReleased(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& /* vData */)
{
  Application::instance().quit();
}

void GuiWindowManager::callbackFullscreenMouseReleased(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& /* vData */)
{
  Application::instance().toggleFullscreen();
}

void GuiWindowManager::callbackCycleCameraMouseReleased(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& /* vData */)
{
  CameraManager::instance().cycleCameraMode();
}

void GuiWindowManager::callbackCameraProjectionMouseReleased(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& /* vData */)
{
  bool toggle = !CameraManager::instance().isProjectionOrthogonal();
  CameraManager::instance().setProjectionOrthogonal(toggle);
}

void GuiWindowManager::callbackCommandMouseReleased(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& /* vData */)
{
  const char* name = "Command Overlay";
  toggleWindowVisibilityAndFocus(name);
}

void GuiWindowManager::callbackConsoleMouseReleased(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& /* vData */)
{
  const char* name = "Console";
  toggleWindowVisibilityAndFocus(name);
}

void GuiWindowManager::callbackButtonMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& /* vData */)
{
  RBGui::ButtonWidget* activeButton = static_cast<RBGui::ButtonWidget*>(&vElement);
  Logger::logDEBUG("button clicked: '%s'", activeButton->getText().c_str());
  for (size_t i = 0; i < _taskbarButtons.size(); ++i) {
    RBGui::ButtonWidget* button = _taskbarButtons[i];
    if (button == activeButton) {
      button->setEnabled(false);
    } else {
      button->setEnabled(true);
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
