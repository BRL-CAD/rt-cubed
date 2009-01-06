
/*             F I L T E R O U T P U T S T R E A M . H
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

/** @file FilterOutputStream.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */



#ifndef _CLASS_FILTEROUTPUTSTREAM_H
#define _CLASS_FILTEROUTPUTSTREAM_H

#ifdef __cplusplus

#include "io/OutputStream.h"


namespace ibme {
	namespace io {

		class  FilterOutputStream : public OutputStream
		{
		protected:
			OutputStream& out;

		public:
			FilterOutputStream(OutputStream& out);
			virtual ~FilterOutputStream();

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
