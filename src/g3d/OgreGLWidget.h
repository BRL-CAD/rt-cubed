/*                  O G R E G L W I D G E T . H
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
 *	Ogre Qt OpenGL widget header
 */

#ifndef __G3D_GLWIDGET_H__
#define __G3D_GLWIDGET_H__

#include <QGLWidget>

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderWindow.h>

class OgreGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    OgreGLWidget(QWidget *parent = NULL);
    ~OgreGLWidget();

    // RBGui->Qt Transitional use only
    Ogre::Root *root() const;
    Ogre::RenderWindow *renderWindow() const;
    Ogre::Camera *camera() const;
    Ogre::Viewport *viewport() const;
    Ogre::SceneManager *scene() const;

protected:
    void initializeGL();
    void resizeGL( int, int );
    void paintGL();

    void loadResources();

    Ogre::Root *_root;
    Ogre::RenderWindow *_renderWindow;
    Ogre::Camera *_camera;
    Ogre::Viewport *_viewport;
    Ogre::SceneManager *_scene;
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
