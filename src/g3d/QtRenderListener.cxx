/*                  Q T R E N D E R L I S T E N E R . C X X
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

/** @file OgreScene.cxx
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	Performs Qt event handling/rendering immediately after
 * 	Ogre renders.
 */

#include "QtRenderListener.h"

#include <GL/gl.h>

#include <OGRE/Ogre.h>

QtRenderListener::QtRenderListener(const QApplication *qapp, const Ogre::MovableObject *parentObj, const Ogre::Camera *camera, Ogre::SceneManager *sceneMgr) :
    _qapp(qapp),
    _camera(camera), _sceneMgr(sceneMgr), _parentObj(parentObj),
    _clearPass(NULL)
{}


void QtRenderListener::renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String &invocation, bool &skipThisInvocation)
{}

void QtRenderListener::renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String &invocation, bool &repeatThisInvocation) 
{
    // Save matrices
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    Ogre::RenderSystem *renderSystem = _parentObj->_getManager()->getDestinationRenderSystem();
    Ogre::Node *parentNode = _parentObj->getParentNode();
    renderSystem->_setWorldMatrix(parentNode->_getFullTransform());
    renderSystem->_setViewMatrix(_camera->getViewMatrix());
    renderSystem->_setProjectionMatrix(_camera->getProjectionMatrixRS());

    if (!_clearPass)
    {
	Ogre::MaterialPtr clearMat = Ogre::MaterialManager::getSingleton().getByName("BaseWhite");
	_clearPass = clearMat->getTechnique(0)->getPass(0);
    }
    // Set a clear pass to give the renderer a clear renderstate
    _sceneMgr->_setPass(_clearPass, true, false);

    GLboolean depthTestEnabled=glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    GLboolean stencilTestEnabled = glIsEnabled(GL_STENCIL_TEST);
    glDisable(GL_STENCIL_TEST);

    // Save some more GL state
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // Step Qt
    _qapp->processEvents();

    // Restore state
    glPopAttrib();
    if (depthTestEnabled)
    {
	glEnable(GL_DEPTH_TEST);
    }
    if (stencilTestEnabled)
    {
	glEnable(GL_STENCIL_TEST);
    }
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
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
