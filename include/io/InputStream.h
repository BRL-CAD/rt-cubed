/*                     I N P U T S T R E A M . H
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

/** @file InputStream.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#ifndef _INPUTSTREAM_H_
#define _INPUTSTREAM_H_

#ifdef __cplusplus

#include "common/array.h"
#include "io/IOException.h"
#include "lang/Object.h"

namespace ibme {
	namespace io {
	  class InputStream : public ibme::lang::Object
		{
		public:
			virtual ~InputStream() {};

			virtual off_t available() throw (IOException);
			virtual void close() throw (IOException);
			virtual void mark(off_t readlimit) throw ();
			virtual bool markSupported() throw ();
			virtual int read() throw (IOException) = 0;
			virtual int read(uByte* data, size_t offset, size_t length) throw (IOException);
			virtual int read(array<uByte>& b) throw (IOException);
			virtual void reset() throw (IOException);
			virtual off_t skip(off_t n) throw (IOException);
		};
	}
}

#endif

#endif
