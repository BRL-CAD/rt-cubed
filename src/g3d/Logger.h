/*                        L O G G E R . H
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

/** @file Logger.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Logging facilities for the application.
 *
 * This class sets the interface for the Logging facilities in the
 * application.
 *
 * \note The idea is that, since it would be used anywhere, it should be
 * handy and simple to use, and thus it uses the traditional printf()
 * syntax.  Additionally, it's not longer to write
 * 'Logger.logDEBUG(msg)' that 'printf("DEBUG: msg")' (and I was even
 * tempted to reduce it to 'Log.DEBUG(msg)'); so people don't really
 * have excuses to start using rogue std::cout and printf() around
 * even for debugging purposes.
 *
 * \note That's also the reason why it uses static methods -- to avoid
 * having to introduce the getInstance() in the middle and make it
 * longer, as in the somewhat ridiculous
 * 'Ogre::LogManager::getSingletonPtr()->logMessage(msg, level)', and
 * having to format the message separately.  That way is painful to
 * use, and induces to use simpler printf()s and std::cout's that
 * remain there forever.
 */

#ifndef __G3D_LOGGER_H__
#define __G3D_LOGGER_H__


/// If not using GCC, elide __attribute__
#ifndef __GNUC__
#define __attribute__(x)	/* nothing */
#endif


#include <string>
#include <vector>

#include "../../include/Utility/Singleton.h"

#include "Observer.h"


/**
 * @brief ObserverEvent for Logger
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class LoggerObserverEvent: public ObserverEvent
{
public:
  /** Action Identifier enumerator */
  enum ActionId { ADDED_ENTRY = 1 };

  /** Action Identifier */
  const ActionId _actionId;
  /** Content of the event */
  const std::string _content;


  /** Default constructor */
  LoggerObserverEvent(ActionId id, const std::string& content) :
    ObserverEvent("LoggerObserverEvent"), _actionId(id), _content(content) { }
};


/** @brief Class implementing logging facilities
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 */
class Logger : public ObserverSubject, public Singleton<Logger>
{
public:
  /** Encodes priority levels and names */
  enum Level {
    // Only for developers
    DEBUG = 1,
    // Useful information, like "Screenshot dumped 'filename'"
    INFO,
    // Most likely an error, or will lead to it
    WARNING,
    // Plain error
    ERROR,
    // Error that will force the program to stop imminently
    FATAL
  };

  /** Set a new level filter (to really log the messages with the
   * given or superior level).
   *
   * @param level New level to filter out messages.
   */
  void setLevelFilter(Level level);
  /** Translate the given encoded level to an string */
  static const char* translateToString(Level level);

  /** Log a FATAL message */
  static void logFATAL(const char* msg, ...) __attribute__((format(printf, 1, 2)));
  /** Log an ERROR message */
  static void logERROR(const char* msg, ...) __attribute__((format(printf, 1, 2)));
  /** Log a WARNING */
  static void logWARNING(const char* msg, ...) __attribute__((format(printf, 1, 2)));
  /** Log a INFO message */
  static void logINFO(const char* msg, ...) __attribute__((format(printf, 1, 2)));
  /** Log a DEBUG message */
  static void logDEBUG(const char* msg, ...) __attribute__((format(printf, 1, 2)));

private:
  /** Friend access for the Singleton */
  friend class Singleton<Logger>;

  /** Attribute to save the logging level desired */
  static Level _levelFilter;


  /** Default constructor */
  Logger();

  /** Common function to use by the specific methods */
  void log(Level level, const char* msg);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
