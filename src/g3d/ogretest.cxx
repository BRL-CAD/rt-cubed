/*                        M A I N . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
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

/** @file main.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Entry point of the 3D Geometry Editor (g3d).
 */

#include <QtGui>
#include <QGLWidget>

#include "OgreScene.h"

class GraphicsView : public QGraphicsView
{
public:
  GraphicsView(const char* title) 
  {
    setWindowTitle(title);
  }

protected:
  void resizeEvent(QResizeEvent *ev) 
  {
    if(scene()) {
      scene()->setSceneRect(QRect(QPoint(0, 0), ev->size()));
    }
    QGraphicsView::resizeEvent(ev);
  }
};

int main(int argc, char** argv)
{
#if defined(WIN32)
  // HACK!
  // This is required on Windows XP because of a bug that causes
  // timing to be wrong when more than one CPU is available.
  // This issue has been fixed in Vista.

  HANDLE id = GetCurrentThread();
  DWORD pmask;
  DWORD psysmask;
  GetProcessAffinityMask(id, &pmask, &psysmask);
  DWORD res = SetThreadAffinityMask(id, 1);
#endif
  
  // Set up Qt
  QApplication qapp(argc, argv);

  GraphicsView view("G3D");
  OgreScene scene;
  
  view.setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
  view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  view.setScene(&scene);
  view.show();

  view.resize(1024, 768);

  // Main loop
  // TODO: Clean exit support
  while(true) {
    qapp.processEvents();
  }

  return 0;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
