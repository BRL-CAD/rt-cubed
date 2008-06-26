/*                  G U I B A S E W I N D O W . C X X
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
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

#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/Window.h>

#include "Logger.h"

#include "GuiBaseWindow.h"


/*******************************************************************************
 * GuiBaseWindow
 ******************************************************************************/
GuiBaseWindow::GuiBaseWindow(RBGui::GuiManager& guiMgr, bool inTaskbar) :
  _guiMgr(guiMgr), _mainWin(0), _presentInTaskbar(inTaskbar)
{
}

GuiBaseWindow::~GuiBaseWindow()
{
  Logger::logDEBUG("GuiBaseWindow::~GuiBaseWindow()");
}

void GuiBaseWindow::setMainWindow(RBGui::Window* w)
{
  _mainWin = w;
}

const std::string& GuiBaseWindow::getName() const
{
  return _mainWin->getName();
}

bool GuiBaseWindow::getPresentInTaskbar() const
{
  return _presentInTaskbar;
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
