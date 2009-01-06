/*           O U T P U T S T R E A M . C X X
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

/** @file OutputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "io/OutputStream.h"
#include "lang/NullPointerException.h"

using ibme::io::OutputStream;

void OutputStream::close() throw (IOException)
{
}

void OutputStream::flush() throw (IOException)
{
}

void OutputStream::write(const uint8_t* data, size_t offset, size_t length) throw (IOException)
{
	if (length)
	{
		if (!data)
			throw ibme::lang::NullPointerException();

		for (size_t i = 0; i < length; i++)
			write(data[offset+i]);
	}
}

void OutputStream::write(const array<uint8_t>& b) throw (IOException)
{
	write(b.data(), 0, b.size());
}
