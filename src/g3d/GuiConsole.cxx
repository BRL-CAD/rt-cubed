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
 *	(g3d).
 */

#include <OIS/OISKeyboard.h>
#include <OGRE/OgreRenderWindow.h>
#include <RBGui/GuiDefines.h>
#include <RBGui/GuiManager.h>
#include <RBGui/Window.h>
#include <RBGui/Widgets/TextWidget.h>
#include <RBGui/Widgets/TextEntryWidget.h>

#include "GuiConsole.h"

#include "Logger.h"
#include "History.h"
#include "Command.h"
#include "CommandInterpreter.h"
#include "GuiWindowManager.h"


/*******************************************************************************
 * GuiConsole
 ******************************************************************************/
GuiConsole::GuiConsole(RBGui::GuiManager& guiMgr) :
  GuiBaseWindow(guiMgr, "Console", "Console", false), _prompt(0), _panel(0)
{
  // creating windows and widgets
  // _mainWindow->setTheme("brlcad_translucent.theme");
  _mainWindow->setCloseable(false);
  _mainWindow->setMovable(false);
  _mainWindow->setResizeable(false);
  _mainWindow->setBorderVisible(false);
  show();

  _panel = static_cast<RBGui::TextWidget*>(_mainWindow->createWidget("Text"));
  _panel->setName("ConsolePanel");
  _panel->setVerticalTextAlignment(RBGui::TEXTALIGN_BOTTOM);
  _panel->setText("Console started.");
  _panel->setWrap(true);
  _panel->setScrollable(true);

  _prompt = static_cast<RBGui::TextEntryWidget*>(_mainWindow->createWidget("TextEntry"));
  _prompt->setName("ConsolePrompt");

  // setting callbacks for window/widget events within RBGui.
  // ReturnPressed managed in KeyPressed, since both are called anyway
  _mainWindow->setCallback(&GuiConsole::callbackFocusReceived, this, "FocusRecieved"); // recieved [sic]
  _prompt->setCallback(&GuiConsole::callbackPromptKeyPressed, this, "onKeyPressed");

  GuiWindowManager::instance().registerWindow(this);
  Logger::instance().attach(this);
  History::instance().attach(this);

  /// \todo mafm: remove this call at some point...

  // creating an initial shape, for convenience while in initial
  // phases of development... (need to instantiate commands...)
  CommandInterpreter::instance();
}

GuiConsole::~GuiConsole()
{
  /// \todo mafm: could/should automatically detached by ~Observer()
  History::instance().detach(this);
  Logger::instance().detach(this);

  delete _prompt; _prompt = 0;
  delete _panel; _panel = 0;
  delete _mainWindow; _mainWindow = 0;
}

void GuiConsole::resize(float contentLeft, float contentTop, float contentWidth, float contentHeight)
{
  // main window
  _mainWindow->setPosition(Mocha::Vector2(contentLeft,
					  contentTop + (contentHeight*0.7f)));
  _mainWindow->setSize(Mocha::Vector2(contentWidth, contentHeight*0.3f));

  // widgets
  const float promptHeight = 18.0f;
  Mocha::Vector2 panelSize = _mainWindow->getClientRectangle().getSize();
  panelSize.y -= promptHeight;

  _panel->setPosition(Mocha::Vector2(0.0f, 0.0f));
  _panel->setSize(panelSize);

  _prompt->setPosition(Mocha::Vector2(0.0f, panelSize.y));
  _prompt->setSize(Mocha::Vector2(panelSize.x, promptHeight));
}

void GuiConsole::update(const ObserverEvent& event)
{
  try {
    // history events
    {
      const HistoryObserverEvent* e = dynamic_cast<const HistoryObserverEvent*>(&event);
      if (e) {
	switch (e->_actionId) {
	case HistoryObserverEvent::ADDED_ENTRY:
	  addTextToPanel(e->_content);
	  setPromptContent("");
	  break;
	case HistoryObserverEvent::INDEX_CHANGED:
	  setPromptContent(e->_content);
	  break;
	default:
	  throw "Action not understood by Observer";
	}
	return;
      }
    }

    // logger events
    {
      const LoggerObserverEvent* e = dynamic_cast<const LoggerObserverEvent*>(&event);
      if (e) {
	switch (e->_actionId) {
	case LoggerObserverEvent::ADDED_ENTRY:
	  addTextToPanel(e->_content);
	  break;
	default:
	  throw "Action not understood by Observer";
	}
	return;
      }
    }

    // event not processed before
    throw "Event type not expected by Observer";
  } catch (const char* error) {
    Logger::logWARNING("GuiConsole: '%s' event: %s", event._className.c_str(), error);
  }
}

void GuiConsole::addTextToPanel(const std::string& content)
{
  if (content.length() > 0) {
    _panel->setText(_panel->getText() + "\n" + content);
  }
}

const std::string& GuiConsole::getPromptContent() const
{
  return _prompt->getText();
}

void GuiConsole::setPromptContent(const std::string& content)
{
  _prompt->setText(content);
  _prompt->setCursorPos(content.length());
}

void GuiConsole::callbackPromptKeyPressed(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& vData)
{
  /// \note mafm: should be synchronized with CommandOverlay, to avoid
  /// inconsistencies

  int key = static_cast<int>(vData[0].getAsNumber());
  std::string cmd("");
  switch (key) {
    case OIS::KC_RETURN:
      // return key -- insert in history
      cmd = getPromptContent();
      if (cmd.length() > 0) {
	setPromptContent("");
	History::instance().insert(cmd.c_str());
	CommandOutput output;
	CommandInterpreter::instance().execute(cmd, output);
	addTextToPanel(output.getOutput());
      } else {
	// return pressed, but empty command
	addTextToPanel(" ");
      }
      break;
    case OIS::KC_UP:
    case OIS::KC_DOWN:
      // up & down keys -- navigate history
      if (key == OIS::KC_UP) {
	cmd = History::instance().getPrev();
      } else if (key == OIS::KC_DOWN) {
	cmd = History::instance().getNext();
      }
      setPromptContent(cmd);
      break;
    case OIS::KC_TAB:
      // tab -- command autocompletion
      cmd = getPromptContent();
      cmd = CommandInterpreter::instance().getAutocompleteString(cmd);
      setPromptContent(cmd);
      break;
    default:
      // nothing
      ;
  }
}

void GuiConsole::callbackFocusReceived(RBGui::GuiElement& /* vElement */, const Mocha::ValueList& /* vData */)
{
  _mainWindow->setFocused(_prompt);
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
