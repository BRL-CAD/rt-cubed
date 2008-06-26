/*              G U I C O M M A N D O V E R L A Y. H
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

/** @file GuiCommandOverlay.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header of the GuiCommandOverlay class of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_GUICOMMANDOVERLAY_H__
#define __G3D_GUICOMMANDOVERLAY_H__


#include "GuiBaseWindow.h"
#include "History.h"

namespace RBGui {
  class TextEntryWidget;
}


/**
 * @brief GUI Command Overlay class of the 3D Geometry Editor.
 *
 * This class implements the Command Overlay for the application.  It
 * lets the user to enter commands.
 */
class GuiCommandOverlay : public GuiBaseWindow, public HistoryListener
{
public:
  /**
   * Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiCommandOverlay(RBGui::GuiManager& guiMgr);
  /** Default destructor */
  ~GuiCommandOverlay();

  /** @see GuiBaseWindow::resize */
  virtual void resize(float contentLeft, float contentTop, float contentWidth, float contentHeight);

  /** @see HistoryListener::indexChanged */
  virtual void indexChanged(const std::string& entry);

private:
  /** Main Window (in the sense of the GUI) implemented by the class
   * which inherits this one */
  RBGui::Window* _mainWin;
  /** Prompt to enter commands */
  RBGui::TextEntryWidget* _prompt;

  /** Callback for "KeyPressed" in prompt */
  void callbackPromptKeyPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
  /** Callback for "FocusRecieved" [sic] in prompt */
  void callbackFocusReceived(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
