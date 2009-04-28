/*                     I N P U T S T R E A M . C X X
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

/** @file InputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GE/io/InputStream.h"
#include "GE/exception/NullPointerException.h"

off_t InputStream::available() throw (IOException)
{
	return 0;
}

void InputStream::close() throw (IOException)
{
}

void InputStream::mark(off_t readlimit) throw ()
{
}

bool InputStream::markSupported() throw ()
{
	return false;
}

unsigned int InputStream::read(array<unsigned char>& b) throw (IOException)
{
	return read(b.data(), 0, b.size());
}

unsigned int InputStream::read(unsigned char* data, size_t offset, size_t length) throw (IOException)
{
	if (!data)
		throw NullPointerException();

	int b = read();
	if (b < 0)
		return -1;

	data[offset] = (unsigned char) b;

	size_t i = 1;
	try
	{
		while (i < length)
		{
			b = read();
			if (b < 0)
				break;
			data[offset+i++] = (unsigned char) b;
		}
	}
	catch (IOException)
	{
		// ignore
	}
	return i;
}

off_t InputStream::skip(off_t n) throw (IOException)
{
	off_t remaining = n;

	unsigned char skip[2048];

	while (remaining > 0)
	{
		int rc = read(skip, 0, remaining > 2048 ? 2048 : remaining);
		if (rc < 0)
			break;
		remaining -= rc;
	}

	return n - remaining;
}

void InputStream::reset() throw (IOException)
{
	throw IOException("reset not supported");
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
