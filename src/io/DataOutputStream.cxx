
/*           D A T A O U T P U T S T R E A M . C X X
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

/** @file DataOutputStream.cxx
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */



#include "io/DataOutputStream.h"

#include <iostream>

using ibme::io::DataOutputStream;

DataOutputStream::DataOutputStream(OutputStream& out) : FilterOutputStream(out)
{
	written = 0;
}

DataOutputStream::~DataOutputStream()
{
}

size_t DataOutputStream::size() const throw ()
{
	return written;
}

void DataOutputStream::write(uint8_t b) throw (IOException)
{
	out.write(b);
	written++;
}

void DataOutputStream::write(const uint8_t* data, size_t offset, size_t length) throw (IOException)
{
	if (length)
	{
		out.write(data, offset, length);
		written += length;
	}
}

void DataOutputStream::write(const array<uint8_t>& b) throw (IOException)
{
	write(b.data(), 0, b.size());
}

void DataOutputStream::writeBoolean(bool b) throw (IOException)
{
	out.write(b ? 1 : 0);
	written++;
}

void DataOutputStream::writeByte(uint8_t b) throw (IOException)
{
	out.write(b);
	written++;
}

void DataOutputStream::writeShort(int16_t s) throw (IOException)
{
	out.write((s >>  8)       );
	out.write((s      ) & 0xff);
	written += 2;
}

void DataOutputStream::writeInt(int32_t i) throw (IOException)
{
	out.write((i >> 24)       );
	out.write((i >> 16) & 0xff);
	out.write((i >>  8) & 0xff);
	out.write((i      ) & 0xff);
	written += 4;
}

void DataOutputStream::writeLong(int64_t l) throw (IOException)
{
	out.write((l >> 56)       );
	out.write((l >> 48) & 0xff);
	out.write((l >> 40) & 0xff);
	out.write((l >> 32) & 0xff);
	out.write((l >> 24) & 0xff);
	out.write((l >> 16) & 0xff);
	out.write((l >>  8) & 0xff);
	out.write((l      ) & 0xff);
	written += 8;
}

void DataOutputStream::writeChar(int32_t v) throw (IOException)
{
	out.write((v >> 8) && 0xff);
	out.write((v     ) && 0xff);
	written += 2;
}

void DataOutputStream::writeChars(const String& str) throw (IOException)
{
  const char* buffer = str.c_str();
	size_t len = str.length();

	for (size_t i = 0; i < len; i++)
	{
		out.write((buffer[i] >> 8) & 0xff);
		out.write((buffer[i]     ) & 0xff);
	}
	written += (len << 1);
}


