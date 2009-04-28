
/*           D A T A O U T P U T . H
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

/** @file DataOutput.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#ifndef _DATAOUTPUT_H_
#define _DATAOUTPUT_H_

#include "common/array.h"
#include "exception/IOException.h"

    class DataOutput
    {
    public:
      virtual void write(const array<unsigned char>& b) throw (IOException) = 0;
      virtual void write(const unsigned char* data, size_t offset, size_t length) throw (IOException) = 0;

      virtual void write(unsigned char v) throw (IOException) = 0;

      virtual void writeBoolean(const bool v) throw (IOException) = 0;

      virtual void writeUChar(const unsigned char v) throw (IOException) = 0;
      virtual void writeChar(const char v) throw (IOException) = 0;

      virtual void writeUShort(const unsigned short v) throw (IOException) = 0;
      virtual void writeShort(const short v) throw (IOException) = 0;

      virtual void writeUInt(const unsigned int v) throw (IOException) = 0;
      virtual void writeInt(const int v) throw (IOException) = 0;

      virtual void writeULong(const unsigned long v) throw (IOException) = 0;
      virtual void writeLong(const long v) throw (IOException) = 0;
	
      virtual void writeFloat(const float v) throw (IOException) = 0;
      virtual void writeDouble(const double v) throw (IOException) = 0;

      virtual void writeChar(const unsigned char v) throw (IOException) = 0;
      virtual void writeString(const std::string& s) throw (IOException) = 0;


    };

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
