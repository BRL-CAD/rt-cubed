/*                 D A T A I N P U T . H
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

/** @file DataInput.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */


#ifndef _DATAINPUT_H_
#define _DATAINPUT_H_

#include "common/array.h"
#include "io/IOException.h"

    class DataInput
    {
    public:
      virtual void readFully(uByte* data, size_t offset, size_t length) = 0;
      virtual void readFully(array<uByte>& b) = 0;

      virtual bool readBoolean() throw (IOException) = 0;

      virtual Byte readByte() throw (IOException) = 0;
      virtual uByte readUByte() throw (IOException) = 0;

      virtual Short readShort() throw (IOException) = 0;
      virtual uShort readUShort() throw (IOException) = 0;

      virtual Int readInt() throw (IOException) = 0;
      virtual uInt readUInt() throw (IOException) = 0;

      virtual Long readLong() throw (IOException) = 0;
      virtual uLong readULong() throw (IOException) = 0;

      virtual float readFloat() throw (IOException) = 0;
      virtual double readDouble() throw (IOException) = 0;

      virtual uByte readChar() throw (IOException) = 0;
      virtual String readString(uInt strLen) throw (IOException) = 0;

      virtual String* readLine() throw (IOException) = 0;
      virtual void readLine(String& line) throw (IOException) = 0;


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
