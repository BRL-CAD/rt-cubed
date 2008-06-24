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


#include "GuiBaseWindow.h"

namespace RBGui {
  class TextEntryWidget;
  class TextWidget;
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
class GuiTaskbar : public GuiBaseWindow
{
public:
  /**
   * Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiTaskbar(RBGui::GuiManager& guiMgr);

  /** Default destructor */
  ~GuiTaskbar();

  /** @see GuiBaseWindow::resized */
  virtual void resize(float rwWidth, float rwHeight);

  /** Add a new window */
  void addWindow(const GuiBaseWindow* w);

private:
  /** Main Window (in the sense of the GUI) implemented by the class
   * which inherits this one */
  RBGui::Window* _mainWin;

  /** List of windows that are registered in the taskbar */
  std::vector<const GuiBaseWindow*> _windowList;

  /** List of windows buttons that are displayed in the taskbar */
  std::vector<RBGui::ButtonWidget*> _windowButtons;


  /** Callback for "MouseReleased" in the buttons */
  void callbackButtonMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
