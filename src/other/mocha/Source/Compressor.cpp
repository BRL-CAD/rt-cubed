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

#include "Mocha/Compressor.h"
#include "Mocha/Exception.h"

namespace Mocha
{

//--------------------------------
Compressor::Compressor( )
{
	// Initialize inflate

    mInflateStream.zalloc = Z_NULL;
    mInflateStream.zfree = Z_NULL;
    mInflateStream.opaque = Z_NULL;
    mInflateStream.next_in = Z_NULL;
    mInflateStream.avail_in = 0;

	if ( inflateInit( &mInflateStream ) != Z_OK )
		throw Exception( "Unable to initialize zlib inflate" );

	// Initialize deflate

    mDeflateStream.zalloc = Z_NULL;
    mDeflateStream.zfree = Z_NULL;
    mDeflateStream.opaque = Z_NULL;
    mDeflateStream.next_in = Z_NULL;
    mDeflateStream.avail_in = 0;

	if ( deflateInit( &mDeflateStream, Z_DEFAULT_COMPRESSION ) != Z_OK )
		throw Exception( "Unable to initialize zlib deflate" );
}

//--------------------------------
Compressor::~Compressor( )
{
	inflateEnd( &mInflateStream );
	deflateEnd( &mDeflateStream );
}

//--------------------------------
size_t Compressor::compress( const void* vIn, size_t vInSize, void* vOut, size_t vOutSize )
{
	mDeflateStream.avail_in = vInSize;
	mDeflateStream.avail_out = vOutSize;
	mDeflateStream.next_in = (Bytef*)vIn;
	mDeflateStream.next_out = (Bytef*)vOut;
	mDeflateStream.total_out = 0;

	int res = deflate( &mDeflateStream, Z_FINISH );
	if ( res != Z_STREAM_END )
		throw Exception( "zlib compression error" );

	return mDeflateStream.total_out;
}

//--------------------------------
size_t Compressor::decompress( const void* vIn, size_t vInSize, void* vOut, size_t vOutSize )
{
	mInflateStream.avail_in = vInSize;
	mInflateStream.avail_out = vOutSize;
	mInflateStream.next_in = (Bytef*)vIn;
	mInflateStream.next_out = (Bytef*)vOut;
	mInflateStream.total_out = 0;

	int res = inflate( &mInflateStream, Z_FINISH );
	if ( res != Z_STREAM_END )
		throw Exception( "zlib decompression error" );

	return mInflateStream.total_out;
}

}
