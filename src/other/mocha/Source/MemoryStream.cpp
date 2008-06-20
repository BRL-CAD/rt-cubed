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

#include "Mocha/MemoryStream.h"

namespace Mocha
{

//--------------------------------
MemoryStream::MemoryStream( size_t vSize )
: mBuffer( 0 ), mBufferSize( 0 ), mDataSize( 0 ), mDataPos( 0 )
{
	setData( 0, vSize );
}

//--------------------------------
MemoryStream::MemoryStream( const char* vBuffer, size_t vSize )
: mBuffer( 0 ), mBufferSize( 0 ), mDataSize( 0 ), mDataPos( 0 )
{
	setData( vBuffer, vSize );
}

//--------------------------------
MemoryStream::~MemoryStream( )
{
	if ( mBuffer )
		::free( mBuffer );
}

//--------------------------------
size_t MemoryStream::writeData( const void* vData, size_t vSize )
{
	// Make sure we have enough room

	if ( (mDataPos + vSize) > mBufferSize )
	{
		mBufferSize = (mBufferSize * 2) + vSize;
		mBuffer = (char*)realloc( mBuffer, mBufferSize );
	}

	// Copy data to buffer

	memcpy( mBuffer + mDataPos, vData, vSize );

	// Increase pointers

	mDataPos += vSize;
	if ( mDataPos > mDataSize )
		mDataSize = mDataPos;

	return vSize;
}

//--------------------------------
size_t MemoryStream::readData( void* vData, size_t vSize ) const
{
	// Calculate the number of bytes that can be read

	size_t end = mDataPos + vSize;
	if ( end >= mDataSize )
		vSize -= (end - mDataSize);

	// Copy data

	memcpy( vData, mBuffer + mDataPos, vSize );

	// Increase pointers

	mDataPos += vSize;
	return vSize;
}

//--------------------------------
void MemoryStream::seek( size_t vPosition ) const
{
	// Adjust data stream position

	mDataPos = vPosition;

	// Make sure stream position is within range

	if ( mDataPos > mDataSize )
		mDataPos = mDataSize;
}

//--------------------------------
size_t MemoryStream::getPosition( ) const
{
	return mDataPos;
}

//--------------------------------
void MemoryStream::setData( const char* vBuffer, size_t vSize )
{
	if ( mBuffer )
	{
		::free( mBuffer );

		mBufferSize = 0;
		mBuffer = 0;
	}

	mDataSize = vSize;
	mDataPos = 0;

	if ( vSize > 0 )
	{
		mBuffer = (char*)malloc( vSize );
		mBufferSize = vSize;

		if ( vBuffer )
			memcpy( mBuffer, vBuffer, vSize );
	}
}

//--------------------------------
const char* MemoryStream::getData( ) const
{
	return mBuffer;
}

//--------------------------------
bool MemoryStream::getEndOfStream( ) const
{
	return ( mDataPos >= mDataSize );
}

//--------------------------------
size_t MemoryStream::getSize( ) const
{
	return mDataSize;
}

//--------------------------------
void MemoryStream::reset( )
{
	mDataSize = 0;
	mDataPos = 0;
}

//--------------------------------
void MemoryStream::free( )
{
	if ( mBuffer )
	{
		::free( mBuffer );

		mBufferSize = 0;
		mBuffer = 0;
	}

	reset( );
}

}
