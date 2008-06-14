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

/** @file Logger.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Logging facilities for the application.
 */

#ifndef __G3D_LOGGER_H__
#define __G3D_LOGGER_H__


/** @brief Class implementing logging facilities
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 */
class Logger
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
  static void setLevelFilter(Level level);

  /** Log a FATAL message */
  static void logFATAL(const char* msg, ...);
  /** Log an ERROR message */
  static void logERROR(const char* msg, ...);
  /** Log a WARNING */
  static void logWARNING(const char* msg, ...);
  /** Log a INFO message */
  static void logINFO(const char* msg, ...);
  /** Log a DEBUG message */
  static void logDEBUG(const char* msg, ...);

private:
  /** Attribute to save the logging level desired */
  static Level _levelFilter;


  /** Translate the given encoded level to an string */
  static const char* translateToString(Level level);

  /** Common function to use by the specific methods */
  static void log(Level level, const char* msg);
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
