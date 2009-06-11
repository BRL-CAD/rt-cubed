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

#include <OGRE/Ogre.h>

#define OGRE_PLUGIN_FILE        (DATA_DIR "ogreplugins.cfg")
#define OGRE_CFG_FILE           (DATA_DIR "ogre.cfg")
#define OGRE_LOG_FILE           (DATA_DIR "ogre.log")
#define OGRE_RESOURCES_CFG_FILE (DATA_DIR "resources.cfg")

OgreGLWidget::OgreGLWidget(QWidget *parent) : QGLWidget(parent)
{
}

OgreGLWidget::~OgreGLWidget() 
{
    _renderWindow->removeAllViewports();
    _renderWindow->destroy();

    delete _root; _root = 0;
}


void OgreGLWidget::initializeGL() 
{
    _root = new Ogre::Root(OGRE_PLUGIN_FILE, OGRE_CFG_FILE, OGRE_LOG_FILE);
    _root->restoreConfig();
    _root->initialise(false);

    Ogre::NameValuePairList params;
    params["currentGLContext"] = Ogre::String("True");

    _renderWindow = _root->createRenderWindow("MainRenderWindow", 640, 480, false, &params);

    // Setup resource locations
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

	// Initialize resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }

    _renderWindow->setVisible(true);
}

void OgreGLWidget::resizeGL(int width, int height)
{
    _renderWindow->windowMovedOrResized();
}

void OgreGLWidget::paintGL() 
{
    _root->renderOneFrame();
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
