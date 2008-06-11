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

/** @file GuiConsole.cxx
 *
 * @brief
 *	Implementation of the GUI Console class of 3D Geometry Editor
 *	(g3d), along with some internal classes.
 */

#include <OIS/OISKeyboard.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreRenderWindow.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/Window.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "GuiConsole.h"

using namespace std;


/** @brief Implements History service for the Console
 *
 * The class store the commands the user has entered into the
 * entrybox/prompt of the console window.  It keeps all of them in
 * memory (it's not supposed to represent huge amounts), in sequential
 * order.
 */
class History {
public:
  /** Default constructor */
  History() : _index(0)
    { }

  /** Insert a new string, the last one typed */
  void insert(const char* str)
    {
      string s(str);
      if (s.length() != 0) {
	_lines.push_back(s);
	_index = _lines.size();
	cout << "History: inserted: [" << _index << "] " << s << endl;
      }
    }

  /** Get a string from the history */
  string getByIndex(size_t i)
    {
      if (i < _lines.size()) {
	// index is in proper range (and _lines not empty, since 0<=i<lines.size())
	cout << "History: getByIndex[" << _index << "]: " << _lines[i] << endl;
	return _lines[i];
      } else {
	// index out of range -- return empty string
	cout << "History: getByIndex: _lines empty or index out of range, returning empty string" << endl;
	return string("");
      }
    }

  /** Return the next command from history (empty for the "current" one) */
  string getNext()
    {
      if (_index < (_lines.size() - 1)) {
	_index++;
	cout << "History: getNext: [" << _index << "] " << getByIndex(_index) << endl;
	return getByIndex(_index);
      } else {
	// when "returning" from history (we past the most recent
	// typed), the prompt is cleared
	return string("");
      }
    }

  /** Return the previous command from history, remains in the oldest
   * if the user continues to press the key */
  string getPrev()
    {
      if (_index > 0)
	_index--;

      cout << "History: getPrev: [" << _index << "] " << getByIndex(_index) << endl;
      return getByIndex(_index);
    }

private:
  /** Array of strings to store our history */
  vector<string> _lines;
  /** Pointer to the current line */
  size_t _index;
};


/*******************************************************************************
 * GuiConsole
 ******************************************************************************/
GuiConsole::GuiConsole(RBGui::GuiManager& guiMgr) :
  _guiMgr(guiMgr), _mainWin(0), _consolePrompt(0), _consolePanel(0), _history(0)
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
  _consolePrompt->setText("Type in something.");

  // set initial size
  resize();

  // setting callbacks for window/widget events within RBGui
  // return managed in KeyPressed, since both are called anyway
  // _consolePrompt->setCallback(&GuiConsole::callbackPromptReturnPressed, this, "onReturnPressed");
  _consolePrompt->setCallback(&GuiConsole::callbackPromptKeyPressed, this, "onKeyPressed");
  _consolePrompt->setCallback(&GuiConsole::callbackPromptKeyReleased, this, "onKeyReleased");

  _mainWin->setCallback(&GuiConsole::callbackWindowResized, this, "Resized");
}

GuiConsole::~GuiConsole()
{
  delete _consolePrompt; _consolePrompt = 0;
  delete _consolePanel; _consolePanel = 0;
  delete _mainWin; _mainWin = 0;
  delete _history; _history = 0;
}

void GuiConsole::resize()
{
  unsigned int w = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
  unsigned int h = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

  _mainWin->setPosition(Mocha::Vector2(0, h*0.7f));
  _mainWin->setSize(Mocha::Vector2(static_cast<float>(w), h*0.3f));

  const float promptHeight = 18.0f;
  const Mocha::Rectangle& windowScreen = _mainWin->getClientRectangle();
  Mocha::Vector2 consolePanelSize = windowScreen.getSize();
  consolePanelSize.y -= promptHeight;

  _consolePanel->setPosition(Mocha::Vector2(0.0f, 0.00f));
  _consolePanel->setSize(consolePanelSize);

  _consolePrompt->setPosition(Mocha::Vector2(0.0f, consolePanelSize.y));
  _consolePrompt->setSize(Mocha::Vector2(consolePanelSize.x, promptHeight));
}

/** \note not used, see above
void GuiConsole::callbackPromptReturnPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  cout << "GuiConsole return pressed" << endl;
  _history->insert(_consolePrompt->getText().c_str());

  string text = _consolePanel->getText() + "\n" + _consolePrompt->getText();
  _consolePanel->setText(text);
  _consolePrompt->setText("");
}
*/

void GuiConsole::callbackPromptKeyPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  cout << "GuiConsole key pressed, value: " << vData[0].getAsNumber() << endl;
  int key = static_cast<int>(vData[0].getAsNumber());
  string cmd("");
  switch (key) {
  case OIS::KC_RETURN:
    // return key -- insert in history
    cmd = _consolePrompt->getText();
    if (cmd.length() > 0) {
      cout << "GuiConsole return pressed, inserting: '" << cmd << "'" << endl;
      _history->insert(cmd.c_str());
      _consolePanel->setText(_consolePanel->getText() + "\n" + cmd);
      _consolePrompt->setText("");
    } else {
      cout << "GuiConsole return pressed, but empty command" << endl;
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
  cout << "GuiConsole key released" << endl;
}

void GuiConsole::callbackWindowResized(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  cout << "GuiConsole window resized" << endl;
  resize();
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
