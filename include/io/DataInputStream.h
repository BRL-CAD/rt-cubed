/*           D A T A I N P U T S T R E A M . H
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

/** @file DataInputStream.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#ifndef _DATAINPUTSTREAM_H_
#define _DATAINPUTSTREAM_H_

#ifdef __cplusplus

#include "io/DataInput.h"
#include "io/FilterInputStream.h"


namespace ibme {
  namespace io {
    class DataInputStream : public FilterInputStream, public DataInput
    {
    private:
      bool _del;
      InputStream* _pin;

    public:
      DataInputStream(InputStream& in);
      virtual ~DataInputStream();

      virtual void readFully(uByte* data, size_t offset, size_t length) throw (IOException);
      virtual void readFully(array<uByte>& b) throw (IOException);

      virtual bool readBoolean() throw (IOException);

      virtual Byte readByte() throw (IOException);
      virtual uByte readUByte() throw (IOException);

      virtual Short readShort() throw (IOException);
      virtual uShort readUShort() throw (IOException);

      virtual Int readInt() throw (IOException);
      virtual uInt readUInt() throw (IOException);

      virtual Long readLong() throw (IOException);
      virtual uLong readULong() throw (IOException);



      virtual uShort readChar() throw (IOException);
      virtual String readString(uInt strLen) throw (IOException);

      virtual String* readLine() throw (IOException);
      virtual void readLine(String& line) throw (IOException);

	

      virtual off_t skipBytes(off_t n) throw (IOException);
    };
  }
}

#endif

#endif
