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

#include <cstdarg>
#include <ctime>
#include <cstdio>
#include <string>

#include "Logger.h"

using namespace std;

// Max length for log messages
const int LOGSTR_LENGTH = 255;
// Macro to parse printf-like arguments of a method into fixed string
#define VARARG_PARSE() \
  va_list arg;\
  va_start(arg, msg);\
  char formatBuffer[LOGSTR_LENGTH] = { 0 };\
  vsnprintf(formatBuffer, sizeof(formatBuffer), msg, arg);\
  va_end(arg);


Logger::Level Logger::_levelFilter = Logger::DEBUG;

void Logger::setLevelFilter(Level level)
{
  _levelFilter = level;
}

void Logger::logDEBUG(const char* msg, ...)
{
  VARARG_PARSE();
  log(Logger::DEBUG, formatBuffer);
}

void Logger::logINFO(const char* msg, ...)
{
  VARARG_PARSE();
  log(Logger::INFO, formatBuffer);
}

void Logger::logWARNING(const char* msg, ...)
{
  VARARG_PARSE();
  log(Logger::WARNING, formatBuffer);
}

void Logger::logERROR(const char* msg, ...)
{
  VARARG_PARSE();
  log(Logger::ERROR, formatBuffer);
}

void Logger::logFATAL(const char* msg, ...)
{
  VARARG_PARSE();
  log(Logger::FATAL, formatBuffer);
}

void Logger::log(Level level, const char* msg)
{
  // log it only if it's equal or above the configured level
  if (level >= _levelFilter) {
    char ts[sizeof("YYYYmmdd HH:MM:SS")];
    time_t now = time(0);
    strftime(ts, sizeof(ts), "%Y%m%d %H:%M:%S", localtime(&now));
    char fullMsg[LOGSTR_LENGTH] = { 0 };
    snprintf(fullMsg, sizeof(fullMsg),
	     "%s :: %s :: %s\n", ts, translateToString(level), msg);
    fprintf(stderr, fullMsg);
  }
}

const char* Logger::translateToString(Level level)
{
  switch (level) {
    case DEBUG:
      return "DEBUG";
    case INFO:
      return "INFO";
    case WARNING:
      return "WARNING";
    case ERROR:
      return "ERROR";
    case FATAL:
      return "FATAL";
    default:
      return "INVALID LEVEL";
  }
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
