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
/** @file Date.h
 *
 *	Description:
 *
 *	$HeadURL: $
 *	$Date$
 *	$Revision$
 *	$Author$ 
 *
 */
 
#ifndef _DATE_H_
#define _DATE_H_

#include <string>

namespace Utility {

  /** Generic representation of a date
   */
  class Date
  {
  protected:
  public:
    Date();
    Date(int year, unsigned month, unsigned day);
    Date(const Date& date);
    Date(const std::string date);
    ~Date();

    std::string string();
    Date& operator=(Date date);
    Date& operator+=(Date date);
    Date& operator-=(Date date);
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
