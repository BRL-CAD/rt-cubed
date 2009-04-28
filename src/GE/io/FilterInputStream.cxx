/*             F I L T E R I N P U T S T R E A M . C X X
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

/** @file FilterInputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "GE/io/FilterInputStream.h"

FilterInputStream::FilterInputStream(InputStream& in) : in(in)
{
}

FilterInputStream::~FilterInputStream()
{
}

off_t FilterInputStream::available() throw (IOException)
{
	return in.available();
}

void FilterInputStream::close() throw (IOException)
{
	in.close();
}

void FilterInputStream::mark(off_t readlimit) throw ()
{

	in.mark(readlimit);

}

bool FilterInputStream::markSupported() throw ()
{
	return in.markSupported();
}

unsigned int FilterInputStream::read() throw (IOException)
{
	return in.read();
}

unsigned int FilterInputStream::read(unsigned char* data, size_t offset, size_t len) throw (IOException)
{
	return in.read(data, offset, len);
}

unsigned int FilterInputStream::read(array<unsigned char>& b) throw (IOException)
{
	return in.read(b);
}

void FilterInputStream::reset() throw (IOException)
{

	in.reset();

}

off_t FilterInputStream::skip(off_t n) throw (IOException)
{
	return in.skip(n);
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
