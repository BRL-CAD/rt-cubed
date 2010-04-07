/*                       T I M E R . C X X
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file Timer.cxx
 *
 * Brief description
 *
 */

// interface header
#include "Utility/Timer.h"

// XXX temp
#include <iostream>

using namespace Utility;

/* protected */

double Timer::elapsedSinceStart()
{
  if (!_started) {
    return 0.0;
  }
  return ((double)clock() - (double)_start) / (double)CLOCKS_PER_SEC;
}


/* public */

Timer::Timer() :
  _running(false),
  _started(false),
  _accumulated(0.0)
{
}


Timer::Timer(const Timer& timer)
{
  _running = timer._running;
  _started = timer._started;
  _start = timer._start;
  _accumulated = timer._accumulated;
}


Timer::~Timer()
{
}


void Timer::start()
{
  if (_running) {
    return;
  }

  _running = _started = true;
  _start = clock();
}


void Timer::stop()
{
  if (!_running) {
    return;
  }
  _running = false;

  _accumulated += elapsedSinceStart();
}


void Timer::reset()
{
  _accumulated = 0.0;
  _start = clock();
}


double Timer::elapsed()
{
  if (_running) {
    return elapsedSinceStart() + _accumulated;
  }
  return _accumulated;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
