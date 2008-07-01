/*                    H I S T O R Y . H
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

/** @file History.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	History functionality for Console-like windows.
 */

#ifndef __G3D_HISTORY_H__
#define __G3D_HISTORY_H__


#include "Observer.h"

#include <string>
#include <vector>


/**
 * @brief ObserverEvent for History
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class HistoryObserverEvent: public ObserverEvent
{
public:
  /** Action Identifier enumerator */
  enum ActionId { ADDED_ENTRY = 1, INDEX_CHANGED };

  /** Action Identifier */
  ActionId _actionId;
  /** Content of the event */
  std::string _content;


  /** Default constructor */
  HistoryObserverEvent(ActionId id, const std::string& content) :
    ObserverEvent("HistoryObserverEvent"), _actionId(id), _content(content) { }
};


/**
 * @brief Implements History service for the Console-like windows
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * The class store the commands the user has entered into the
 * entrybox/prompt of the console or similar windows.  It keeps all of
 * them in memory (it's not supposed to represent huge amounts), in
 * sequential order, and it's not saved when the program finishes.
 */
class History: public ObserverSubject
{
public:
  /** Singleton, access to the manager */
  static History& instance();

  /** Insert a new string, the last one typed */
  void insert(const char* str);
  /** Insert a new string, the last one typed */
  void insert(const std::string& str);
  /** Return the next command from history (empty for the "current" one) */
  std::string getNext();
  /** Return the previous command from history, remains in the oldest
   * if the user continues to press the key */
  std::string getPrev();

private:
  /** Singleton instance */
  static History* INSTANCE;

  /** Array of strings to store our history */
  std::vector<std::string> _lines;
  /** Pointer to the current entry */
  size_t _index;


  /** Default constructor */
  History();

  /** Get a string from the history */
  std::string getByIndex(size_t i);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
