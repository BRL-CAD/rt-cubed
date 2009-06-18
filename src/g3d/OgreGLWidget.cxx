/*                  O G R E G L W I D G E T . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by the
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

/** @file OgreGLWidget.h
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief
 *      Ogre Qt OpenGL widget
 */

#include "OgreGLWidget.h"

#include <exception>
#include <cstdio>

#include <OGRE/Ogre.h>

// RBGui->Qt transitional
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

// RBGui->Qt transitional
#include "CameraManager.h"
#include "GuiWindowManager.h"
#include "GuiWidgetRotation.h"
#include "GuiConsole.h"
#include "GuiCommandOverlay.h"
#include "GuiCamera.h"

#define OGRE_PLUGIN_FILE        (DATA_DIR "ogreplugins.cfg")
#define OGRE_CFG_FILE           (DATA_DIR "ogre.cfg")
#define OGRE_LOG_FILE           (DATA_DIR "ogre.log")
#define OGRE_RESOURCES_CFG_FILE (DATA_DIR "resources.cfg")

// RBGui->Qt transitional
/** @brief Listener for Mouse events
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
   * @param guiMgr The GUI Manager that this listener is related to
   */
    MouseListener(RBGui::GuiManager& guiMgr) :
    _guiMgr(guiMgr), _prevPos(Mocha::Vector2(0.0f, 0.0f))
    { }

  /** Method for Mouse Moved events */
  virtual bool mouseMoved(const OIS::MouseEvent& event) {
    // Get absolute position
    Mocha::Vector2 absPos = Mocha::Vector2(static_cast<float>(event.state.X.abs), 
					   static_cast<float>(event.state.Y.abs));
    // Calculate relative position in pixels
    Mocha::Vector2 relPos = absPos - _prevPos;
    _prevPos = absPos;

    // Send event to GUI
    bool used = _guiMgr.injectMouseMotion(relPos, absPos);
    if (!used && event.state.Z.rel != 0) {
      used = _guiMgr.injectMouseScrolled(static_cast<float>(event.state.Z.rel / 120.0f),
					 absPos);
    }
    if (used) {
      return true;
    }

    // Event to Camera
    used = CameraManager::instance().injectMouseMotion(event.state.X.abs,
						       event.state.Y.abs);
    if (!used && event.state.Z.rel != 0) {
      if (event.state.Z.rel > 0) {
	used = CameraManager::instance().injectMouseScrolled(CameraMode::POSITIVE);
      } else {
	used = CameraManager::instance().injectMouseScrolled(CameraMode::NEGATIVE);
      }
    }
    if (used) {
      return true;
    }

    return false;
  }
	
  /** Method for Mouse Pressed events */
  virtual bool mousePressed(const OIS::MouseEvent& event, OIS::MouseButtonID id) {
    // GUI
    bool used = _guiMgr.injectMousePressed(static_cast<RBGui::MouseButtonID>(id),
					   Mocha::Vector2(static_cast<float>(event.state.X.abs),
							  static_cast<float>(event.state.Y.abs)));
    if (used) {
      return true;
    }

    // Camera
    used = CameraManager::instance().injectMousePressed(id,
							event.state.X.abs,
							event.state.Y.abs);
    if (used) {
      return true;
    }

    return false;
  }

  /** Method for Mouse Released events */
  virtual bool mouseReleased(const OIS::MouseEvent& event, OIS::MouseButtonID id) {
    // GUI
    bool used = _guiMgr.injectMouseReleased(static_cast<RBGui::MouseButtonID>(id),
					    Mocha::Vector2(static_cast<float>(event.state.X.abs),
							   static_cast<float>(event.state.Y.abs)));
    if (used) {
      return true;
    }

    // Camera
    used = CameraManager::instance().injectMouseReleased(id,
							 event.state.X.abs,
							 event.state.Y.abs);
    if (used) {
      return true;
    }

    return false;
  }

private:
  /** Link to the GUI manager */
  RBGui::GuiManager& _guiMgr;
  /** Variable to save the state of the previous position of the
   * mouse */
  Mocha::Vector2 _prevPos;
};


/** @brief Listener for Keyboard events
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
  KeyListener(RBGui::GuiManager& guiMgr) :
    _guiMgr(guiMgr)
    { }

  /** Method for Key Pressed events */
  virtual bool keyPressed(const OIS::KeyEvent& event) {
    /*************************************************************************
     * These first ones have precedence over anything
     ************************************************************************/
    if (event.key == OIS::KC_ESCAPE) {
      // ESC key to quit -- hack for convenience while developing 
	//_app.quit();
      return true;
    } else if (event.key == OIS::KC_F12) {
      // Fullscreen
      //_app.toggleFullscreen();
      return true;
    }

    // No need to translate key IDs because they are the same as OIS
    bool used = _guiMgr.injectKeyPressed(static_cast<RBGui::KeyID>(event.key));
    if (used) {
      return true;
    }

    // Camera
    used = CameraManager::instance().injectKeyPressed(event.key);
    if (used) {
      return true;
    }

    // not handled before...
    return false;
  }
	
  /** Method for Key released events */
  virtual bool keyReleased(const OIS::KeyEvent& event) {
    // No need to translate key IDs because they are the same as OIS
    bool used = _guiMgr.injectKeyReleased(static_cast<RBGui::KeyID>(event.key));
    if (used) {
      return true;
    }

    // Camera
    used = CameraManager::instance().injectKeyReleased(event.key);
    if (used) {
      return true;
    }

    // not handled before
    return false;
  }

private:
  /** Link to the GUI manager */
  RBGui::GuiManager& _guiMgr;
};


/** @brief Listener for DeviceLost event
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
			     const Ogre::NameValuePairList* /* parameters */) {
    // Redraw the GUI if the device has been lost
    if (eventName == "DeviceLost") {
	//Logger::logWARNING("OGRE lost the device, redrawing");
	RBGui::Core::Get().invalidate();
    }
  }
};

OgreGLWidget::OgreGLWidget(QWidget *parent) :
    QGLWidget(parent),
    _scene(0), _camera(0), _viewport(0), _renderWindow(0),
    _mouse(0), _keyboard(0), _inputManager(0),
    _guiCore(0), _guiManager(0),
    _mouseListener(0), _keyListener(0), _lostDeviceListener(0), _rbguiRenderListener(0)
{
    _timer = new Mocha::Timer();
    _root = new Ogre::Root(OGRE_PLUGIN_FILE, OGRE_CFG_FILE, OGRE_LOG_FILE);
    
    // TODO: Explicitly configure
    if (_root->restoreConfig() || _root->showConfigDialog()) {
	_root->initialise(false);
    }
    printf("Ogre initialized!\n");
}

OgreGLWidget::~OgreGLWidget() 
{
    // RBGui->Qt Transitional
    {
	if (_inputManager) {
	    if (_mouse)
		_inputManager->destroyInputObject(_mouse);
	    if (_keyboard)
		_inputManager->destroyInputObject(_keyboard);
	    _inputManager->destroyInputSystem(_inputManager);
	}

	// Destroy input listeners
	//Logger::logINFO("Freeing input listeners");
	delete _mouseListener; _mouseListener = 0;
	delete _keyListener; _keyListener = 0;
	delete _lostDeviceListener; _lostDeviceListener = 0;

	/// \todo mafm: segfaulting and thus commented out at the moment,
	/// look more closely later

	// Release GUI resources
	//Logger::logINFO("Freeing RBGui resources");
	delete _rbguiRenderListener; _rbguiRenderListener = 0;
	//delete _guiCore; _guiCore = 0;
	//delete _guiManager; _guiManager = 0;
	//Logger::logINFO(" - clearing windows");
	// _guiManager->clear();
	//Logger::logINFO(" - removing the rest of the GUI");
	// _guiCore->destroyGui("g3d GUI");
	while (_windowList.size() > 0) {
	    // delete _windowList.back();
	    _windowList.pop_back();
	}

	// Shutdown OGRE
	//Logger::logINFO("Freeing OGRE resources");
	//Logger::logINFO(" - renderWindow");
	_renderWindow->removeAllViewports();
	_renderWindow->destroy();
    }

    if(_renderWindow) {
	_renderWindow->removeAllViewports();
	_renderWindow->destroy();
    }

    if(_root) {
	delete _root;
    }
}


void OgreGLWidget::initializeGL() 
{   
    Ogre::NameValuePairList params;
    params["currentGLContext"] = Ogre::String("True");

    _renderWindow = _root->createRenderWindow("MainRenderWindow", 640, 480, false, &params);
    if(!_renderWindow) {
	// TODO: Real error handling
	throw std::exception();
    }
    _renderWindow->setVisible(true);

    loadResources();
    printf("Resources loaded!\n");

    // Create scene, camera, viewport
    _scene = _root->createSceneManager("DefaultSceneManager", "g3d SceneManager");
    _camera = _scene->createCamera("g3d Camera");
    _viewport = _renderWindow->addViewport(_camera);
    _viewport->setBackgroundColour(Ogre::ColourValue(0.6f, 0.6f, 0.6f, 1.0f));
    _scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    Ogre::Light* l = _scene->createLight("MainLight");
    l->setPosition(0, 10, 0);
    l->setDiffuseColour(Ogre::ColourValue(1.0, 0.5, 0.0));

    _renderWindow->setVisible(true);

    // RBGui->Qt Transitional
    initRBGui();
}

void OgreGLWidget::loadResources() 
{
    Ogre::ConfigFile config;
    config.load(OGRE_RESOURCES_CFG_FILE);

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

    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreGLWidget::resizeGL(int width, int height)
{
    _renderWindow->windowMovedOrResized();
}

void OgreGLWidget::paintGL() 
{
    //_root->renderOneFrame();
    
    // RBGUI->Qt transitional
    {
	float delta = static_cast<float>(_timer->getDeltaSeconds());

	// If window was closed, we need to exit
	if (_renderWindow->isClosed()) {
	    //quit();
	    return;
	}

	// Pump message events
	Ogre::WindowEventUtilities::messagePump();

	// Make sure mouse region is up to date
	//_mouse->getMouseState().width = static_cast<int>(_renderWindow->getWidth());
	//_mouse->getMouseState().height = static_cast<int>(_renderWindow->getHeight());

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

	    // Update camera
	    CameraManager::instance().updateCamera(_camera, delta);

	    // Tell OGRE to render a frame. The GUI will get drawn as part of
	    // the OGRE render queue
	    if (_root) {
		_root->renderOneFrame();
	    }
	} else {
	    usleep(100*1000); // in microseconds
	}
    }
}

// RBGui->Qt Transitional use only
void OgreGLWidget::initRBGui() 
{
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

    // Register custom widgets
    RBGui::AddWidgetFactory("GuiWidgetRotation", &GuiWidgetRotation::factory);


    // Setup all the input stuff
    {
	std::ostringstream windowString;
	windowString << winId();

	OIS::ParamList paramList;
	paramList.insert(make_pair(std::string("WINDOW"), windowString.str()));
#if defined(WIN32)
	paramList.insert(make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND")));
	paramList.insert(make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
	paramList.insert(make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
	paramList.insert(make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
#else
	paramList.insert(make_pair(std::string("XAutoRepeatOn"), std::string("true")));
	paramList.insert(make_pair(std::string("x11_keyboard_grab"), std::string("false")));
	paramList.insert(make_pair(std::string("x11_mouse_grab"), std::string("false")));
#endif

	// Create input object using parameter list, then keyboard and mouse
	_inputManager = OIS::InputManager::createInputSystem(paramList);
	printf("Created input manager\n");
	_mouseListener = new MouseListener(*_guiManager);
	printf("Created mouse listener\n");
	// X error here:
	//_mouse = static_cast<OIS::Mouse*>(_inputManager->createInputObject(OIS::OISMouse, true));
	printf("Created mouse input object\n");
	//_mouse->setEventCallback(_mouseListener);
	_keyListener = new KeyListener(*_guiManager);
	printf("Created key listener\n");
	_keyboard = static_cast<OIS::Keyboard*>(_inputManager->createInputObject(OIS::OISKeyboard, true));
	printf("Created key input object\n");
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
    _windowList.push_back(new GuiCamera(*_guiManager));

    //createTestingWindows();
}

// RBGui->Qt Transitional use only
Ogre::Root *OgreGLWidget::root() const
{
    return _root;
}

// RBGui->Qt Transitional use only
Ogre::RenderWindow *OgreGLWidget::renderWindow() const
{
    return _renderWindow;
}

// RBGui->Qt Transitional use only
Ogre::Camera *OgreGLWidget::camera() const
{
    return _camera;
}

// RBGui->Qt Transitional use only
Ogre::Viewport *OgreGLWidget::viewport() const
{
    return _viewport;
}

// RBGui->Qt Transitional use only
Ogre::SceneManager *OgreGLWidget::scene() const
{
    return _scene;
}

/*
 * Local Variables:
 * mode: C++
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
