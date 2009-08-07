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

#include "Logger.h"

#include "MainWindow.h"

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
  
  MainWindow *window = new MainWindow();
  window->show();

  Logger::logDEBUG("Qt initialized.");

  // Main loop
  int ret = qapp.exec();

  delete window;

  return ret;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
