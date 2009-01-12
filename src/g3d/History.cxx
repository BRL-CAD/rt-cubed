/*                    H I S T O R Y . C X X
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

/** @file History.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of History functionality.
 */

#include "History.h"


/*******************************************************************************
 * History
 ******************************************************************************/
template <> History* Singleton<History>::_instance = 0;

History::History() :
  _index(0)
{
}

void History::insert(const char* str)
{
  insert(std::string(str));
}

void History::insert(const std::string& str)
{
  if (str.length() != 0) {
    _lines.push_back(str);
    _index = _lines.size();

    // notify observers
    notify(HistoryObserverEvent(HistoryObserverEvent::ADDED_ENTRY, str));
  }
}

std::string History::getByIndex(size_t i)
{
  if (i < _lines.size()) {
    // index is in proper range (and _lines not empty, since 0<=i<lines.size())
    return _lines[i];
  } else {
    // index out of range -- return empty string
    return std::string("");
  }
}

std::string History::getNext()
{
  std::string entry("");
  if (_index < (_lines.size() - 1)) {
    _index++;
    entry = getByIndex(_index);
  } else {
    // when "returning" from history (we past the most recent typed),
    // the prompt is cleared
    _index = _lines.size();
  }

  // notify observers
  notify(HistoryObserverEvent(HistoryObserverEvent::INDEX_CHANGED, entry));

  return entry;
}

std::string History::getPrev()
{
  if (_index > 0)
    _index--;

  std::string entry = getByIndex(_index);

  // notify observers
  notify(HistoryObserverEvent(HistoryObserverEvent::INDEX_CHANGED, entry));

  return entry;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
