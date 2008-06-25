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

#include <OIS/OISKeyboard.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreWindowEventUtilities.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/Window.h>
#include <RBGui/Widgets/ButtonWidget.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "Logger.h"
#include "Application.h"
#include "GuiBaseWindow.h"

#include "GuiWindowManager.h"


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
  Ogre::WindowEventUtilities::addWindowEventListener(Ogre::Root::getSingleton().getAutoCreatedWindow(),
						     this);
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

    RBGui::WidgetList children = _topbar->getRoot()->getChildren();

    Mocha::Vector2 buttonSize(_topbar->getClientRectangle().getSize());
    buttonSize.x /= static_cast<float>(children.size());

    for (size_t i = 0; i < children.size(); ++i) {
      Logger::logDEBUG("_topbar children: '%s':'%s'",
		       children[i]->getName().c_str(),
		       children[i]->getText().c_str());

      children[i]->setPosition(Mocha::Vector2(0.0f, 0.0f));
      children[i]->setSize(_topbar->getClientRectangle().getSize());
    }
  }

  // "taskbar" panel
  {
    _taskbar->setPosition(Mocha::Vector2(0.0f, rwHeight - taskbarHeight));
    _taskbar->setSize(Mocha::Vector2(rwWidth, taskbarHeight));

    Mocha::Vector2 buttonSize(_taskbar->getClientRectangle().getSize());
    buttonSize.x /= static_cast<float>(_windowButtons.size());
    for (size_t i = 0; i < _windowButtons.size(); ++i) {
      RBGui::ButtonWidget* b = _windowButtons[i];
      b->setPosition(Mocha::Vector2(i*buttonSize.x, 0.0f));
      b->setSize(buttonSize);
    }
  }

  // propagate to all registered windows
  for (size_t i = 0; i < _windowList.size(); ++i) {
    GuiBaseWindow* w = _windowList[i];
    w->resize(0.0f, topbarHeight, contentWidth, contentHeight);
  }
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

    // create new button in the "topbar"
    RBGui::ButtonWidget* b = static_cast<RBGui::ButtonWidget*>(_topbar->createWidget("Button"));
    b->setName("Fullscreen Button");
    b->setText("Fullscreen");
    b->setCallback(&GuiWindowManager::callbackFullscreenMouseReleased, this, "onMouseReleased");
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
  Logger::logDEBUG("GuiWindowManager::registerWindow(%s)", name);
  _windowList.push_back(w);

  // create new button in the "taskbar"
  RBGui::ButtonWidget* b = static_cast<RBGui::ButtonWidget*>(_taskbar->createWidget("Button"));
  b->setText(name);
  b->setCallback(&GuiWindowManager::callbackButtonMouseReleased, this, "onMouseReleased");
  _windowButtons.push_back(b);

  // set size initially -- have to recalculate everything due to
  // static panels and so on, better than duplicate code here
  windowResized(Ogre::Root::getSingleton().getAutoCreatedWindow());
}

const std::vector<GuiBaseWindow*>& GuiWindowManager::getWindowList() const
{
  return _windowList;
}

void GuiWindowManager::callbackFullscreenMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  Application::instance().toggleFullscreen();
}

void GuiWindowManager::callbackButtonMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  RBGui::ButtonWidget* activeButton = static_cast<RBGui::ButtonWidget*>(&vElement);
  Logger::logDEBUG("button clicked: '%s'", activeButton->getText().c_str());
  for (size_t i = 0; i < _windowButtons.size(); ++i) {
    RBGui::ButtonWidget* button = _windowButtons[i];
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
