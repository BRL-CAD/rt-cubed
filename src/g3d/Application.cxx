/*                  A P P L I C A T I O N . C X X
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

/** @file Application.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the Application class of 3D Geometry Editor
 *	(g3d), along with some internal classes.
 */

#include <Mocha/DataSection.h>
#include <Mocha/Stream.h>
#include <Mocha/Timer.h>

#include <RBGui/Core.h>
#include <RBGui/BrushCursorManager.h>
#include <RBGui/SimpleWindowFader.h>
#include <RBGui/OgreSupport/OgreBrush.h>
#include <RBGui/OgreSupport/OgreRenderQueueListener.h>
#include <RBGui/OgreSupport/OgreResourceManager.h>
#include <RBGui/OgreSupport/OgreTextureManager.h>
#include <RBGui/Widgets/AttributeEditWidget.h>
#include <RBGui/Widgets/CheckWidget.h>
#include <RBGui/Widgets/ColorSelectWidget.h>
#include <RBGui/Widgets/DirectoryListWidget.h>
#include <RBGui/Widgets/DropListWidget.h>
#include <RBGui/Widgets/DropSplineWidget.h>
#include <RBGui/Widgets/MenuWidget.h>
#include <RBGui/Widgets/ImageWidget.h>
#include <RBGui/Widgets/OptionWidget.h>
#include <RBGui/Widgets/ProgressWidget.h>
#include <RBGui/Widgets/ScrollWidget.h>
#include <RBGui/Widgets/TextWidget.h>

#include <OGRE/Ogre.h>
#include <OGRE/OgreSceneNode.h>
#include <OIS/OIS.h>

#if defined(WIN32)
#include <RBGui/Win32PlatformManager.h>
#include <RBGui/Win32CursorManager.h>
#elif defined(POSIX)
#include <RBGui/PosixPlatformManager.h>
#elif defined(APPLE)
#include <RBGui/MacOSPlatformManager.h>
#else
#error "No platform manager available"
#endif

#include "Logger.h"
#include "GuiBaseWindow.h"
#include "GuiCommandOverlay.h"
#include "GuiConsole.h"
#include "GuiWindowManager.h"

#include "Application.h"

using namespace std;


/** @brief Internal class for writing files.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class CustomStream : public Mocha::Stream
{
public:
  /** Default constructor
   *
   * @param name Name of the file
   */
  CustomStream(const string& name) { _file = fopen(name.c_str(), "wb+"); }

  /** Default destructor */
  virtual ~CustomStream() { fclose(_file); }

  /** Write given data to the stream */
  virtual size_t writeData(const void* data, size_t size) { return fwrite(data, 1, size, _file); }

  /** Read data from stream \note (NOT IMPLEMENTED) */
  virtual size_t readData(void* /* data */, size_t /* size */) const { return 0; }

  /** Seek position in the stream \note (NOT IMPLEMENTED) */
  virtual void seek(size_t /* position */) const { }

  /** Get size of the stream \note (NOT IMPLEMENTED) */
  virtual size_t getSize() const { return 0; }

  /** Get the position being used for the stream */
  virtual size_t getPosition() const { return ftell(_file); }

  /** Check whether we're at the end of the stream */
  virtual bool getEndOfStream() const { return feof(_file); }

private:
  /** Low level file pointer */
  FILE* _file;
};


/** @brief
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Internal class for mouse related updates from the 3D engine, to
 * pass them to the GUI (and move windows, be able to click on
 * buttons, etc).
 */
class MouseListener : public OIS::MouseListener
{
public:
  /** Default constructor
   *
   * @param app The application that this listener is related to
   * @param guiMgr The GUI Manager that this listener is related to
   */
  MouseListener(Application& app, RBGui::GuiManager& guiMgr) :
    _app(app), _guiMgr(guiMgr), _prevPos(Mocha::Vector2(0.0f, 0.0f))
    { }

  /** Method for Mouse Moved events */
  virtual bool mouseMoved(const OIS::MouseEvent& event)
    {
      // Get absolute position
      Mocha::Vector2 absPos = Mocha::Vector2(static_cast<float>(event.state.X.abs), 
					     static_cast<float>(event.state.Y.abs));

      // Inject mouse scroll event
      if (event.state.Z.rel != 0) {
	_guiMgr.injectMouseScrolled(static_cast<float>(event.state.Z.rel / 120.0f),
				    absPos);
      }

      // Calculate relative position in pixels
      Mocha::Vector2 relPos = absPos - _prevPos;
      _prevPos = absPos;

      // Send event to GUI
      _guiMgr.injectMouseMotion(relPos, absPos);
      return true;
    }
	
  /** Method for Mouse Pressed events */
  virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id)
    {
      _guiMgr.injectMousePressed(static_cast<RBGui::MouseButtonID>(id),
				 Mocha::Vector2(static_cast<float>(event.state.X.abs),
						static_cast<float>(event.state.Y.abs)));
      return true;
    }

  /** Method for Mouse Released events */
  virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id)
    {
      _guiMgr.injectMouseReleased(static_cast<RBGui::MouseButtonID>(id),
				  Mocha::Vector2(static_cast<float>(event.state.X.abs),
						 static_cast<float>(event.state.Y.abs)));
      return true;
    }

private:
  /** Link to the Application that this listener applies */
  Application& _app;
  /** Link to the GUI manager */
  RBGui::GuiManager& _guiMgr;
  /** Variable to save the state of the previous position of the
   * mouse */
  Mocha::Vector2 _prevPos;
};


/** @brief
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Internal class for keyboard related updates from the 3D engine, to
 * pass them to the GUI (and write in text areas, etc).
 */
class KeyListener : public OIS::KeyListener
{
public:
  /** Default constructor
   *
   * @param app The application that this listener is related to
   * @param guiMgr The GUI Manager that this listener is related to
   */
  KeyListener(Application& app, RBGui::GuiManager& guiMgr) :
    _app(app), _guiMgr(guiMgr)
    { }

  /** Method for Key Pressed events */
  virtual bool keyPressed(const OIS::KeyEvent& event)
    {
      // ESC key to quit -- hack for convenience while developing
      if (event.key == OIS::KC_ESCAPE) {
	_app.quit();
	return true;
      } else if (event.key == OIS::KC_F12) {
	// toggle fullscreen
	_app.toggleFullscreen();
	return true;
      } else if (event.key == OIS::KC_F5) {
	// zoom in
	_app.zoomIn();
	return true;
      } else if (event.key == OIS::KC_F6) {
	// zoom out
	_app.zoomOut();
	return true;
      } else if (event.key == OIS::KC_F7) {
	// turn around, left
	_app.turnAround(0.1);
	return true;
      } else if (event.key == OIS::KC_F8) {
	// turn around, right
	_app.turnAround(-0.1);
	return true;
      }

      // No need to translate key IDs because they are the same as OIS
      _guiMgr.injectKeyPressed(static_cast<RBGui::KeyID>(event.key));
      return true;
    }
	
  /** Method for Key released events */
  virtual bool keyReleased(const OIS::KeyEvent& event)
    {
      // No need to translate key IDs because they are the same as OIS
      _guiMgr.injectKeyReleased(static_cast<RBGui::KeyID>(event.key));
      return true;
    }

private:
  /** Link to the Application that this listener applies */
  Application& _app;
  /** Link to the GUI manager */
  RBGui::GuiManager& _guiMgr;
};


/** @brief
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * Internal class for the event "DeviceLost" from the 3D engine, to
 * pass them to the GUI.
 */
class LostDeviceListener : public Ogre::RenderSystem::Listener 
{
public:
  /** Method for any event */
  virtual void eventOccurred(const Ogre::String& eventName,
			     const Ogre::NameValuePairList* /* parameters */)
    {
      // Redraw the GUI if the device has been lost
      if (eventName == "DeviceLost") {
	Logger::logWARNING("OGRE lost the device, redrawing");
	RBGui::Core::Get().invalidate();
      }
    }
};


/*******************************************************************************
 * Application
 ******************************************************************************/
Application* Application::INSTANCE = 0;

Application& Application::instance()
{
  if (!INSTANCE)
    INSTANCE = new Application();
  return *INSTANCE;
}

Application::Application() :
  _root(0), _scene(0), _camera(0), _viewport(0), _renderWindow(0),
  _mouse(0), _keyboard(0), _inputManager(0),
  _guiCore(0), _guiManager(0),
  _mouseListener(0), _keyListener(0), _lostDeviceListener(0), _rbguiRenderListener(0),
  _quit(false)
{
}

void Application::initialize()
{
  // Try to initialize OGRE core
  _root = new Ogre::Root(DATA_DIR "ogreplugins.cfg");
  if (_root->restoreConfig() || _root->showConfigDialog()) {
    _renderWindow = _root->initialise(true, "BRL-CAD 3D Geometry Editor (g3d)");
  }
  if (!_renderWindow) {
    Logger::logFATAL("Unable to initialize OGRE");
    exit(EXIT_FAILURE);
  }

  // Setup resource locations
  {
    Ogre::ConfigFile config;
    config.load(DATA_DIR "resources.cfg");

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = config.getSectionIterator();
    while (seci.hasMoreElements()) {
      const Ogre::String& secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
      for (Ogre::ConfigFile::SettingsMultiMap::iterator i = settings->begin();
	   i != settings->end(); ++i) {
	const Ogre::String& typeName = i->first;
	const Ogre::String& archName = i->second;

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName,
								       typeName,
								       secName);
      }
    }

    // Initialize resource groups
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  }

  // Create scene, camera, viewport
  _scene = _root->createSceneManager("DefaultSceneManager", "g3d SceneManager");
  _camera = _scene->createCamera("g3d Camera");
  _camera->setPosition(0, 0, 10);
  _camera->lookAt(0, 0, 0);
  _viewport = _renderWindow->addViewport(_camera);
  _viewport->setBackgroundColour(Ogre::ColourValue(0.6f, 0.6f, 0.6f, 1.0f));
  _scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
  Ogre::Light* l = _scene->createLight("MainLight");
  l->setPosition(0, 10, 0);
  l->setDiffuseColour(Ogre::ColourValue(1.0, 0.5, 0.0));

  // Initialize the GUI. This adds all of the default widget factories
  RBGui::Initialize();

  // Choose the platform and cursor manager to use
  Mocha::RefPointer<RBGui::PlatformManager> platformManager;
  Mocha::RefPointer<RBGui::CursorManager> cursorManager;

#if defined(WIN32)
  platformManager = new RBGui::Win32PlatformManager();
//  cursorManager = new RBGui::Win32CursorManager();
#elif defined(POSIX)
  platformManager = new RBGui::PosixPlatformManager();
#elif defined(APPLE)
  platformManager = new RBGui::MacOSPlatformManager();
#endif

  // Create the GUI manager and set the default theme
  _guiCore = new RBGui::Core(new RBGui::OgreTextureManager(),
			     platformManager,
			     new RBGui::OgreResourceManager());
  _guiCore->getThemeManager().setDefaultTheme("brlcad.theme");
  _guiManager = _guiCore->createGui("g3d GUI", new RBGui::OgreBrush(_scene, _viewport));

  // The following code can be used to setup a custom cursor
  Mocha::RefPointer<RBGui::BrushCursorManager> bcursorManager = new RBGui::BrushCursorManager();
  bcursorManager->setCursorType(RBGui::CURSOR_TEXT, "cursor_text.png",
				Mocha::Vector2(3.0f, 8.0f), RBGui::BRUSHBLEND_INVERT);
  bcursorManager->setCursorType(RBGui::CURSOR_RESIZE, "cursor_resize.png",
				Mocha::Vector2(8.0f, 8.0f));
  bcursorManager->setCursorType(RBGui::CURSOR_HAND, "cursor_hand.png",
				Mocha::Vector2(8.0f, 8.0f));
  bcursorManager->setCursorType(RBGui::CURSOR_DEFAULT, "cursor.png");


  // Set the default window animator and fader for all created windows
  _guiManager->setDefaultWindowAnimator("Wobble");
  _guiManager->setDefaultWindowFader("Simple");

  // Setup all the input stuff
  {
    size_t data;
    _renderWindow->getCustomAttribute("WINDOW", &data);

    ostringstream windowString;
    windowString << data;

    OIS::ParamList paramList;
    paramList.insert(make_pair(string("WINDOW"), windowString.str()));
#if defined(WIN32)
    paramList.insert(make_pair(string("w32_mouse"), string("DISCL_FOREGROUND")));
    paramList.insert(make_pair(string("w32_mouse"), string("DISCL_NONEXCLUSIVE")));
    paramList.insert(make_pair(string("w32_keyboard"), string("DISCL_FOREGROUND")));
    paramList.insert(make_pair(string("w32_keyboard"), string("DISCL_NONEXCLUSIVE")));
#else
    paramList.insert(make_pair(string("XAutoRepeatOn"), string("true")));
    paramList.insert(make_pair(string("x11_keyboard_grab"), string("false")));
    paramList.insert(make_pair(string("x11_mouse_grab"), string("false")));
#endif

    // Create input object using parameter list, then keyboard and mouse
    _inputManager = OIS::InputManager::createInputSystem(paramList);
    _mouseListener = new MouseListener(*this, *_guiManager);
    _mouse = static_cast<OIS::Mouse*>(_inputManager->createInputObject(OIS::OISMouse, true));
    _mouse->setEventCallback(_mouseListener);
    _keyListener = new KeyListener(*this, *_guiManager);
    _keyboard = static_cast<OIS::Keyboard*>(_inputManager->createInputObject(OIS::OISKeyboard, true));
    _keyboard->setEventCallback(_keyListener);
  }

  // Set the cursor manager to use -- after setting mouse and so on
  _guiManager->setCursorManager(bcursorManager);

  // Add a render queue listener to draw the GUI
  _rbguiRenderListener = new RBGui::OgreRenderQueueListener(*_guiManager);
  _scene->addRenderQueueListener(_rbguiRenderListener);

  // Create lost device listener
  _lostDeviceListener = new LostDeviceListener();
  _root->getRenderSystem()->addListener(_lostDeviceListener);

  /// \todo mafm: not destroyed, unless RBGui does it in the end --
  /// it's not harmful anyway, the console it's supposed to be active
  /// always
  GuiWindowManager::instance().setGuiManager(_guiManager);
  _windowList.push_back(new GuiConsole(*_guiManager));
  _windowList.push_back(new GuiCommandOverlay(*_guiManager));

  //createTestingWindows();
}

void Application::finalize()
{
  Logger::logINFO("Application being destroyed...");

  // Destroy OIS
  Logger::logINFO("Freeing OIS resources");
  if (_inputManager) {
    if (_mouse)
      _inputManager->destroyInputObject(_mouse);
    if (_keyboard)
      _inputManager->destroyInputObject(_keyboard);
    _inputManager->destroyInputSystem(_inputManager);
  }

  // Destroy input listeners
  Logger::logINFO("Freeing input listeners");
  delete _mouseListener; _mouseListener = 0;
  delete _keyListener; _keyListener = 0;
  delete _lostDeviceListener; _lostDeviceListener = 0;

  /// \todo mafm: segfaulting and thus commented out at the moment,
  /// look more closely later

  // Release GUI resources
  Logger::logINFO("Freeing RBGui resources");
  delete _rbguiRenderListener; _rbguiRenderListener = 0;
  //delete _guiCore; _guiCore = 0;
  //delete _guiManager; _guiManager = 0;
  Logger::logINFO(" - clearing windows");
  // _guiManager->clear();
  Logger::logINFO(" - removing the rest of the GUI");
  // _guiCore->destroyGui("g3d GUI");
  while (_windowList.size() > 0) {
    // delete _windowList.back();
    _windowList.pop_back();
  }

  // Shutdown OGRE
  Logger::logINFO("Freeing OGRE resources");
  Logger::logINFO(" - renderWindow");
  _renderWindow->removeAllViewports();
  _renderWindow->destroy();
  Logger::logINFO(" - root");
  delete _root; _root = 0;
  /*
  Logger::logINFO(" - scene");
  delete _scene; _scene = 0;
  Logger::logINFO(" - camera");
  delete _camera; _camera = 0;
  Logger::logINFO(" - renderWindow");
  _renderWindow->removeAllViewports();
  _renderWindow->destroy();
  delete _renderWindow; _renderWindow = 0;
  Logger::logINFO(" - viewport");
  delete _viewport; _viewport = 0;
  Logger::logINFO(" - root");
  delete _root; _root = 0;
  */

  Logger::logINFO("Application stopped.");
}

void Application::tick(float delta)
{
  // If window was closed, we need to exit
  if (_renderWindow->isClosed()) {
    quit();
    return;
  }

  // Pump message events
  Ogre::WindowEventUtilities::messagePump();

  // Make sure mouse region is up to date
  _mouse->getMouseState().width = static_cast<int>(_renderWindow->getWidth());
  _mouse->getMouseState().height = static_cast<int>(_renderWindow->getHeight());

  // Capture mouse and keyboard state
  if (_mouse) {
    _mouse->capture();
  }
  if (_keyboard) {
    _keyboard->capture();
  }

  // Sleep for a bit if windows is not visible...
  if (_renderWindow->isVisible()) {
    // Tick the gui manager
    if (_guiManager) {
      _guiManager->tick(delta);
    }

    // Tell OGRE to render a frame. The GUI will get drawn as part of
    // the OGRE render queue
    if (_root) {
      _root->renderOneFrame();
    }
  } else {
    usleep(100*1000); // in microseconds
  }
}

void Application::run()
{
#if defined(WIN32)
  // HACK!
  // This is required on Windows XP because of a bug that causes
  // timing to be wrong when more than one CPU is available.
  // This issue has been fixed in Vista.

  HANDLE id = GetCurrentThread();
  DWORD pmask;
  DWORD psysmask;
  GetProcessAffinityMask(id, &pmask, &psysmask);
  DWORD res = SetThreadAffinityMask(id, 1);
#endif

  initialize();

  // Run the main loop
  Mocha::Timer timer;
  while (!_quit) {
    tick(static_cast<float>(timer.getDeltaSeconds()));
  }

  finalize();
}

void Application::quit()
{
  _quit = true;
}

bool Application::isFullscreen() const
{
  return _renderWindow->isFullScreen();
}

void Application::setFullscreen(bool value)
{
  /// \note mafm: it doesn't work smoothly when the resolution is low
  /// (say, 640x480) and the screen is of moderately high resolution
  /// (1280x960).  Maybe it happens the same with all non-native
  /// fullscreen modes?
  _renderWindow->setFullscreen(value,
			       _renderWindow->getWidth(),
			       _renderWindow->getHeight());
}

void Application::toggleFullscreen()
{
  setFullscreen(!isFullscreen());
}

void Application::setPolygonMode(Ogre::PolygonMode polygonMode)
{
  if (_camera) {
    Logger::logINFO("Changed camera polygon mode: %d", static_cast<int>(polygonMode));
    _camera->setPolygonMode(polygonMode);
  } else {
    Logger::logWARNING("Tried to changed polygon mode but camera is null");
  }
}

void Application::addGeometry(const std::string& name, const std::string& mesh)
{
  if (_scene) {
    Logger::logINFO("Adding geometry to the scene: '%s' of mesh '%s'",
		    name.c_str(), mesh.c_str());
    Ogre::Entity* e = _scene->createEntity(name, mesh);
    _scene->getRootSceneNode()->createChildSceneNode()->attachObject(e);
  } else {
    Logger::logWARNING("Tried to add geometry polygon mode but scene manager is null");
  }
}

void Application::zoomIn()
{
  if (_camera) {
    Ogre::Vector3 pos = _camera->getPosition() / 1.25f;
    Logger::logINFO("Zooming in camera (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);
    _camera->setPosition(pos);
  } else {
    Logger::logWARNING("Tried to zoom but camera is null");
  }
}

void Application::zoomOut()
{
  if (_camera) {
    Ogre::Vector3 pos = _camera->getPosition() * 1.25f;
    Logger::logINFO("Zooming out camera: (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);
    _camera->setPosition(pos);
  } else {
    Logger::logWARNING("Tried to zoom but camera is null");
  }
}

void Application::turnAround(float radians)
{
  if (_camera) {
    Ogre::Vector3 pos = _camera->getPosition();
    pos.x = pos.x*cos(radians) - pos.z*sin(radians);
    pos.z = pos.z*cos(radians) + pos.x*sin(radians);
    Logger::logINFO("Turning %s camera (%0.1f, %0.1f, %0.1f)", 
		    radians >= 0.0f ? "left" : "right",
		    pos.x, pos.y, pos.z);
    _camera->setPosition(pos);
    _camera->lookAt(0, 0, 0);
  } else {
    Logger::logWARNING("Tried to turn but camera is null");
  }
}

void Application::turnAroundLeft(float radians)
{
  if (_camera) {
    Ogre::Vector3 pos = _camera->getPosition();
    float radius = sqrt(pos.x*pos.x + pos.z*pos.z);
    pos.x = pos.x*cos(radians) - pos.z*sin(radians);
    pos.z = pos.z*cos(radians) + pos.x*sin(radians);
    Logger::logINFO("Turning left camera (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);
    _camera->setPosition(pos);
    _camera->lookAt(0, 0, 0);
  } else {
    Logger::logWARNING("Tried to turn but camera is null");
  }
}

void Application::turnAroundRight(float radians)
{
  if (_camera) {
    Ogre::Vector3 pos = _camera->getPosition();
    float radius = sqrt(pos.x*pos.x + pos.z*pos.z);
    pos.x = pos.x*cos(radians) - pos.z*sin(radians);
    pos.z = pos.z*cos(radians) + pos.x*sin(radians);
    Logger::logINFO("Turning right camera (%0.1f, %0.1f, %0.1f)", pos.x, pos.y, pos.z);
    _camera->setPosition(pos);
    _camera->lookAt(0, 0, 0);
  } else {
    Logger::logWARNING("Tried to turn but camera is null");
  }
}

Ogre::Root& Application::getRoot() const
{
  return *_root;
}

Ogre::RenderWindow& Application::getRenderWindow() const
{
  return *_renderWindow;
}


/*-----------------------------------------------------------------------------
 * Testing code ahead...
 *----------------------------------------------------------------------------*/
void Application::createTestingWindows()
{
  // Setup a test window
  Mocha::RefPointer<RBGui::Window> win = _guiManager->createWindow();
  win->setPosition(Mocha::Vector2(64.0f, 64.0f));
  win->setSize(Mocha::Vector2(300.0f, 300.0f));
  win->setText("Wobbly Window");
  win->show();

  Mocha::RefPointer<RBGui::TextWidget> text = static_cast<RBGui::TextWidget*>(win->createWidget("Text"));
  text->setPosition(Mocha::Vector2(16.0f, 16.0f));
  text->setSize(Mocha::Vector2(256.0f, 20.0f));
  text->setText("Hello, world.");

  Mocha::RefPointer<RBGui::DropSplineWidget> spline = static_cast<RBGui::DropSplineWidget*>(win->createWidget("DropSpline"));
  spline->setPosition(Mocha::Vector2(16.0f, 64.0f));
  spline->setSize(Mocha::Vector2(256.0f, 64.0f));

  Mocha::RefPointer<RBGui::CheckWidget> check = static_cast<RBGui::CheckWidget*>(win->createWidget("Check"));
  check->setPosition(Mocha::Vector2(16.0f, 140.0f));
  check->setSize(Mocha::Vector2(256.0f, 25.0f));
  check->setText("Check me!");
  check->setChecked(true);

  Mocha::RefPointer<RBGui::OptionWidget> option = static_cast<RBGui::OptionWidget*>(win->createWidget("Option"));
  option->setPosition(Mocha::Vector2(16.0f, 160.0f));
  option->setSize(Mocha::Vector2(256.0f, 25.0f));
  option->setText("Select me!");

  Mocha::RefPointer<RBGui::OptionWidget> option2 = static_cast<RBGui::OptionWidget*>(win->createWidget("Option"));
  option2->setPosition(Mocha::Vector2(16.0f, 180.0f));
  option2->setSize(Mocha::Vector2(256.0f, 25.0f));
  option2->setText("No, select me!");

  // Create a menu along the top of the screen
  win = _guiManager->createWindow();
  win->setBorderVisible(false);
  win->setSize(Mocha::Vector2(_renderWindow->getWidth(), 22.0f));
  win->show();

  Mocha::RefPointer<RBGui::MenuWidget> menu = static_cast<RBGui::MenuWidget*>(win->createWidget("Menu"));
  menu->setSize(win->getSize());
  menu->setCallback(&Application::menuPicked, this);
  menu->addEntry("File.Open File", "FILE_OPEN");
  menu->addEntry("File.-", "");
  menu->addEntry("File.Save File", "FILE_SAVE");
  menu->addEntry("File.Save File As", "FILE_SAVEAS");
  menu->addEntry("File.-", "");
  menu->addEntry("File.Quit", "FILE_QUIT");

  menu->addEntry("Another Menu.Another World", "FILE_ANOTHERWORLD");
  menu->addEntry("Another Menu.Another Time", "FILE_ANOTHERTIME");
  menu->addEntry("Another Menu.Another Time.In An Age Of Wonder", "FILE_INAGEOFWONDER");
  menu->addEntry("Another Menu.Another Time.This World Was Green And Good", "FILE_GREENANDGOOD");
  menu->addEntry("Another Menu.Another Time.This World Was Green And Good.Until The Crystal Cracked", "FILE_CRYSTAL");

  menu->addEntry("Help.About", "HELP_ABOUT");

  // Create more test windows

  win = _guiManager->createWindow();
  win->setPosition(Mocha::Vector2(128.0f, 128.0f));
  win->setSize(Mocha::Vector2(300.0f, 400.0f));
  win->setText("Another Test Window");
  win->setCloseable(false);
  win->show();

  // Set a callback so we know when the window is resized

  win->setCallback(&Application::browserResized, this, "Resized");

  // Create an attribute edit widget

  RBGui::AttributeEditWidget* w = static_cast<RBGui::AttributeEditWidget*>(win->createWidget("AttributeEdit"));
  w->setCallback(&Application::attributeChanged, this);
  w->setSize(win->getClientRectangle().getSize());
  w->setName("Editor");

  // Fill in the attributes that can be edited
  // Each AttributeEntry has the following parameters:
  // Title, unique string ID, type, initial value
  // The string ID is used to identify the attribute when it changes in the callback
  // See Application::attributeChanged for an example of how to handle callbacks

  RBGui::AttributeMap m;
  m["Test Group 1"].push_back(RBGui::AttributeEntry("File Value", "FILE", "file|dll;exe"));
  m["Test Group 1"].push_back(RBGui::AttributeEntry("Float Value", "TEST1", "float", 4.0f));
  m["Test Group 1"].push_back(RBGui::AttributeEntry("Vector 2 Value", "TEST2", "vector2", 4.0f));
  m["Test Group 1"].push_back(RBGui::AttributeEntry("Vector 3 Value", "TEST3", "vector3", 4.0f));
  m["Test Group 1"].push_back(RBGui::AttributeEntry("Color Value", "COLOR", "color", 8.0f));
  m["Test Group 1"].push_back(RBGui::AttributeEntry("Push Me!", "BUTTON", "button"));
  m["Test Group 1"].push_back(RBGui::AttributeEntry("Select File", "SELECT_FILE", "button"));
  m["Test Group 2"].push_back(RBGui::AttributeEntry("Bool Value", "BOOL", "bool", false));
  m["Test Group 2"].push_back(RBGui::AttributeEntry("Text Value", "TEXT", "text|multiline", "Hello!"));
  m["Test Group 2"].push_back(RBGui::AttributeEntry("Int Value", "INT", "int", 20));
  m["Test Group 2"].push_back(RBGui::AttributeEntry("List Value", "LIST", "list|Entry 1|Entry 2|Entry 3|Entry 4", "Entry 2"));
  m["Test Group 2"].push_back(RBGui::AttributeEntry("Spline Value", "SPLINE", "spline"));
  m["Test Group 2"].push_back(RBGui::AttributeEntry("Slider Value", "SLIDER", "slider", 0.5f));

  w->setAttributes(m);
  w->updateAttribute("BOOL", false);
  w->updateAttribute("COLOR", Mocha::Color::Red);

  // Setup the handles of the spline attribute
  // This list could also have been passed in as the initial value for the attribute entry

  Mocha::ValueList v;
  v.push_back(Mocha::Vector2(1, 0));
  v.push_back(Mocha::Vector2(1, 0.25));
  v.push_back(Mocha::Vector2(0, 0.75));
  v.push_back(Mocha::Vector2(0, 1));

  w->updateAttribute("SPLINE", v);

  // Test persistance
  /*
  Mocha::DataSection s;
  win->getRoot()->save(s);
  Mocha::RefPointer<CustomStream> stream = new CustomStream("test.widget");
  s.write(*stream);
  */
}

void Application::browserResized(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  RBGui::Window& win = static_cast<RBGui::Window&>(vElement);
  win.findWidget("Editor")->setSize(win.getClientRectangle().getSize());
}


void Application::fileSelected(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  _guiManager->createMessageBox("File Selected", "You selected: " + vData[0].getString())->show();
}


void Application::attributeChanged(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  // Get the name of the attribute

  const Mocha::String& name = vData[0].getAsString();

  // Get the value of the attribute

  const Mocha::Value& value = vData[1];

  // Do something...

  if (name == "BUTTON")
    _guiManager->createMessageBox("Hooray!", "You clicked me!")->show();
  else if (name == "SELECT_FILE")
    _guiManager->createFileSelectWindow("Select File", ".", "ilk;dll",
					new RBGui::MemberGuiCallback<Application>(&Application::fileSelected, this),
					RBGui::FILESELECTWINDOW_SAVE)->show();
}


void Application::menuPicked(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  // Get the ID of the menu that was picked

  const Mocha::String& id = vData[0].getAsString();

  // Do something with ID...

  if (id == "FILE_QUIT")
    quit();
  else if (id == "HELP_ABOUT")
    _guiManager->createMessageBox("About", "Right Brain Games GUI\nOgre Sample Application\nVersion 1.0")->show();
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
