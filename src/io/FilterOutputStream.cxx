/*             F I L T E R O U T P U T S T R E A M . C X X
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

/** @file FilterOutputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */



#include "io/FilterOutputStream.h"

using ibme::io::FilterOutputStream;

FilterOutputStream::FilterOutputStream(OutputStream& out) : out(out)
{
}

FilterOutputStream::~FilterOutputStream()
{
}

void FilterOutputStream::close() throw (IOException)
{
	try
	{
		flush();
	}
	catch (IOException)
	{
		// ignore
	}
	out.close();
}

void FilterOutputStream::flush() throw (IOException)
{
	out.flush();
}

void FilterOutputStream::write(uByte b) throw (IOException)
{
	out.write(b);
}

void FilterOutputStream::write(const uByte* data, size_t offset, size_t len) throw (IOException)
{
	out.write(data, offset, len);
}

void FilterOutputStream::write(const array<uByte>& b) throw (IOException)
{
	out.write(b.data(), 0, b.size());
}
