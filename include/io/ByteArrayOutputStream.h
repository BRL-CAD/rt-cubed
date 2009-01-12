/*           B Y T E A R R A Y O U T P U T S T R E A M . H
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

#include "io/OutputStream.h"

	    
	class ByteArrayOutputStream : public OutputStream
	{

	protected:

		array<uByte> buf;
		size_t    count;
	public:

		ByteArrayOutputStream();
		ByteArrayOutputStream(size_t size);
		virtual ~ByteArrayOutputStream();
			void reset() throw ();
		size_t size() throw ();
		array<uByte>* toByteArray();
		void toByteArray(array<uByte>& b);
		void toByteArray(uByte* data, size_t offset, size_t length);
		void writeTo(OutputStream& out) throw (IOException);
			virtual void close() throw (IOException);
		virtual void flush() throw (IOException);
		virtual void write(uByte b) throw (IOException);
		virtual void write(const uByte* data, size_t offset, size_t length) throw (IOException);
		virtual void write(const array<uByte>& b) throw (IOException);
	};

#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
