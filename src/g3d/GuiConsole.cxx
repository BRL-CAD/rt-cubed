/*                  G U I C O N S O L E . C X X
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
/** @file GuiConsole.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the GUI Console class of 3D Geometry Editor
 *	(g3d), along with some internal classes.
 */

//#include "common.h"

#include <OIS/OISKeyboard.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreWindowEventUtilities.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/Window.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "Logger.h"

#include "GuiConsole.h"
#include "History.h"


/**
 * Internal class for [OGRE] Window Resized events, so the Console
 * accomodates to the new size of the render window automatically.
 */
class WindowResizedListener : public Ogre::WindowEventListener
{
public:
  /**
   * Default constructor
   *
   * @param guiConsole The GUI Console that this listener relates to
   */
  WindowResizedListener(GuiConsole& guiConsole) : _guiConsole(guiConsole) { }

  /** Method for Window Resized events */
  virtual void windowResized(Ogre::RenderWindow* rw)
  {
    _guiConsole.resize(rw);
  }

private:
  /** Link to the GuiConsole that this listener applies */
  GuiConsole& _guiConsole;
};


/*******************************************************************************
 * GuiConsole
 ******************************************************************************/
GuiConsole::GuiConsole(RBGui::GuiManager& guiMgr) :
  _guiMgr(guiMgr), _mainWin(0), _consolePrompt(0), _consolePanel(0),
  _history(0), _windowResizedListener(0)
{
  // creating history
  _history = new History();

  // creating windows and widgets
  _mainWin = _guiMgr.createWindow();
  _mainWin->setText("Console Window");
  _mainWin->setCloseable(false);
  _mainWin->setMovable(false);
  _mainWin->setResizeable(false);
  // _mainWin->setBorderVisible(false);
  _mainWin->show();

  _consolePanel = static_cast<RBGui::TextWidget*>(_mainWin->createWidget("Text"));
  _consolePanel->setName("ConsolePanel");
  _consolePanel->setVerticalTextAlignment(RBGui::TEXTALIGN_BOTTOM);
  _consolePanel->setText("Console started.");

  _consolePrompt = static_cast<RBGui::TextEntryWidget*>(_mainWin->createWidget("TextEntry"));
  _consolePrompt->setName("ConsolePrompt");

  // setting callbacks for window/widget events within RBGui.
  // ReturnPressed managed in KeyPressed, since both are called anyway
  _consolePrompt->setCallback(&GuiConsole::callbackPromptKeyPressed, this, "onKeyPressed");
  _consolePrompt->setCallback(&GuiConsole::callbackPromptKeyReleased, this, "onKeyReleased");

  // listener for [OGRE] window resized
  _windowResizedListener = new WindowResizedListener(*this);
  Ogre::WindowEventUtilities::addWindowEventListener(Ogre::Root::getSingleton().getAutoCreatedWindow(),
						     _windowResizedListener);

  // set initial size
  resize(Ogre::Root::getSingleton().getAutoCreatedWindow());
}

GuiConsole::~GuiConsole()
{
  delete _consolePrompt; _consolePrompt = 0;
  delete _consolePanel; _consolePanel = 0;
  delete _mainWin; _mainWin = 0;
  delete _history; _history = 0;
  delete _windowResizedListener; _windowResizedListener = 0;
}

void GuiConsole::resize(Ogre::RenderWindow* rw)
{
  unsigned int w = rw->getWidth();
  unsigned int h = rw->getHeight();

  _mainWin->setPosition(Mocha::Vector2(0, (h-0.3f)/2.0f));
  _mainWin->setSize(Mocha::Vector2(static_cast<float>(w), h*0.3f));

  const float promptHeight = 18.0f;
  const Mocha::Rectangle& windowScreen = _mainWin->getClientRectangle();
  Mocha::Vector2 consolePanelSize = windowScreen.getSize();
  consolePanelSize.y -= promptHeight;

  _consolePanel->setPosition(Mocha::Vector2(0.0f, 0.00f));
  _consolePanel->setSize(consolePanelSize);
  _consolePanel->setWrap(true);

  _consolePrompt->setPosition(Mocha::Vector2(0.0f, consolePanelSize.y));
  _consolePrompt->setSize(Mocha::Vector2(consolePanelSize.x, promptHeight));
}

void GuiConsole::callbackPromptKeyPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  //cout << "GuiConsole key pressed, value: " << vData[0].getAsNumber() << endl;
  int key = static_cast<int>(vData[0].getAsNumber());
  std::string cmd("");
  switch (key) {
    case OIS::KC_RETURN:
      // return key -- insert in history
      cmd = _consolePrompt->getText();
      if (cmd.length() > 0) {
	//cout << "GuiConsole return pressed, inserting: '" << cmd << "'" << endl;
	_history->insert(cmd.c_str());
	_consolePanel->setText(_consolePanel->getText() + "\n" + cmd);
	_consolePrompt->setText("");
      } else {
	//cout << "GuiConsole return pressed, but empty command" << endl;
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
      _consolePrompt->setText(cmd);
      break;
    default:
      // nothing
      ;
  }
}

void GuiConsole::callbackPromptKeyReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  //cout << "GuiConsole key released" << endl;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
