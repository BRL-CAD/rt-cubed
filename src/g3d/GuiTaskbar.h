/*                    G U I T A S K B A R . H
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

/** @file GuiTaskbar.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Taskbar functionality for the application.
 */

#ifndef __G3D_GUITASKBAR_H__
#define __G3D_GUITASKBAR_H__


class WindowResizedListener;
namespace Ogre {
  class RenderWindow;
}
namespace RBGui {
  class GuiElement;
  class GuiManager;
  class TextEntryWidget;
  class TextWidget;
  class Window;
}


/**
 * @brief Implements Taskbar service for the application
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * The class implementing taskbar functionality for the application,
 * so we can bring opened windows to front, and similar kind of window
 * operations.
 */
class GuiTaskbar {
public:
  /**
   * Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiTaskbar(RBGui::GuiManager& guiMgr);

  /** Default destructor */
  ~GuiTaskbar();

  /** Resize */
  void resize(Ogre::RenderWindow* rw);

private:
  /** Link to the RBGui's GUI manager */
  RBGui::GuiManager& _guiMgr;

  /** Main window */
  RBGui::Window* _mainWin;
  /**
   * Panel of the console, to show text (information, commands
   * entered, etc)
   */
  RBGui::TextWidget* _consolePanel;

  /**
   * WindowResized listener, to get notified when the OGRE render
   * window is resized and act accordingly
   */
  WindowResizedListener* _windowResizedListener;
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
