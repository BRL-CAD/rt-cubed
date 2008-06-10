/*
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by the
 * U.S. Army Research Laboratory.
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

/** @file Application.h
 *
 * @brief
 *	Header of the Application class of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_APPLICATION_H__
#define __G3D_APPLICATION_H__


#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <RBGui/Core.h>
#include <RBGui/Widgets/ProgressWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

class MouseListener;
class KeyListener;

/** @brief Main class of the 3D Geometry Editor.
 *
 * This class implements the main application using OGRE render loop
 * and the GUI.
 */
class Application
{
public:
  /** Default constructor */
  Application();

  /** Default destructor */
  ~Application();

  void initialize();

  void tick(float vDelta);

  void run();

  void quit();

  friend class LostDeviceListener;
  friend class MouseListener;
  friend class KeyListener;

private:
  Mocha::RefPointer<RBGui::Core> _guiCore;

  Mocha::RefPointer<RBGui::GuiManager> _guiManager;

  MouseListener* _mouseListener;

  KeyListener* _keyListener;

  OIS::Mouse* _mouse;

  OIS::Keyboard* _keyboard;

  OIS::InputManager* _inputManager;

  Ogre::SceneManager* _scene;

  Ogre::RenderWindow* _window;

  Ogre::Viewport* _viewport;

  Ogre::Camera* _camera;

  Ogre::Root* _root;

  bool _quit;


  void addResourceLocations();

  void setupInput();

  void fileSelected(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

  void browserResized(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

  void attributeChanged(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

  void menuPicked(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

  void updateMouseWindowMetrics();
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
