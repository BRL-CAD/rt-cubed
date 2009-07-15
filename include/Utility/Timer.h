/*
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
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
/** @file Timer.h
 *
 *	Description:
 *
 *	$HeadURL: $
 *	$Date$
 *	$Revision$
 *	$Author$ 
 *
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

namespace Utility {

  /** Low-resolution (hundredth of a second) timer class
   */
  class Timer
  {
  protected:
    bool _running;
    bool _started;
    clock_t _start;
    double _accumulated;
    
    double elapsedSinceStart();

  public:
    Timer();
    Timer(const Timer& timer);
    ~Timer();

    void start();
    void stop();
    void reset();

    double elapsed();

    bool running();
  };

}


#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
