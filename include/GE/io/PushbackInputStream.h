/*           P U S H B A C K I N P U T S T R E A M . H
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
/** @file PushbackInputStream.h
 *
 * Brief description
 *
 */

#ifndef _PUSHBACKINPUTSTREAM_H_
#define _PUSHBACKINPUTSTREAM_H_

#include "GE/io/FilterInputStream.h"

class  PushbackInputStream : public FilterInputStream
{
private:
  bool _closed;

protected:
  array<unsigned char> buf;
  size_t pos;

public:
  PushbackInputStream(InputStream& in, size_t size = 1);
  virtual ~PushbackInputStream();

  virtual off_t available() throw (IOException);
  virtual void close() throw (IOException);
  virtual bool markSupported() throw ();
  virtual unsigned int read() throw (IOException);
  virtual unsigned int read(unsigned char* data, size_t offset, size_t length) throw (IOException);
  virtual off_t skip(off_t n) throw (IOException);

  void unread(unsigned char) throw (IOException);
  void unread(const unsigned char* data, size_t offset, size_t length) throw (IOException);
  void unread(const array<unsigned char>& b) throw (IOException);
};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
