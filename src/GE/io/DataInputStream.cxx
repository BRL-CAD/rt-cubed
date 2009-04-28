/*           D A T A I N P U T S T R E A M . C X X
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

/** @file DataInputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GE/io/DataInputStream.h"
#include "exception/EOFException.h"
#include "GE/io/PushbackInputStream.h"
#include "exception/NullPointerException.h"

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

char DataInputStream::readChar() throw (IOException)
{
  return static_cast<char>(this->readUChar());
}

unsigned char DataInputStream::readUChar() throw (IOException)
{
  register int b = _pin->read();

  if (b < 0)
    throw EOFException();

  return static_cast<unsigned char>(b);
}



short DataInputStream::readShort() throw (IOException)
{
  return static_cast<short>(this->readUShort());
}

unsigned short DataInputStream::readUShort() throw (IOException)
{
  register unsigned int tmp = 0, rc;

  for (register unsigned int i = 0; i < 2; ++i)
    {
      if ((rc = _pin->read()) < 0)
	throw EOFException();

      tmp = (tmp << 8) + rc;
    }

  return tmp;
}



std::string DataInputStream::readString() throw (IOException)
{

	unsigned int len = this->readUInt();

	std::string out = "";

	for (int i = 0; i < len; ++i)
	  {
	    out += this->readChar();
	  }

	return out;
}


int DataInputStream::readInt() throw (IOException)
{
  return static_cast<int>(this->readUInt());
}

unsigned int DataInputStream::readUInt() throw (IOException)
{
  register unsigned int tmp = 0;
  register int rc;

  for (register unsigned int i = 0; i < 4; ++i)
    {
      if ((rc = _pin->read()) < 0)
	throw EOFException();

      tmp = (tmp << 8) + rc;
    }

  return tmp;
}


long DataInputStream::readLong() throw (IOException)
{
  return static_cast<long>(this->readULong());
}

unsigned long DataInputStream::readULong() throw (IOException)
{
  register unsigned long tmp = 0;
  register int rc;

  for (register unsigned int i = 0; i < 8; ++i)
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
  unsigned char* pf = (unsigned char*) &f;
  unsigned char b;

  for (int i = 0; i < 4; ++i)
    {
      *pf = this->readUChar();
      *pf++;
    }
  return f;
}

double DataInputStream::readDouble() throw (IOException)
{
//Need to route this through ntohd
  double d = 0.0;
  unsigned char* pd = (unsigned char*) &d;
  unsigned char b;

  for (int i = 0; i < 8; ++i)
    {
      *pd = this->readUChar();
      *pd++;
    }
  return d;
}








std::string* DataInputStream::readLine() throw (IOException)
{
  std::string* result = new std::string();

  readLine(*result);

  return result;
}

void DataInputStream::readLine(std::string& line) throw (IOException)
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

	  *(source_limit++) = (unsigned char) ch;
	}



      if (target == target_limit)
	{
	  // we got a whole character from the converter
	  if (cr)
	    {
	      // last character read was ASCII <CR>; is this one a <LF>?
	      if (target_buffer[0] != 0x0A)
		{
		  // unread the right number of unsigned chars 
		  PushbackInputStream* p = dynamic_cast<PushbackInputStream*>(_pin);
		  if (p)
		    p->unread((const unsigned char*) source_buffer, 0, source-source_buffer);
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

void DataInputStream::readFully(unsigned char* data, size_t offset, size_t length) throw (IOException)
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

void DataInputStream::readFully(array<unsigned char>& b) throw (IOException)
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
