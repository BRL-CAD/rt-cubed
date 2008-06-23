/*                    G U I B A S E W I N D O W . H
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

/** @file GuiBaseWindow.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief Base Window infrastructure.
 *
 * File containing necessary infrastructure for windows, with common
 * functionalities that are convenient for us, so all windows within
 * the 3D GUI should inherit from.
 */

#ifndef __G3D_GUIBASEWINDOW_H__
#define __G3D_GUIBASEWINDOW_H__


#include <string>

class WindowResizedListener;
namespace Ogre {
  class RenderWindow;
}
namespace RBGui {
  class GuiManager;
  class Window;
}


/**
 * @brief Base Window from which all other windows should inherit
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 */
class GuiBaseWindow {
public:
  /**
   * Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiBaseWindow(RBGui::GuiManager& guiMgr);

  /** Default destructor */
  virtual ~GuiBaseWindow();

  /** Get name */
  virtual const std::string& getName() const = 0;
  /** Resize application window when the window created by the 3D
   * engine is resized */
  virtual void resize(Ogre::RenderWindow* rw) = 0;

protected:
  /** Link to the RBGui's GUI manager */
  RBGui::GuiManager& _guiMgr;

private:
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
