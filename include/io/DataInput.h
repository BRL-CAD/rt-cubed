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

#ifdef __cplusplus

#include "common/array.h"
#include "io/IOException.h"

namespace ibme {
	namespace io {

		class DataInput
		{
		public:
			virtual bool readBoolean() throw (IOException) = 0;
			virtual int8_t readByte() throw (IOException) = 0;
			virtual uint16_t readChar() throw (IOException) = 0;
			virtual void readFully(uint8_t* data, size_t offset, size_t length) = 0;
			virtual void readFully(array<uint8_t>& b) = 0;
			virtual int32_t readInt() throw (IOException) = 0;
			virtual String* readLine() throw (IOException) = 0;
			virtual void readLine(String& line) throw (IOException) = 0;
			virtual int64_t readLong() throw (IOException) = 0;
			virtual int16_t readShort() throw (IOException) = 0;
			virtual int readUnsignedByte() throw (IOException) = 0;
			virtual int readUnsignedShort() throw (IOException) = 0;
			virtual String* readUTF() throw (IOException) = 0;
			virtual void readUTF(String& str) throw (IOException) = 0;
			virtual off_t skipBytes(off_t n) throw (IOException) = 0;
		};
	}
}

#endif

#endif
