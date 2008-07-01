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

/** @file GuiBaseWindow.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief Implementation of basic window infrastructure.
 *
 */

#include <RBGui/GuiManager.h>
#include <RBGui/Window.h>

#include "Logger.h"

#include "GuiBaseWindow.h"


/*******************************************************************************
 * GuiBaseWindow
 ******************************************************************************/
GuiBaseWindow::GuiBaseWindow(RBGui::GuiManager& guiMgr,
			     const std::string& name,
			     const std::string& text,
			     bool inTaskbar) :
  _guiMgr(guiMgr), _mainWindow(0), _presentInTaskbar(inTaskbar)
{
  // creating window
  _mainWindow = _guiMgr.createWindow();
  _mainWindow->setName(name);
  _mainWindow->setText(text);
}

GuiBaseWindow::~GuiBaseWindow()
{
  Logger::logDEBUG("GuiBaseWindow::~GuiBaseWindow()");
}

const std::string& GuiBaseWindow::getName() const
{
  return _mainWindow->getName();
}

bool GuiBaseWindow::getPresentInTaskbar() const
{
  return _presentInTaskbar;
}

void GuiBaseWindow::hide()
{
  _mainWindow->hide();
}

void GuiBaseWindow::show()
{
  _mainWindow->show();
}



// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
