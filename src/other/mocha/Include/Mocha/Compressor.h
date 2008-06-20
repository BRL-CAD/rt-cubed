/*
-----------------------------------------------------------------------------
This source file is part of Mocha
For the latest info, see http://www.rightbraingames.com/

Copyright (c) 2000-2007 Right Brain Games Inc.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

This software may also be used under the terms of a separate unrestricted license,
provided that you have obtained such a license from Right Brain Games Inc.
-----------------------------------------------------------------------------
*/

#ifndef MOCHA_COMPRESSOR_H
#define MOCHA_COMPRESSOR_H

#include "zlib.h"

namespace Mocha
{

class Compressor
{
private:
	z_stream mInflateStream;

	z_stream mDeflateStream;

public:
	Compressor( );

	~Compressor( );

	void init( );

	size_t compress( const void* vIn, size_t vInSize, void* vOut, size_t vOutSize );

	size_t decompress( const void* vIn, size_t vInSize, void* vOut, size_t vOutSize );
};

}

#endif
