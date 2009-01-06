/*             P U S H B A C K I N P U T S T R E A M . H
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

/** @file PushBackInputStream.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */
#ifndef _PUSHBACKINPUTSTREAM_H_
#define _PUSHBACKINPUTSTREAM_H_

#ifdef __cplusplus

#include "io/FilterInputStream.h"

namespace ibme {
	namespace io {
		class  PushbackInputStream : public FilterInputStream
		{
		private:
			bool _closed;

		protected:
			array<uint8_t> buf;
			size_t pos;

		public:
			PushbackInputStream(InputStream& in, size_t size = 1);
			virtual ~PushbackInputStream();

			virtual off_t available() throw (IOException);
			virtual void close() throw (IOException);
			virtual bool markSupported() throw ();
			virtual int read() throw (IOException);
			virtual int read(uint8_t* data, size_t offset, size_t length) throw (IOException);
			virtual off_t skip(off_t n) throw (IOException);

			void unread(uint8_t) throw (IOException);
			void unread(const uint8_t* data, size_t offset, size_t length) throw (IOException);
			void unread(const array<uint8_t>& b) throw (IOException);
		};
	}
}

#endif

#endif
