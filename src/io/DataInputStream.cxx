/*           D A T A I N P U T S T R E A M . C X X
 * BRL-CAD
 *
 * Copyright (c) 1997-2008 United States Government as represented by
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

/** @file DataInputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "io/DataInputStream.h"
#include "io/EOFException.h"
#include "io/PushbackInputStream.h"
#include "lang/NullPointerException.h"

#define MAX_BYTES_PER_CHARACTER	8

DataInputStream::DataInputStream(InputStream& in) : FilterInputStream(in)
{
  _pin = &in;
  _del = false;
}

DataInputStream::~DataInputStream()
{

  if (_del)
    {
      delete _pin;
      _pin = 0;
    }
}

bool DataInputStream::readBoolean() throw (IOException)
{
  register int b = _pin->read();

  if (b < 0)
    throw EOFException();

  return (b != 0);
}

Byte DataInputStream::readByte() throw (IOException)
{
  return static_cast<Byte>(this->readUByte());
}

uByte DataInputStream::readUByte() throw (IOException)
{
  register int b = _pin->read();

  if (b < 0)
    throw EOFException();

  return static_cast<uByte>(b);
}



Short DataInputStream::readShort() throw (IOException)
{
  return static_cast<Short>(this->readUShort());
}

uShort DataInputStream::readUShort() throw (IOException)
{
  register uInt tmp = 0, rc;

  for (register unsigned i = 0; i < 2; ++i)
    {
      if ((rc = _pin->read()) < 0)
	throw EOFException();

      tmp = (tmp << 8) + rc;
    }

  return tmp;
}



uByte DataInputStream::readChar() throw (IOException)
{
  return this->readUByte();
}

String DataInputStream::readString(uInt strLen) throw (IOException)
{
	String out = "";

	for (uInt i = 0; i < strLen; ++i)
	  {
	    out += this->readChar();
	  }

	return out;
}


Int DataInputStream::readInt() throw (IOException)
{
  return static_cast<Int>(this->readUInt());
}

uInt DataInputStream::readUInt() throw (IOException)
{
  register uInt tmp = 0;
  register int rc;

  for (register unsigned i = 0; i < 4; ++i)
    {
      if ((rc = _pin->read()) < 0)
	throw EOFException();

      tmp = (tmp << 8) + rc;
    }

  return tmp;
}


Long DataInputStream::readLong() throw (IOException)
{
  return static_cast<uLong>(this->readULong());
}

uLong DataInputStream::readULong() throw (IOException)
{
  register uLong tmp = 0;
  register int rc;

  for (register unsigned i = 0; i < 8; ++i)
    {
      if ((rc = _pin->read()) < 0)
	throw EOFException();

      tmp = (tmp << 8) + rc;
    }

  return tmp;
}


float DataInputStream::readFloat() throw (IOException)
{
//Need to route this through ntohf
  float f = 0.0;
  uByte* pf = (uByte*) &f;
  uByte b;

  for (uInt i = 0; i < 4; ++i)
    {
      *pf = this->readUByte();
      *pf++;
    }
  return f;
}

double DataInputStream::readDouble() throw (IOException)
{
//Need to route this through ntohd
  double d = 0.0;
  uByte* pd = (uByte*) &d;
  uByte b;

  for (uInt i = 0; i < 8; ++i)
    {
      *pd = this->readUByte();
      *pd++;
    }
  return d;
}








String* DataInputStream::readLine() throw (IOException)
{
  String* result = new String();

  readLine(*result);

  return result;
}

void DataInputStream::readLine(String& line) throw (IOException)
{


  char  target_buffer[1];
  char* target = target_buffer;
  const char* target_limit = target_buffer+1;
  char  source_buffer[MAX_BYTES_PER_CHARACTER];
  const char* source = source_buffer;
  char* source_limit = source_buffer;

  bool cr = false;

  int ch;

  // clear the line
  line.clear();

  do
    {
      ch = _pin->read();

      if (ch >= 0)
	{
	  if ((source_limit - source_buffer) == MAX_BYTES_PER_CHARACTER)
	    throw IOException("fubar in readLine");

	  *(source_limit++) = (uByte) ch;
	}



      if (target == target_limit)
	{
	  // we got a whole character from the converter
	  if (cr)
	    {
	      // last character read was ASCII <CR>; is this one a <LF>?
	      if (target_buffer[0] != 0x0A)
		{
		  // unread the right number of uBytes 
		  PushbackInputStream* p = dynamic_cast<PushbackInputStream*>(_pin);
		  if (p)
		    p->unread((const uByte*) source_buffer, 0, source-source_buffer);
		  else
		    throw IOException("fubar in dynamic_cast");
		}
	      // we're now officially at the end of the line
	      break;
	    }

	  // did we get an ASCII <LF>?
	  if (target_buffer[0] == 0x0A)
	    break;

	  // did we get an ASCII <CR>?
	  if (target_buffer[0] == 0x0D)
	    {
	      cr = true;

	      // the next character may be a <LF> but if not we'll have to 'unread' it
	      if (!_del)
		{
		  // lazy push
		  _pin = new PushbackInputStream(in, MAX_BYTES_PER_CHARACTER);
		  _del = true;
		}
	    }
	  else
	    {
	      // append character to string and reset pointers
	      source = source_limit = source_buffer;
	      line.append((const char*)*(target = target_buffer));
	    }
	}
    } while (ch >= 0);
}

void DataInputStream::readFully(uByte* data, size_t offset, size_t length) throw (IOException)
{
  if (!data)
    throw NullPointerException();

  size_t total = 0;

  while (total < length)
    {
      int rc = _pin->read(data, offset+total, length-total);
      if (rc < 0)
	throw EOFException();
      total += rc;
    }
}

void DataInputStream::readFully(array<uByte>& b) throw (IOException)
{
  readFully(b.data(), 0, b.size());
}

off_t DataInputStream::skipBytes(off_t n) throw (IOException)
{
  off_t total = 0, rc;

  while ((total < n) && ((rc = _pin->skip(n - total)) > 0))
    total += rc;

  return total;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
