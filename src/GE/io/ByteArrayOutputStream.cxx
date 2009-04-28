/*           B Y T E A R R A Y O U T P U T S T R E A M . C X X
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

/** @file ByteArrayOutputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GE/io/ByteArrayOutputStream.h"
#include "GE/exception/NullPointerException.h"

ByteArrayOutputStream::ByteArrayOutputStream() : buf(32)
{
  count = 0;
}

ByteArrayOutputStream::ByteArrayOutputStream(size_t size) : buf(size)
{
  count = 0;
}

ByteArrayOutputStream::~ByteArrayOutputStream()
{
}

void ByteArrayOutputStream::reset() throw ()
{
  count = 0;
}

size_t ByteArrayOutputStream::size() throw ()
{
  return count;
}

array<unsigned char>* ByteArrayOutputStream::toCharArray()
{
  array<unsigned char>* result = new array<unsigned char>();

  this->toCharArray(*result);

  return result;
}

void ByteArrayOutputStream::toCharArray(array<unsigned char>& b)
{
  b.resize(count);
  memcpy(b.data(), buf.data(), count);
}

void ByteArrayOutputStream::toCharArray(unsigned char* data, size_t offset, size_t length)
{
  if (!data)
    throw NullPointerException();
  memcpy(data+offset, buf.data(), length < count ? length : count);

}
void ByteArrayOutputStream::close() throw (IOException)
{
}

void ByteArrayOutputStream::flush() throw (IOException)
{
}

void ByteArrayOutputStream::write(unsigned char b) throw (IOException)
{
  size_t newcount = count+1;
  size_t actualsz = buf.size();

  if (actualsz < newcount)
    {
      if (actualsz == 0)
	buf.resize(32);
      else
	buf.resize(actualsz << 1);
    }

  buf[count++] = b;
}

void ByteArrayOutputStream::write(const unsigned char* data, size_t offset, size_t length) throw (IOException)
{
  if (length)
    {
      if (!data)
	throw NullPointerException();

      size_t newcount = count + length;
      size_t actualsz = buf.size();

      if (newcount > actualsz)
	{
	  buf.resize(newcount > (actualsz << 1) ? newcount : (actualsz << 1));
	}
      memcpy(buf.data()+count, data, length);
      count += length;

    }
}

void ByteArrayOutputStream::write(const array<unsigned char>& b) throw (IOException)
{
  write(b.data(), 0, b.size());
}

void ByteArrayOutputStream::writeTo(OutputStream& out) throw (IOException)
{
  if (count)
    {
      out.write(buf.data(), 0, count);
    }
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8