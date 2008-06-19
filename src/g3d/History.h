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
 *	History functionality for GuiConsole.
 */

#ifndef __G3D_HISTORY_H__
#define __G3D_HISTORY_H__


#include <string>


/**
 * @brief Implements History service for the Console
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
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
    std::string s(str);
    if (s.length() != 0) {
      _lines.push_back(s);
      _index = _lines.size();
      //cout << "History: inserted: [" << _index << "] " << s << endl;
    }
  }

  /** Get a string from the history */
  std::string getByIndex(size_t i)
  {
    if (i < _lines.size()) {
      // index is in proper range (and _lines not empty, since 0<=i<lines.size())
      //cout << "History: getByIndex[" << _index << "]: " << _lines[i] << endl;
      return _lines[i];
    } else {
      // index out of range -- return empty string
      //cout << "History: getByIndex: _lines empty or index out of range, returning empty string" << endl;
      return std::string("");
    }
  }

  /** Return the next command from history (empty for the "current" one) */
  std::string getNext()
  {
    if (_index < (_lines.size() - 1)) {
      _index++;
      //cout << "History: getNext: [" << _index << "] " << getByIndex(_index) << endl;
      return getByIndex(_index);
    } else {
      // when "returning" from history (we past the most recent
      // typed), the prompt is cleared
      return std::string("");
    }
  }

  /** Return the previous command from history, remains in the oldest
   * if the user continues to press the key */
  std::string getPrev()
  {
    if (_index > 0)
      _index--;

    //cout << "History: getPrev: [" << _index << "] " << getByIndex(_index) << endl;
    return getByIndex(_index);
  }

private:
  /** Array of strings to store our history */
  std::vector<std::string> _lines;
  /** Pointer to the current line */
  size_t _index;
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
