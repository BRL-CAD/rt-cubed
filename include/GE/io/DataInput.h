/*                     D A T A I N P U T . H
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
/** @file DataInput.h
 *
 * Brief description
 *
 */

#ifndef __DATAINPUT_H__
#define __DATAINPUT_H__

#include "common/array.h"
#include "GE/exception/IOException.h"

    class DataInput
    {
    public:
      virtual void readFully(unsigned char* data, size_t offset, size_t length) = 0;
      virtual void readFully(array<unsigned char>& b) = 0;

      virtual bool readBoolean() throw (IOException) = 0;

      virtual char readChar() throw (IOException) = 0;
      virtual unsigned char readUChar() throw (IOException) = 0;

      virtual short readShort() throw (IOException) = 0;
      virtual unsigned short readUShort() throw (IOException) = 0;

      virtual int readInt() throw (IOException) = 0;
      virtual unsigned int readUInt() throw (IOException) = 0;

      virtual long readLong() throw (IOException) = 0;
      virtual unsigned long readULong() throw (IOException) = 0;

      virtual float readFloat() throw (IOException) = 0;
      virtual double readDouble() throw (IOException) = 0;

      virtual std::string readString() throw (IOException) = 0;

      virtual std::string* readLine() throw (IOException) = 0;
      virtual void readLine(std::string& line) throw (IOException) = 0;


      virtual off_t skipBytes(off_t n) throw (IOException) = 0;
    };


#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
