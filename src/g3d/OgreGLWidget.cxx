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

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#else
#error OgreGLWidget is currently only implemented for GLX
#endif

#include <OGRE/Ogre.h>
#include <OGRE/OgreLogManager.h>

#include "Logger.h"
#include "CameraModeBlender.h"
#include "CameraModeMGED.h"
#include "CameraModeOrbital.h"

#define OGRE_PLUGIN_FILE        (DATA_DIR "ogreplugins.cfg")
#define OGRE_CFG_FILE           (DATA_DIR "ogre.cfg")
#define OGRE_LOG_FILE           (DATA_DIR "ogre.log")
#define OGRE_RESOURCES_CFG_FILE (DATA_DIR "resources.cfg")

OgreGLWidget::OgreGLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
    _ogreContext(0), _renderWindow(0), _camera(0), _viewport(0), _scene(0),
    _cameraCtl(new CameraModeBlender)
{
    // We need to swap carefully to prevent flicker.
    setAutoBufferSwap(false);
    
    // Take keyboard focus after being clicked
    setFocusPolicy(Qt::ClickFocus);
    
    _root = new Ogre::Root(OGRE_PLUGIN_FILE, OGRE_CFG_FILE, OGRE_LOG_FILE);
    
    // TODO: Explicitly configure
    _root->loadPlugin("RenderSystem_GL");
    _root->setRenderSystem(*(_root->getAvailableRenderers().begin()));
    _root->initialise(false);
    Logger::logDEBUG("Ogre initialized!\n");

    clock_gettime(CLOCK_REALTIME, &_lastFrame);
}

OgreGLWidget::~OgreGLWidget() 
{
    Logger::logDEBUG("Shutting down OGRE...");
	
    delete _root;

    Logger::logDEBUG("OGRE shutdown complete.");
}


CameraMode& OgreGLWidget::getCameraMode() const
{
    return *_cameraCtl;
}


void OgreGLWidget::initializeGL() 
{   
    Ogre::NameValuePairList params;

    WId win_id = winId();

#ifdef Q_WS_X11
    _display = x11Info().display();
    XWindowAttributes window_attributes;
    Status get_attrib_status = XGetWindowAttributes(_display, win_id, &window_attributes);
    OgreAssert(get_attrib_status, "Couldn't determine attributes of render window.");
    XVisualInfo xvis_template;
    xvis_template.visualid = XVisualIDFromVisual(window_attributes.visual);

    int items;

    XVisualInfo *xvisinfo = XGetVisualInfo(_display, VisualIDMask, &xvis_template, &items);
    OgreAssert(items > 0, "Couldn't determine the XVisualInfo for the render window.");
    if (items > 1)
	Ogre::LogManager::getSingleton().logMessage(
	    "More than one visual structure found for visualID " +
	    Ogre::StringConverter::toString(xvis_template.visualid) +
	    " - Expect BadMatches.", Ogre::LML_CRITICAL);

    params["externalWindowHandle"] =
	Ogre::StringConverter::toString((unsigned long)_display) +
	":" + Ogre::StringConverter::toString((unsigned int)x11Info().screen()) +
	":" + Ogre::StringConverter::toString((unsigned long)win_id) +
	":" + Ogre::StringConverter::toString((unsigned long)xvisinfo);

    _renderWindow = _root->createRenderWindow(metaObject()->className() + Ogre::StringConverter::toString((unsigned long)this), width(), height(), false, &params);

    XFree(xvisinfo);
    _ogreContext = glXGetCurrentContext();
#else
#error OgreGLWidget is currently only implemented for GLX
#endif

    if(!_renderWindow) {
	// TODO: Real error handling
	throw std::exception();
    }
    _renderWindow->setVisible(true);

    loadResources();

    // Create scene, camera, viewport
    _scene = _root->createSceneManager("DefaultSceneManager", "g3d SceneManager");
    _camera = _scene->createCamera("g3d Camera");
    _camera->setAutoAspectRatio(true);
    _viewport = _renderWindow->addViewport(_camera);
    _viewport->setBackgroundColour(Ogre::ColourValue(0.1f, 0.1f, 0.1f, 1.0f));
    _scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    Ogre::Light* l = _scene->createLight("MainLight");
    l->setPosition(0, 10, 0);
    l->setDiffuseColour(Ogre::ColourValue(1.0, 0.5, 0.0));

    // Basic rendering test
    Ogre::Entity *sphereEnt = _scene->createEntity("Knot", "knot.mesh");
    Ogre::SceneNode *sphereNode = _scene->getRootSceneNode()->createChildSceneNode("KnotNode");
    sphereNode->setVisible(true);
    sphereNode->attachObject(sphereEnt);
    sphereNode->setPosition(50, 0, 0);
    _camera->setPosition(0, 0, 0);
    _camera->lookAt(sphereNode->getPosition());

    _renderWindow->setVisible(true);

    // Orthographic is the default projection mode
    setProjection(0);

    Logger::logDEBUG("Ogre ready to render.");
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
    if(_renderWindow) {
	makeOgreCurrent();
	_renderWindow->resize(width, height);
	_renderWindow->windowMovedOrResized();
	makeCurrent();
    }
    QGLWidget::resizeGL(width, height);
}

void OgreGLWidget::paintGL() 
{
    makeOgreCurrent();
    
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    _cameraCtl->updateCamera(_camera, (now.tv_sec - _lastFrame.tv_sec) + 1e-9 * (now.tv_nsec - _lastFrame.tv_nsec));
    _lastFrame = now;

    if(_root->_fireFrameStarted()) {
	_renderWindow->update(false);
	_root->_fireFrameEnded();
    }
    
    makeCurrent();
}


void OgreGLWidget::setProjection(int type) 
{
    if(_camera) {
	Logger::logDEBUG("Setting projection %d", type);
	_camera->setProjectionType(static_cast<Ogre::ProjectionType>(type));
    } else {
	Logger::logWARNING("Attempted to set projection mode with uninitialized Ogre!");
    }
}

void OgreGLWidget::setCameraMode(int type)
{
    Logger::logDEBUG("Setting camera mode %d", type);
    
    if(_cameraCtl) {
	delete _cameraCtl;
    }
    
    // WARNING: The cases here MUST match up with the ordering of
    // camera modes in the GUI's dropdown.
    switch(type) {
    case 0:
	_cameraCtl = new CameraModeBlender();
	break;

    case 1:
	_cameraCtl = new CameraModeMGED();
	break;

    case 2:
	_cameraCtl = new CameraModeOrbital();
	break;

    default:
	Logger::logWARNING("Attempted to set invalid camera mode!");
	break;
    }
}

void OgreGLWidget::makeOgreCurrent() 
{
#ifdef Q_WS_X11
    if(_ogreContext != glXGetCurrentContext() && _display) {
	glXMakeCurrent(_display, winId(), _ogreContext);
    }
#else
#error OgreGLWidget is currently only implemented for GLX
#endif
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
