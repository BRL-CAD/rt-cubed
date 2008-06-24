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
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "Logger.h"
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
  _guiManager(0)
{
  Ogre::WindowEventUtilities::addWindowEventListener(Ogre::Root::getSingleton().getAutoCreatedWindow(),
						     this);
}

GuiWindowManager::~GuiWindowManager()
{
}

void GuiWindowManager::windowResized(Ogre::RenderWindow* rw)
{
  Logger::logDEBUG("GuiWindowManager::windowResized()");

  // get size as float
  float rwWidth = static_cast<float>(rw->getWidth());
  float rwHeight = static_cast<float>(rw->getHeight());

  // propagate to all registered windows
  for (size_t i = 0; i < _windowList.size(); ++i) {
    GuiBaseWindow* w = _windowList[i];
    w->resize(rwWidth, rwHeight);
  }
}

void GuiWindowManager::setGuiManager(RBGui::GuiManager* guiManager)
{
  _guiManager = guiManager;
}

void GuiWindowManager::registerWindow(GuiBaseWindow* w)
{
  const char* name = w->getName().c_str();
  Logger::logDEBUG("GuiWindowManager::registerWindow(%s)", name);
  _windowList.push_back(w);

  // set size initially
  const Ogre::RenderWindow* rw = Ogre::Root::getSingleton().getAutoCreatedWindow();
  float rwWidth = static_cast<float>(rw->getWidth());
  float rwHeight = static_cast<float>(rw->getHeight());
  w->resize(rwWidth, rwHeight);
}

const std::vector<GuiBaseWindow*>& GuiWindowManager::getWindowList() const
{
  return _windowList;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
