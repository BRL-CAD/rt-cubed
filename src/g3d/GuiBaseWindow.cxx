/*                  G U I B A S E W I N D O W . C X X
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

#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreWindowEventUtilities.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/Window.h>

#include "Logger.h"

#include "GuiBaseWindow.h"


/**
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>

 * Internal class for [OGRE] Window Resized events, so the target
 * accomodates to the new size of the render window automatically.
 */
class WindowResizedListener : public Ogre::WindowEventListener
{
public:
  /**
   * Default constructor
   *
   * @param target The target that this listener relates to
   */
  WindowResizedListener(GuiBaseWindow& target) : _target(target) { }

  /** Method for Window Resized events */
  virtual void windowResized(Ogre::RenderWindow* rw)
  {
    Logger::logDEBUG("OGRE WindowResized event received, for window: '%s'",
		     _target.getName().c_str());
    _target.resize(rw);
  }

private:
  /** Link to the target that this listener applies */
  GuiBaseWindow& _target;
};


/*******************************************************************************
 * GuiBaseWindow
 ******************************************************************************/
GuiBaseWindow::GuiBaseWindow(RBGui::GuiManager& guiMgr) :
  _guiMgr(guiMgr), _mainWin(0), _windowResizedListener(0)
{
  // listener for [OGRE] window resized
  _windowResizedListener = new WindowResizedListener(*this);
  Ogre::WindowEventUtilities::addWindowEventListener(Ogre::Root::getSingleton().getAutoCreatedWindow(),
						     _windowResizedListener);
}

GuiBaseWindow::~GuiBaseWindow()
{
  Logger::logDEBUG("GuiBaseWindow::~GuiBaseWindow()");
  Ogre::WindowEventUtilities::removeWindowEventListener(Ogre::Root::getSingleton().getAutoCreatedWindow(),
							_windowResizedListener);
  delete _windowResizedListener; _windowResizedListener = 0;
}

void GuiBaseWindow::setMainWindow(RBGui::Window* w)
{
  _mainWin = w;
}


const std::string& GuiBaseWindow::getName() const
{
  return _mainWin->getText();
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
