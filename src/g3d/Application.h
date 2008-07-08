/*                  A P P L I C A T I O N . H
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
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header of the Application class of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_APPLICATION_H__
#define __G3D_APPLICATION_H__


#include <vector>
#include <Mocha/Value.h>
#include <OGRE/OgreCommon.h>

class MouseListener;
class KeyListener;
class LostDeviceListener;
class GuiBaseWindow;
namespace Ogre {
  class Camera;
  class RenderWindow;
  class Root;
  class SceneManager;
  class Viewport;
}
namespace OIS {
  class InputManager;
  class Keyboard;
  class Mouse;
}
namespace Mocha {
}
namespace RBGui {
  class Core;
  class GuiElement;
  class GuiManager;
  class OgreRenderQueueListener;
}


/** @brief Main class of the 3D Geometry Editor.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * This class implements the main application using OGRE render loop
 * and the GUI.
 */
class Application
{
public:
  /** Singleton, access to the manager */
  static Application& instance();

  /** Main application loop -- will quit only shortly thereafter
   * calling to that method */
  void run();
  /** Tell application to stop main loop */
  void quit();

  /** Check whether application is set to fullscreen or not */
  bool isFullscreen() const;
  /** Tell application to set fullscreen or not */
  void setFullscreen(bool value);
  /** Toggle fullscreen mode */
  void toggleFullscreen();
  /** Tell the polygon mode to use */
  void setPolygonMode(Ogre::PolygonMode polygonMode);
  /** Get Ogre::Root */
  Ogre::Root& getRoot() const;
  /** Get Ogre::RenderWindow */
  Ogre::RenderWindow& getRenderWindow() const;

private:
  /** Singleton instance */
  static Application* INSTANCE;

  /** Pointer to OGRE "application" */
  Ogre::Root* _root;
  /** Pointer to SceneManager */
  Ogre::SceneManager* _scene;
  /** Pointer to the camera to view the scene */
  Ogre::Camera* _camera;
  /** Pointer to the viewport */
  Ogre::Viewport* _viewport;
  /** Pointer to the window where all our application is rendered, in
   * the host OS */
  Ogre::RenderWindow* _renderWindow;

  /** Pointer to the mouse of the input libraries */
  OIS::Mouse* _mouse;
  /** Pointer to the keyboard of the input libraries */
  OIS::Keyboard* _keyboard;
  /** Pointer to the manager of the input libraries */
  OIS::InputManager* _inputManager;

  /** Pointer to the "application" of the GUI */
  RBGui::Core* _guiCore;
  /** Pointer to the manager of the GUI */
  RBGui::GuiManager* _guiManager;

  /** Listener for input/rendering events */
  MouseListener* _mouseListener;
  /** Listener for input/rendering events */
  KeyListener* _keyListener;
  /** Listener for input/rendering events */
  LostDeviceListener* _lostDeviceListener;
  /** Listener for input/rendering events */
  RBGui::OgreRenderQueueListener* _rbguiRenderListener;

  /** Flag to control when to stop run()ning */
  bool _quit;

  /** List of windows that we've created -- to delete them */
  std::vector<GuiBaseWindow*> _windowList;


  /** Default constructor */
  Application();
  /** Initialize resources, create windows, etc */
  void initialize();
  /** Finalize -- free resources and the like (destructor not usable
   * with Singletons) */
  void finalize();
  /** New discrete step */
  void tick(float delta);


  /*****************************************************************************
   * TESTING CODE AHEAD
   ****************************************************************************/
  void createTestingWindows();

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
