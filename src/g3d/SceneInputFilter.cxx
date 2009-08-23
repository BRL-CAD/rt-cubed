/*                  S C E N E I N P U T F I L T E R . C X X
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

/** @file SceneInputFilter.cxx
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief
 *      Receive input for scene and act on it
 */

#include "SceneInputFilter.h"

#include <QGraphicsSceneWheelEvent>

SceneInputFilter::SceneInputFilter(OgreGLWidget *target) : _oglwidget(target)
{
}

bool SceneInputFilter::maybeUpdate(bool value) 
{
    if(value) {
	_oglwidget->update();
    }
    return value;
}

bool SceneInputFilter::eventFilter(QObject *, QEvent *event) 
{
    switch(event->type()) {
    case QEvent::KeyPress:
	return maybeUpdate(_oglwidget->getCameraMode().injectKeyPressed(static_cast<QKeyEvent*>(event)));
	
    case QEvent::KeyRelease:
	return maybeUpdate(_oglwidget->getCameraMode().injectKeyReleased(static_cast<QKeyEvent*>(event)));
	
    case QEvent::MouseButtonPress:
	return maybeUpdate(_oglwidget->getCameraMode().injectMousePressed(static_cast<QMouseEvent*>(event)));
    case QEvent::GraphicsSceneMousePress:
    {
	QGraphicsSceneMouseEvent *mouse = static_cast<QGraphicsSceneMouseEvent*>(event);
	QMouseEvent wrap(QEvent::MouseButtonPress, mouse->screenPos(), mouse->button(), mouse->buttons(), mouse->modifiers());
	return maybeUpdate(_oglwidget->getCameraMode().injectMousePressed(&wrap));
    }

    case QEvent::MouseButtonRelease:
	return maybeUpdate(_oglwidget->getCameraMode().injectMouseReleased(static_cast<QMouseEvent*>(event)));
    case QEvent::GraphicsSceneMouseRelease:
    {
	QGraphicsSceneMouseEvent *mouse = static_cast<QGraphicsSceneMouseEvent*>(event);
	QMouseEvent wrap(QEvent::MouseButtonRelease, mouse->screenPos(), mouse->button(), mouse->buttons(), mouse->modifiers());
	return maybeUpdate(_oglwidget->getCameraMode().injectMouseReleased(&wrap));
    }

    case QEvent::MouseMove:
	return maybeUpdate(_oglwidget->getCameraMode().injectMouseMotion(static_cast<QMouseEvent*>(event)));
    case QEvent::GraphicsSceneMove:
    {
	QGraphicsSceneMouseEvent *mouse = static_cast<QGraphicsSceneMouseEvent*>(event);
	QMouseEvent wrap(QEvent::MouseMove, mouse->screenPos(), mouse->button(), mouse->buttons(), mouse->modifiers());
	return maybeUpdate(_oglwidget->getCameraMode().injectMouseMotion(&wrap));
    }

    case QEvent::Wheel:
	return maybeUpdate(_oglwidget->getCameraMode().injectMouseScrolled((static_cast<QWheelEvent*>(event)->delta() > 0) ? CameraMode::POSITIVE : CameraMode::NEGATIVE));
    case QEvent::GraphicsSceneWheel:
	return maybeUpdate(_oglwidget->getCameraMode().injectMouseScrolled((static_cast<QGraphicsSceneWheelEvent*>(event)->delta() > 0) ? CameraMode::POSITIVE : CameraMode::NEGATIVE));

    default:
	break;
    }
    return false;
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
