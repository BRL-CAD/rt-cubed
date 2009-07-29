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

#include <ctime>

#include <QGLWidget>

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderWindow.h>

#include "OgreGraphicsView.h"

#include "CameraMode.h"

#ifdef Q_WS_X11
#include "qmetatype.h"
#include <GL/glx.h>
#else
#error OgreGLWidget is currently only implemented for GLX
#endif

class OgreGLWidget : public QGLWidget
{
    Q_OBJECT

    friend class OgreGraphicsView;
public:
    OgreGLWidget(QWidget *parent = NULL);
    ~OgreGLWidget();

public slots:
    void setProjection(int type);
    void setCameraMode(int type);

protected:
    /** Loads Ogre resources specified in the resources.cfg */
    void loadResources();

    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

    void makeOgreCurrent();

#ifdef Q_WS_X11
    GLXContext _ogreContext;
    Display *_display;
#else
#error OgreGLWidget is currently only implemented for GLX
#endif

    Ogre::Root *_root;
    Ogre::RenderWindow *_renderWindow;
    Ogre::Camera *_camera;
    Ogre::Viewport *_viewport;
    Ogre::SceneManager *_scene;

    CameraMode *_cameraCtl;

    struct timespec _lastFrame;
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
