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

/** @file OgreScene.h
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	Ogre Qt Scene for use with a GraphicsView.  Requires a
 *	QGLWidget (or similar) set as viewport.
 */

#ifndef __G3D_OGRESCENE_H__
#define __G3D_OGRESCENE_H__

#include <QGraphicsScene>
#include <QGLWidget>

#include <OGRE/Ogre.h>

class OgreScene : public QGraphicsScene
{
    Q_OBJECT

public:
    OgreScene();
    ~OgreScene();

public slots:
    void handleResize(const QRectF &rect);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    
    // Input
    /* TODO
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    */

private:
    /** Prepare Ogre for rendering.  Must be called after the creation
     *  of an OpenGL context. */
    void initOgre();
    /** Load resources. */
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
