/*                     I N P U T S T R E A M . C X X
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

/** @file InputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */




#include "io/InputStream.h"
#include "lang/NullPointerException.h"

using ibme::io::InputStream;

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

int InputStream::read(array<uint8_t>& b) throw (IOException)
{
	return read(b.data(), 0, b.size());
}

int InputStream::read(uint8_t* data, size_t offset, size_t length) throw (IOException)
{
	if (!data)
		throw ibme::lang::NullPointerException();

	int b = read();
	if (b < 0)
		return -1;

	data[offset] = (uint8_t) b;

	size_t i = 1;
	try
	{
		while (i < length)
		{
			b = read();
			if (b < 0)
				break;
			data[offset+i++] = (uint8_t) b;
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

	uint8_t skip[2048];

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
