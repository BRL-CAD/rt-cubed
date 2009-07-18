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

#include <QTimer>

#include <OGRE/Ogre.h>

#include "Logger.h"

#define OGRE_PLUGIN_FILE        (DATA_DIR "ogreplugins.cfg")
#define OGRE_CFG_FILE           (DATA_DIR "ogre.cfg")
#define OGRE_LOG_FILE           (DATA_DIR "ogre.log")
#define OGRE_RESOURCES_CFG_FILE (DATA_DIR "resources.cfg")

#define FRAMEDELAY 10		// Milliseconds; 10ms == 100fps

OgreGLWidget::OgreGLWidget(QWidget *parent) :
    QGLWidget(parent),
    _scene(0), _camera(0), _viewport(0), _renderWindow(0)
{
    _root = new Ogre::Root(OGRE_PLUGIN_FILE, OGRE_CFG_FILE, OGRE_LOG_FILE);
    
    // TODO: Explicitly configure
    if (_root->restoreConfig() || _root->showConfigDialog()) {
	_root->initialise(false);
    }
    Logger::logDEBUG("Ogre initialized!\n");
}

OgreGLWidget::OgreGLWidget(QGLFormat f) :
    QGLWidget(f),
    _scene(0), _camera(0), _viewport(0), _renderWindow(0)
{
    _root = new Ogre::Root(OGRE_PLUGIN_FILE, OGRE_CFG_FILE, OGRE_LOG_FILE);
    
    // TODO: Explicitly configure
    if (_root->restoreConfig() || _root->showConfigDialog()) {
	_root->initialise(false);
    }
    Logger::logDEBUG("Ogre initialized!\n");
}

OgreGLWidget::~OgreGLWidget() 
{
    Logger::logDEBUG("Shutting down OGRE...");
	
    delete _root;

    Logger::logDEBUG("OGRE shutdown complete.");
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

    // Create scene, camera, viewport
    _scene = _root->createSceneManager("DefaultSceneManager", "g3d SceneManager");
    _camera = _scene->createCamera("g3d Camera");
    _viewport = _renderWindow->addViewport(_camera);
    _viewport->setBackgroundColour(Ogre::ColourValue(0.1f, 0.1f, 0.1f, 1.0f));
    _scene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    Ogre::Light* l = _scene->createLight("MainLight");
    l->setPosition(0, 10, 0);
    l->setDiffuseColour(Ogre::ColourValue(1.0, 0.5, 0.0));

    // Basic rendering test
    Ogre::Entity *sphereEnt = _scene->createEntity("Sphere", "sphere.mesh");
    Ogre::SceneNode *sphereNode = _scene->getRootSceneNode()->createChildSceneNode("SphereNode");
    sphereNode->setVisible(true);
    sphereNode->attachObject(sphereEnt);
    sphereNode->setPosition(50, 0, 0);
    _camera->setPosition(0, 0, 0);
    _camera->lookAt(sphereNode->getPosition());

    _renderWindow->setVisible(true);

    QTimer::singleShot(FRAMEDELAY, this, SLOT(update()));

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
    _renderWindow->windowMovedOrResized();
}

void OgreGLWidget::paintGL() 
{
    _root->renderOneFrame();
    QTimer::singleShot(FRAMEDELAY, this, SLOT(update()));
}


void OgreGLWidget::moveEvent(QMoveEvent* e) 
{
    if(_renderWindow) {
	_renderWindow->windowMovedOrResized();
    }
}


Ogre::Root *OgreGLWidget::root()
{
    return _root;
}

Ogre::RenderWindow *OgreGLWidget::renderWindow()
{
    return _renderWindow;
}

Ogre::Camera *OgreGLWidget::camera()
{
    return _camera;
}

Ogre::Viewport *OgreGLWidget::viewport()
{
    return _viewport;
}

Ogre::SceneManager *OgreGLWidget::scene()
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
