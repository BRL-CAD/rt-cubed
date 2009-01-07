/*           O U T P U T S T R E A M . H
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

/** @file OutputStream.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#ifndef _OUTPUTSTREAM_H_
#define _OUTPUTSTREAM_H_

#include "common/array.h"
#include "io/IOException.h"
#include "lang/Object.h"

class OutputStream : public ibme::lang::Object
	{
	public:
		virtual ~OutputStream() {};

		virtual void close() throw (IOException);
		virtual void flush() throw (IOException);
		virtual void write(uByte b) throw (IOException) = 0;
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
