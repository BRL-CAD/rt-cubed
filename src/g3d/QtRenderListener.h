/*                  Q T R E N D E R L I S T E N E R . H
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

/** @file OgreScene.h
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	Ogre Qt Scene for use with a GraphicsView.  Requires a
 *	QGLWidget (or similar) set as viewport.
 */

#ifndef __G3D__QTRENDERLISTENER_H__
#define __G3D__QTRENDERLISTENER_H__

#include <QtGui/QApplication>

#include <OGRE/OgreRenderQueueListener.h>

class QtRenderListener : public RenderQueueListener 
{
public:
    QtRenderListener(QApplication &qapp, const Ogre::Camera *camera, const Ogre::SceneManager *sceneMgr);
    
    virtual void renderQueueStarted(uint8 queueGroupId, const Ogre::String &invocation, bool &skipThisInvocation);
    virtual void renderQueueEnded(uint8 queueGroupId, const Ogre::String &invocation, bool &repeatThisInvocation);

private:
    QApplication *_qapp;
    Ogre::Camera *_camera;
    Ogre::SceneManager *_sceneMgr;
};

#endif

/*
 * Local Variables:
 * mode: C++
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
