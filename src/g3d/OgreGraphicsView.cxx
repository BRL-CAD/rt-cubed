/*                  O G R E G R A P H I C S V I E W . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008-2010 United States Government as represented by the
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

/** @file OgreGraphicsView.cxx
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief
 *      Graphics view for use with OgreGLWidget
 */

#include <QtGui/QResizeEvent>
#include "OgreGraphicsView.h"
#include "OgreGLWidget.h"

void OgreGraphicsView::resizeEvent(QResizeEvent *event)
{
    static_cast<OgreGLWidget *>(viewport())->resizeGL(event->size().width(), event->size().height());
    QGraphicsView::resizeEvent(event);
}

void OgreGraphicsView::drawBackground(QPainter *, const QRectF &) 
{
    static_cast<OgreGLWidget *>(viewport())->updateGL();
}

void OgreGraphicsView::drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[]) 
{
    QGraphicsView::drawItems(painter, numItems, items, options);
    static_cast<OgreGLWidget *>(viewport())->swapBuffers();
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
