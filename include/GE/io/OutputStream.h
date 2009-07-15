/*                  O U T P U T S T R E A M . H
 * BRL-CAD
 *
 * Copyright (c) 2009 United States Government as represented by
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
/** @file OutputStream.h
 *
 * Brief description
 *
 */

#ifndef _OUTPUTSTREAM_H_
#define _OUTPUTSTREAM_H_

#include "common/array.h"
#include "GE/exception/IOException.h"
#include "iBME/Object.h"

class OutputStream : public Object
{
public:
  virtual ~OutputStream() {};

  virtual void close() throw (IOException);
  virtual void flush() throw (IOException);
  virtual void write(unsigned char b) throw (IOException) = 0;
  virtual void write(const unsigned char* data, size_t offset, size_t length) throw (IOException);
  virtual void write(const array<unsigned char>& b) throw (IOException);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
