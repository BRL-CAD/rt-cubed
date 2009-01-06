/*             F I L T E R I N P U T S T R E A M . H
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

/** @file FilterInputStream.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */


#ifndef _FILTERINPUTSTREAM_H_
#define _FILTERINPUTSTREAM_H_

#ifdef __cplusplus

#include "io/InputStream.h"

namespace ibme {
	namespace io {

		class  FilterInputStream : public InputStream
		{
		protected:
			InputStream& in;

		public:
			FilterInputStream(InputStream& in);
			virtual ~FilterInputStream();

			virtual off_t available() throw (IOException);
			virtual void close() throw (IOException);
			virtual void mark(off_t) throw ();
			virtual bool markSupported() throw ();
			virtual int read() throw (IOException);
			virtual int read(uint8_t* data, size_t offset, size_t length) throw (IOException);
			virtual int read(array<uint8_t>& b) throw (IOException);
			virtual void reset() throw (IOException);
			virtual off_t skip(off_t) throw (IOException);
		};
	}
}

#endif

#endif
