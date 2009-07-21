/*               D A T A I N P U T S T R E A M . H
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
/** @file DataInputStream.h
 *
 * Brief description
 *
 */

#ifndef __DATAINPUTSTREAM_H__
#define __DATAINPUTSTREAM_H__

#include "GE/io/DataInput.h"
#include "GE/io/FilterInputStream.h"

    class DataInputStream : public FilterInputStream, public DataInput
    {
    private:
      bool _del;
      InputStream* _pin;

    public:
      DataInputStream(InputStream& in);
      virtual ~DataInputStream();

      virtual void readFully(unsigned char* data, size_t offset, size_t length) throw (IOException);
      virtual void readFully(array<unsigned char>& b) throw (IOException);

      virtual bool readBoolean() throw (IOException);

      virtual char readChar() throw (IOException);
      virtual unsigned char readUChar() throw (IOException);

      virtual short readShort() throw (IOException);
      virtual unsigned short readUShort() throw (IOException);

      virtual int readInt() throw (IOException);
      virtual unsigned int readUInt() throw (IOException);

      virtual long readLong() throw (IOException);
      virtual unsigned long readULong() throw (IOException);

      virtual float readFloat() throw (IOException);
      virtual double readDouble() throw (IOException);

      virtual std::string readString() throw (IOException);

      virtual std::string* readLine() throw (IOException);
      virtual void readLine(std::string& line) throw (IOException);


      virtual off_t skipBytes(off_t n) throw (IOException);
    };

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
