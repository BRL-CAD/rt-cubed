/*             P U S H B A C K I N P U T S T R E A M . C X X
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

/** @file PushBackInputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#include "io/PushbackInputStream.h"
#include "lang/NullPointerException.h"

using ibme::io::PushbackInputStream;

PushbackInputStream::PushbackInputStream(InputStream& in, size_t size) : FilterInputStream(in), buf(size)
{
	_closed = false;
	pos = 0;
}

PushbackInputStream::~PushbackInputStream()
{
}

off_t PushbackInputStream::available() throw (IOException)
{
	if (_closed)
		throw IOException("Stream closed");

	return in.available() + (buf.size() - pos);
}

void PushbackInputStream::close() throw (IOException)
{
	if (!_closed)
	{
		in.close();
		_closed = true;
	}
}

int PushbackInputStream::read() throw (IOException)
{
	if (_closed)
		throw IOException("Stream closed");

	if (pos < buf.size())
		return buf[pos++];

	return in.read();
}

bool PushbackInputStream::markSupported() throw ()
{
	return false;
}

int PushbackInputStream::read(uByte* data, size_t offset, size_t length) throw (IOException)
{
	if (!data)
		throw ibme::lang::NullPointerException();

	if (_closed)
		throw IOException("Stream closed");

	if (length == 0)
		return 0;

	size_t buffered = buf.size() - pos;

	if (buffered > 0)
	{
		if (length < buffered)
			buffered = length;

		memcpy(data+offset, buf.data()+pos, buffered);

		pos += buffered;
		offset += buffered;
		length -= buffered;
	}

	if (length > 0)
	{
		int rc = in.read(data, offset, length);
		if (rc < 0)
			if (buffered == 0)
				return -1; // nothing in buffer and nothing read
			else
				return buffered; // something in buffer and nothing read

		return buffered + rc; // something in buffer and something read
	}

	return buffered; // everything was in buffer
}

off_t PushbackInputStream::skip(off_t n) throw (IOException)
{
	if (_closed)
		throw IOException("Stream closed");

	if (n == 0)
		return 0;

	size_t canskip = buf.size() - pos;

	if (canskip > 0)
	{
		if (n < canskip)
		{
			// more in buffer than we need to skip
			canskip = n;
		}
		pos += canskip;
		n -= canskip;
	}

	if (n > 0)
	{
		// apparently we didn't have enough in the buffer
		canskip += in.skip(n);
	}

	return canskip;
}

void PushbackInputStream::unread(uByte b) throw (IOException)
{
	if (_closed)
		throw IOException("Stream closed");

	if (pos == 0)
		throw IOException("Pushback buffer is full");

	buf[--pos] = b;
}

void PushbackInputStream::unread(const array<uByte>& b) throw (IOException)
{
	unread(b.data(), 0, b.size());
}

void PushbackInputStream::unread(const uByte* data, size_t offset, size_t length) throw (IOException)
{
	if (!data)
		throw ibme::lang::NullPointerException();

	pos -= length;

	memcpy(buf.data()+pos, data+offset, length);
}
