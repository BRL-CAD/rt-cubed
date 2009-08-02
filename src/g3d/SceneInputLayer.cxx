/*                  S C E N E I N P U T L A Y E R . C X X
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

/** @file SceneInputLayer.cxx
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief
 *      Receive input for scene and act on it
 */

#include "SceneInputLayer.h"

SceneInputLayer::SceneInputLayer(OgreGLWidget *target) : oglwidget(target)
{
}


void SceneInputLayer::keyPressEvent(QKeyEvent *e) 
{
    if(!oglwidget->getCameraMode().injectKeyPressed(e)) {
	e->ignore();
    } else {
	oglwidget->update();
    }
}

void SceneInputLayer::keyReleaseEvent(QKeyEvent *e) 
{
    if(!oglwidget->getCameraMode().injectKeyReleased(e)) {
	e->ignore();
    } else {
	oglwidget->update();
    }
}

void SceneInputLayer::mousePressEvent(QMouseEvent *e) 
{
    if(oglwidget->getCameraMode().injectMousePressed(e)) {
	e->ignore();
    } else {
	oglwidget->update();
    }
}

void SceneInputLayer::mouseReleaseEvent(QMouseEvent *e) 
{
    if(!oglwidget->getCameraMode().injectMouseReleased(e)) {
	e->ignore();
    } else {
	oglwidget->update();
    }
}

void SceneInputLayer::mouseMoveEvent(QMouseEvent *e) 
{
    if(!oglwidget->getCameraMode().injectMouseMotion(e)) {
	e->ignore();
    } else {
	oglwidget->update();
    }
}

void SceneInputLayer::wheelEvent(QWheelEvent *e) 
{
    if(!oglwidget->getCameraMode().injectMouseScrolled((e->delta() > 0) ? CameraMode::POSITIVE : CameraMode::NEGATIVE)) {
	e->ignore();
    } else {
	oglwidget->update();
    }
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
