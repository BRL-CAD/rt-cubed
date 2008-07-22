/*              G U I W I N D O W M A N A G E R . H
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

/** @file GuiWindowManager.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header of the GuiWindowManager class of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_GUIWINDOWMANAGER_H__
#define __G3D_GUIWINDOWMANAGER_H__


#include "Observer.h"

#include <Mocha/Value.h>
#include <OGRE/OgreWindowEventUtilities.h>

#include <vector>

class GuiBaseWindow;
namespace RBGui {
  class ButtonWidget;
  class GuiElement;
  class GuiManager;
  class Window;
}


/**
 * @brief GUI Window Manager class of the 3D Geometry Editor.
 *
 * This class implements the Window Manager for the application.  It
 * manages high-level positioning of windows and panels (tiled, etc),
 * registering available windows, etc.
 */
class GuiWindowManager : public Ogre::WindowEventListener, public Observer
{
public:
  /** Singleton, access to the manager */
  static GuiWindowManager& instance();

  /** Register window */
  void registerWindow(GuiBaseWindow* w);
  /** Get list of registered windows */
  const std::vector<GuiBaseWindow*>& getWindowList() const;

  /** Set GUI manager */
  void setGuiManager(RBGui::GuiManager* guiManager);

  /** @see Ogre::WindowEventListener::windowResized */
  virtual void windowResized(Ogre::RenderWindow* rw);

  /** @see Observer::update */
  virtual void update(const ObserverEvent& event);

private:
  /** Singleton instance */
  static GuiWindowManager* INSTANCE;

  /** Main Window (in the sense of the GUI) implemented by the class
   * which inherits this one */
  RBGui::GuiManager* _guiManager;
  /** "Taskbar" panel window */
  RBGui::Window* _taskbar;
  /** Top panel window */
  RBGui::Window* _topbar;

  /** List of windows that are registered in the taskbar */
  std::vector<GuiBaseWindow*> _windowList;
  /** List of windows buttons that are displayed in the panel */
  std::vector<RBGui::ButtonWidget*> _taskbarButtons;


  /** Default constructor */
  GuiWindowManager();

  /** Toggle Window visibility and set to focused when visible */
  void toggleWindowVisibilityAndFocus(const char* name);

  /** Callback for "MouseReleased" in the Quit button */
  void callbackQuitMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "MouseReleased" in the Fullscreen button */
  void callbackFullscreenMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "MouseReleased" in the CycleCamera button */
  void callbackCycleCameraMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "MouseReleased" in the CommandOverlay button */
  void callbackCommandMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "MouseReleased" in the Console button */
  void callbackConsoleMouseReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "MouseReleased" in the taskbar buttons */
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
