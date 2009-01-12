/*                    G U I C O N S O L E . H
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

/** @file GuiConsole.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header of the GuiConsole class of 3D Geometry Editor (g3d).
 */

#ifndef __G3D_GUICONSOLE_H__
#define __G3D_GUICONSOLE_H__


#include <Mocha/Value.h>

#include "GuiBaseWindow.h"
#include "History.h"


namespace RBGui {
  class GuiElement;
  class TextEntryWidget;
  class TextWidget;
}


/**
 * @brief GUI Console class of the 3D Geometry Editor.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * This class implements the Console for the application.  It tries to
 * work as a regular terminal, letting the user to enter commands and
 * showing outputs.
 */
class GuiConsole : public GuiBaseWindow, public Observer
{
public:
  /**
   * Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiConsole(RBGui::GuiManager& guiMgr);

  /** Default destructor */
  ~GuiConsole();

  /** @see GuiBaseWindow::resize */
  virtual void resize(float contentLeft, float contentTop, float contentWidth, float contentHeight);

  /** @see Observer::update */
  virtual void update(const ObserverEvent& event);

private:
  /** Prompt of the console, to enter commands */
  RBGui::TextEntryWidget* _prompt;
  /** Panel of the console, to show text (information, commands
   * entered, etc) */
  RBGui::TextWidget* _panel;


  /** Add text to console panel */
  void addTextToPanel(const std::string& content);
  /** Get content of the prompt */
  const std::string& getPromptContent() const;
  /** Set content of the prompt */
  void setPromptContent(const std::string& content);

  /** Callback for "KeyPressed" in prompt */
  void callbackPromptKeyPressed(RBGui::GuiElement& element, const Mocha::ValueList& data);
  /** Callback for "FocusRecieved" [sic] in prompt */
  void callbackFocusReceived(RBGui::GuiElement& element, const Mocha::ValueList& data);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
