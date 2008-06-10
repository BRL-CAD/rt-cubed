/*
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by the
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

/** @file GuiConsole.h
 *
 * @brief
 *	Header of the GuiConsole class of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_GUICONSOLE_H__
#define __G3D_GUICONSOLE_H__


#include <RBGui/Core.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

class History;


/** @brief GUI Console class of the 3D Geometry Editor.
 *
 * This class implements the Console for the application.  It tries to
 * work as a regular terminal, letting the user to enter commands and
 * showing outputs.
 */
class GuiConsole
{
public:
  /** Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiConsole(RBGui::GuiManager& guiMgr);

  /** Default destructor */
  ~GuiConsole();

private:
  /** Link to the RBGui's GUI manager */
  RBGui::GuiManager& _guiMgr;

  /** Main window */
  RBGui::Window* _mainWin;
  /** Prompt of the console, to enter commands */
  RBGui::TextEntryWidget* _consolePrompt;
  /** Panel of the console, to show text (information, commands
   * entered, etc) */
  RBGui::TextWidget* _consolePanel;

  /** History service for the console */
  History* _history;

  /** Callback for "ReturnPressed" in console prompt */
  void callbackPromptReturnPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "KeyPressed" in console prompt */
  void callbackPromptKeyPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "KeyReleased" in console prompt */
  void callbackPromptKeyReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
