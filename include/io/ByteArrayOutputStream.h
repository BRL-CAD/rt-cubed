

/*           B Y T E A R R A Y O U T P U T S T R E A M . H
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

/** @file ByteArrayOutputStream.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */


#ifndef _BYTEARRAYOUTPUTSTREAM_H_
#define _BYTEARRAYOUTPUTSTREAM_H_

#ifdef __cplusplus

#include "io/OutputStream.h"


namespace ibme {
	namespace io {
	    
		class ByteArrayOutputStream : public OutputStream
		{


		protected:
			array<uint8_t> buf;
			size_t    count;

		public:
			ByteArrayOutputStream();
			ByteArrayOutputStream(size_t size);
			virtual ~ByteArrayOutputStream();

			void reset() throw ();
			size_t size() throw ();
			array<uint8_t>* toByteArray();
			void toByteArray(array<uint8_t>& b);
			void toByteArray(uint8_t* data, size_t offset, size_t length);
			void writeTo(OutputStream& out) throw (IOException);

			virtual void close() throw (IOException);
			virtual void flush() throw (IOException);
			virtual void write(uint8_t b) throw (IOException);
			virtual void write(const uint8_t* data, size_t offset, size_t length) throw (IOException);
			virtual void write(const array<uint8_t>& b) throw (IOException);
		};
	}
}

#endif

#endif
