/*              G U I C O M M A N D O V E R L A Y. C X X
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

/** @file GuiCommandOverlay.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the GuiCommandOverlay class of 3D Geometry
 *	Editor (g3d), along with some internal classes.
 */

#include <OIS/OISKeyboard.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreWindowEventUtilities.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/SimpleWindowFader.h>
#include <RBGui/Window.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "Logger.h"
#include "History.h"
#include "GuiWindowManager.h"

#include "GuiCommandOverlay.h"


/*******************************************************************************
 * GuiCommandOverlay
 ******************************************************************************/
GuiCommandOverlay::GuiCommandOverlay(RBGui::GuiManager& guiMgr) :
  GuiBaseWindow(guiMgr), _mainWin(0), _commandPrompt(0)
{
  // creating windows and widgets
  _mainWin = _guiMgr.createWindow();
  _mainWin->setName("Command Overlay");
  _mainWin->setText("Command:");
  _mainWin->setCloseable(false);
  _mainWin->setMovable(false);
  _mainWin->setResizeable(false);
  // _mainWin->setBorderVisible(false);
  // _mainWin->setOpacity(0.8f);
  // _mainWin->setFader(new RBGui::SimpleWindowFader());
  // _mainWin->setModal(true);
  _mainWin->show();
  GuiBaseWindow::setMainWindow(_mainWin);

  _commandPrompt = static_cast<RBGui::TextEntryWidget*>(_mainWin->createWidget("TextEntry"));
  _commandPrompt->setName("CommandPrompt");

  // setting callbacks for window/widget events within RBGui.
  // ReturnPressed managed in KeyPressed, since both are called anyway
  _commandPrompt->setCallback(&GuiCommandOverlay::callbackPromptKeyPressed, this, "onKeyPressed");

  GuiWindowManager::instance().registerWindow(this);
}

GuiCommandOverlay::~GuiCommandOverlay()
{
  delete _commandPrompt; _commandPrompt = 0;
  delete _mainWin; _mainWin = 0;
}

void GuiCommandOverlay::resize(float contentLeft, float contentTop, float contentWidth, float contentHeight)
{
  const float promptHeight = 18.0f;

  _mainWin->setPosition(Mocha::Vector2(contentLeft + (contentWidth*0.05f),
				       contentTop + ((contentHeight-promptHeight)/2.0f)));
  _mainWin->setSize(Mocha::Vector2(contentWidth*0.9f, promptHeight));

  const Mocha::Rectangle& contentRect = _mainWin->getClientRectangle();

  _commandPrompt->setPosition(Mocha::Vector2(0.0f, 0.0f));
  _commandPrompt->setSize(contentRect.getSize());
}

void GuiCommandOverlay::callbackPromptKeyPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  /// \todo mafm: create history controller, and link both this and
  /// the same function of GuiConsole to it

  /*
  //cout << "GuiCommandOverlay key pressed, value: " << vData[0].getAsNumber() << endl;
  int key = static_cast<int>(vData[0].getAsNumber());
  std::string cmd("");
  switch (key) {
    case OIS::KC_RETURN:
      // return key -- insert in history
      cmd = _commandPrompt->getText();
      if (cmd.length() > 0) {
	//cout << "GuiCommandOverlay return pressed, inserting: '" << cmd << "'" << endl;
	_history->insert(cmd.c_str());
	_consolePanel->setText(_consolePanel->getText() + "\n" + cmd);
	_commandPrompt->setText("");
      } else {
	//cout << "GuiCommandOverlay return pressed, but empty command" << endl;
      }
      break;
    case OIS::KC_UP:
    case OIS::KC_DOWN:
      // up & down keys -- navigate history
      if (key == OIS::KC_UP) {
	cmd = _history->getPrev();
      } else if (key == OIS::KC_DOWN) {
	cmd = _history->getNext();
      }
      _commandPrompt->setText(cmd);
      break;
    default:
      // nothing
      ;
  }
  */
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
