/*                  M A I N W I N D O W . H
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
 *	Implementation for the main GUI
 */

#include "MainWindow.h"

#include <QString>
#include <QApplication>
    

MainWindow::MainWindow() : ogreView(new OgreGLWidget()),
			   scene(new QGraphicsScene()),
			   cmdInterp(new CommandInterpreter()),
			   window(new CameraInputLayer(*ogreView))
{
    setViewport(ogreView);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setScene(scene);
    
    setupUi(window);

    window->setStyleSheet("background: transparent");

    QGraphicsProxyWidget *windowProxy = scene->addWidget(window);
    windowProxy->setAcceptHoverEvents(true);
    window->move(0, 0);
    window->setFocusPolicy(Qt::ClickFocus);

    // WARNING: The entries of the cameraProjection dropdown MUST be
    // listed in the same order as the elements of
    // Ogre::ProjectionType (found in OgreFrustrum.h)
    QObject::connect(cameraProjection, SIGNAL(activated(int)),
		     ogreView, SLOT(setProjection(int)));
    QObject::connect(cameraProjection, SIGNAL(activated(int)),
		     window, SLOT(setFocus(void)));

    QObject::connect(cameraMode, SIGNAL(activated(int)),
		     ogreView, SLOT(setCameraMode(int)));
    QObject::connect(cameraMode, SIGNAL(activated(int)),
		     window, SLOT(setFocus(void)));

    QObject::connect(console, SIGNAL(commandRan(QString)),
		     cmdInterp, SLOT(execute(QString)));
    QObject::connect(cmdInterp, SIGNAL(commandDone(QString)),
		     console, SLOT(pushOutput(QString)));

    // Give focus to the render area, and thus camera control.
    window->setFocus(Qt::OtherFocusReason);
}

MainWindow::~MainWindow() 
{
    delete cmdInterp;
    delete window;
}


void MainWindow::resizeEvent(QResizeEvent *event) 
{
    // Just large enough not to cause scrollbars to appear.
    window->resize(event->size() - QSize(1, 1));
    OgreGraphicsView::resizeEvent(event);
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
