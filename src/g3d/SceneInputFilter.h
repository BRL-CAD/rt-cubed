/*                  S C E N E I N P U T F I L T E R . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2011 United States Government as represented by the
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

/** @file SceneInputFilter.h
 *
 * @author Benjamin Saunders <ralith@users.sourceforge.net>
 *
 * @brief 
 *	A filter to handle input for the 3D scene.
 */

#ifndef __G3D_SCENEINPUTFILTER_H__
#define __G3D_SCENEINPUTFILTER_H__

#include <QtCore/QObject>
#include <QtCore/QEvent>

#include "OgreGLWidget.h"

class SceneInputFilter : public QObject
{
    Q_OBJECT

public:
    /** Constructs a SceneInputFilter
     * @param target The widget containing the Ogre scene to handle input for.
     */
    SceneInputFilter(OgreGLWidget *target);

protected:
    bool eventFilter(QObject *object, QEvent *event);
    
private:
    bool maybeUpdate(bool value);

    Ogre::Camera *_camera;

    OgreGLWidget *_oglwidget;
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
