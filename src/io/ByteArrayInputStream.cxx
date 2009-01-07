/*           B Y T E A R R A Y I N P U T S T R E A M . C X X
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

/** @file ByteArrayInputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "io/ByteArrayInputStream.h"
#include "lang/NullPointerException.h"

ByteArrayInputStream::ByteArrayInputStream(const array<uByte>& b) : _buf(b)
{
	_count = _buf.size();
	_mark = 0;
	_pos = 0;
}

ByteArrayInputStream::ByteArrayInputStream(const uByte* data, size_t offset, size_t length) : _buf(data+offset, length)
{
	_count = _buf.size();
	_mark = 0;
	_pos = 0;
}

ByteArrayInputStream::~ByteArrayInputStream()
{
}

off_t ByteArrayInputStream::available() throw (IOException)
{
	return (off_t)(_count - _pos);
}

void ByteArrayInputStream::close() throw (IOException)
{
}

void ByteArrayInputStream::mark(off_t readlimit) throw ()
{
	_mark = _pos;
}

bool ByteArrayInputStream::markSupported() throw ()
{
	return true;
}

uInt ByteArrayInputStream::read() throw (IOException)
{
	register int rc;
	rc = (_pos < _count) ? _buf[_pos++] : -1;
	return rc;
}

uInt ByteArrayInputStream::read(uByte* data, size_t offset, size_t length) throw (IOException)
{
	if (!data)
		throw NullPointerException();

	if (_pos >= _count)
	{
		return -1;
	}

	if (_pos + length > _count)
		length = _count - _pos;

	if (length == 0)
	{
		return 0;
	}

	memcpy(data+offset, _buf.data()+_pos, length);
	_pos += length;


	return length;
}

uInt ByteArrayInputStream::read(array<uByte>& b) throw (IOException)
{
	return read(b.data(), 0, b.size());
}

void ByteArrayInputStream::reset() throw (IOException)
{
	_pos = _mark;
}

off_t ByteArrayInputStream::skip(off_t n) throw (IOException)
{
	if (_pos + n > _count)
		n = _count - _pos;
	_pos += n;
	return n;
}

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
