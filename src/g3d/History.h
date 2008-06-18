/*
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the GUI Console class of 3D Geometry Editor
 *	(g3d), along with some internal classes.
 */

//#include "common.h"

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


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
