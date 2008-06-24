/*                  G U I T A S K B A R . C X X
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

#include "GuiTaskbar.h"


/*******************************************************************************
 * GuiTaskbar
 ******************************************************************************/
GuiTaskbar::GuiTaskbar(RBGui::GuiManager& guiMgr) :
  GuiBaseWindow(guiMgr), _mainWin(0)
{
  // creating windows and widgets
  _mainWin = _guiMgr.createWindow();
  _mainWin->setText("Taskbar Window");
  _mainWin->setCloseable(false);
  _mainWin->setMovable(false);
  _mainWin->setResizeable(false);
  _mainWin->setBorderVisible(false);
  _mainWin->show();
  GuiBaseWindow::setMainWindow(_mainWin);

  addWindow(this);
  addWindow(this);
  addWindow(this);

  // setting callbacks for window/widget events within RBGui.

  // set initial size
  resize(Ogre::Root::getSingleton().getAutoCreatedWindow());
}

GuiTaskbar::~GuiTaskbar()
{
  delete _mainWin; _mainWin = 0;
}

void GuiTaskbar::resize(Ogre::RenderWindow* rw)
{
  unsigned int rwWidth = rw->getWidth();
  unsigned int rwHeight = rw->getHeight();

  const float height = 24.0f;

  _mainWin->setPosition(Mocha::Vector2(0, rwHeight-height));
  _mainWin->setSize(Mocha::Vector2(static_cast<float>(rwWidth), height));

  Mocha::Vector2 buttonSize(rwWidth/static_cast<float>(_windowButtons.size()), height);
  for (size_t i = 0; i < _windowButtons.size(); ++i) {
    RBGui::ButtonWidget* b = _windowButtons[i];
    b->setPosition(Mocha::Vector2(i*buttonSize.x, 0.0f));
    b->setSize(buttonSize);
  }
}

void GuiTaskbar::addWindow(const GuiBaseWindow* w)
{
  const char* name = w->getName().c_str();
  Logger::logDEBUG("GuiTaskbar::addWindow(%s)", name);
  _windowList.push_back(w);
  RBGui::ButtonWidget* b = static_cast<RBGui::ButtonWidget*>(_mainWin->createWidget("Button"));
  b->setText(name);
  b->setCallback(&GuiTaskbar::callbackButtonMouseReleased, this, "onMouseReleased");
  _windowButtons.push_back(b);
}

void GuiTaskbar::callbackButtonMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  Logger::logDEBUG("button clicked: '%s'", static_cast<RBGui::ButtonWidget&>(vElement).getText().c_str());
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
