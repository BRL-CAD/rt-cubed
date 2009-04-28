/*           O U T P U T S T R E A M . C X X
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

/** @file OutputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GE/io/OutputStream.h"
#include "GE/exception/NullPointerException.h"

void OutputStream::close() throw (IOException)
{
}

void OutputStream::flush() throw (IOException)
{
}

void OutputStream::write(const unsigned char* data, size_t offset, size_t length) throw (IOException)
{
	if (length)
	{
		if (!data)
			throw NullPointerException();

		for (size_t i = 0; i < length; i++)
			write(data[offset+i]);
	}
}

void OutputStream::write(const array<unsigned char>& b) throw (IOException)
{
	write(b.data(), 0, b.size());
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
