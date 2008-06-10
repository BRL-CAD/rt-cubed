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

  void tick(float delta);

  void run();

  void quit();

private:
  Ogre::Root* _root;
  Ogre::SceneManager* _scene;
  Ogre::Camera* _camera;
  Ogre::Viewport* _viewport;
  Ogre::RenderWindow* _window;

  RBGui::Core* _guiCore;
  RBGui::GuiManager* _guiManager;

  OIS::Mouse* _mouse;
  OIS::Keyboard* _keyboard;
  OIS::InputManager* _inputManager;

  MouseListener* _mouseListener;
  KeyListener* _keyListener;

  bool _quit;


  void initialize();

  void setupInput();

  void createTestingWindows();

  void updateMouseWindowMetrics();

  void fileSelected(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

  void browserResized(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

  void attributeChanged(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

  void menuPicked(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
