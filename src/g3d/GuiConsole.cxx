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

#include <OIS/OIS.h>
#include <OGRE/Ogre.h>

#include <Mocha/DataSection.h>
#include <Mocha/Stream.h>
#include <Mocha/Timer.h>

#include <RBGui/GuiDefines.h>
#include <RBGui/Widgets/ScrollWidget.h>
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
  History()
    {
      // adding empty string as default entry
      mLineList.push_back(string(""));
      mIndex = 1;
    }

  /** Insert a new string, the last one typed */
  void insert(const char* str)
    {
      mLineList.push_back(string(str));
      mIndex = mLineList.size();
    }

  /** Get a string from the history */
  const char* getByIndex(size_t i)
    {
      if (i >= mLineList.size()) {
	cout << "History: getByIndex: n>size, returning history[back]: " << mLineList.back() << endl;
	return mLineList.back().c_str();
      } else {
	return mLineList[i].c_str();
      }
    }

  /** Return the next command from history (empty for the last) */
  const char* getNext()
    {
      if (mIndex < (mLineList.size() - 1))
	mIndex++;

      cout << "History: getNext: [" << mIndex << "] " << getByIndex(mIndex) << endl;
      return getByIndex(mIndex);
    }

  /** Return the previous command from history */
  const char* getPrev()
    {
      if (mIndex > 0)
	mIndex--;

      cout << "History: getPrev: [" << mIndex << "] " << getByIndex(mIndex) << endl;
      return getByIndex(mIndex);
    }

private:
  /** Array of strings to store our history */
  std::vector<std::string> mLineList;
  /** Pointer to the current line */
  size_t mIndex;
};


/*******************************************************************************
 * GuiConsole
 ******************************************************************************/
GuiConsole::GuiConsole(RBGui::GuiManager& guiMgr) :
  _guiMgr(guiMgr), _mainWin(0), _consolePrompt(0), _consolePanel(0), _history(0)
{
  _history = new History();

  unsigned int w = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
  unsigned int h = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

  _mainWin = _guiMgr.createWindow();
  _mainWin->setPosition(Mocha::Vector2(0, h*0.7f));
  _mainWin->setSize(Mocha::Vector2(static_cast<float>(w), h*0.3f));
  _mainWin->setText("Console Window");
  _mainWin->setCloseable(false);
  _mainWin->setMovable(false);
  _mainWin->setResizeable(false);
  // _mainWin->setBorderVisible(false);
  _mainWin->show();

  const float promptHeight = 18.0f;
  const Mocha::Rectangle& windowScreen = _mainWin->getClientRectangle();
  Mocha::Vector2 consolePanelSize = windowScreen.getSize();
  consolePanelSize.y -= promptHeight;

  _consolePanel = static_cast<RBGui::TextWidget*>(_mainWin->createWidget("Text"));
  _consolePanel->setName("ConsolePanel");
  _consolePanel->setPosition(Mocha::Vector2(0.0f, 0.00f));
  _consolePanel->setSize(consolePanelSize);
  _consolePanel->setVerticalTextAlignment(RBGui::TEXTALIGN_BOTTOM);
  _consolePanel->setText("Console started.");

  _consolePrompt = static_cast<RBGui::TextEntryWidget*>(_mainWin->createWidget("TextEntry"));
  _consolePrompt->setName("ConsolePrompt");
  _consolePrompt->setPosition(Mocha::Vector2(0.0f, consolePanelSize.y));
  _consolePrompt->setSize(Mocha::Vector2(consolePanelSize.x, promptHeight));
  _consolePrompt->setText("Type in something.");

  _consolePrompt->setCallback(&GuiConsole::callbackPromptReturnPressed, this, "onReturnPressed");
  _consolePrompt->setCallback(&GuiConsole::callbackPromptKeyPressed, this, "onKeyPressed");
  _consolePrompt->setCallback(&GuiConsole::callbackPromptKeyReleased, this, "onKeyReleased");
}

GuiConsole::~GuiConsole()
{
  delete _consolePrompt; _consolePrompt = 0;
  delete _consolePanel; _consolePanel = 0;
  delete _mainWin; _mainWin = 0;
  delete _history; _history = 0;
}

void GuiConsole::callbackPromptReturnPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  _history->insert(_consolePrompt->getText().c_str());

  string text = _consolePanel->getText() + "\n" + _consolePrompt->getText();
  _consolePanel->setText(text);
  _consolePrompt->setText("");
}


void GuiConsole::callbackPromptKeyPressed(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  cout << "GuiConsole key pressed" << endl;
  cout << "value: " << vData[0].getAsNumber() << endl;

  // history
  const char* cmd = 0;
  if (static_cast<int>(vData[0].getAsNumber()) == OIS::KC_UP) {
    cmd = _history->getPrev();
  } else if (static_cast<int>(vData[0].getAsNumber()) == OIS::KC_DOWN) {
    cmd = _history->getNext();
  }

  if (cmd)
      _consolePrompt->setText(cmd);
}

void GuiConsole::callbackPromptKeyReleased(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
{
  cout << "GuiConsole key released" << endl;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
