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

#ifndef MOCHA_BUFFER_H
#define MOCHA_BUFFER_H

#include <stdlib.h>

#include "Mocha/Platform.h"

namespace Mocha
{

//--------------------------------
/// Wrapper class around a dynamically allocated buffer of data
class Buffer
{
protected:
	int8* mData;

	size_t mSize;

public:
	inline Buffer( )
		: mSize( 0 ), mData( 0 )
	{
		// ...
	}

	inline Buffer( size_t vSize )
	{
		mData = (char*)realloc( 0, vSize );
		mSize = vSize;
	}

	inline ~Buffer( )
	{
		free( );
	}

	inline void allocate( size_t vSize )
	{
		if ( vSize != mSize )
		{
			mData = (char*)realloc( mData, vSize );
			mSize = vSize;
		}
	}

	inline void grow( size_t vSize )
	{
		mData = (char*)realloc( mData, mSize + vSize );
		mSize += vSize;
	}

	inline void cut( size_t vAmount )
	{
		int nsize = (int)(mSize - vAmount);

		if ( nsize <= 0 )
		{
			if ( mData )
				::free( mData );

			mData = 0;
			mSize = 0;
		}
		else
		{
			char* tmp = (char*)malloc( nsize );
			memcpy( tmp, mData + vAmount, nsize );
			::free( mData );

			mSize = nsize;
			mData = tmp;
		}
	}

	inline void append( void* vBuffer, size_t vSize )
	{
		size_t size = mSize;
		grow( vSize );

		memcpy( mData + size, vBuffer, vSize );
	}

	inline void copy( const char* vData, size_t vSize, size_t vOffset )
	{
		// Copy data into this buffer
		memcpy( mData + vOffset, vData, vSize );
	}

	inline void setCopy( const char* vData, size_t vSize )
	{
		if ( mSize != vSize )
		{
			mData = (char*)realloc( mData, vSize );
			mSize = vSize;
		}

		memcpy( mData, vData, vSize );
	}

	inline void setCopy( const Buffer& vOther )
	{
		setCopy( vOther.get( ), vOther.getSize( ) );
	}

	inline size_t getSize( ) const
	{
		return mSize;
	}

	inline void fill( char value )
	{
		memset( mData, value, getSize( ) );
	}

	inline void free( )
	{
		if ( mData )
		{
			::free( mData );

			mData = 0;
			mSize = 0;
		}
	}

	inline char* get( ) const
	{
		return mData;
	}

	inline operator char* ( ) const
	{
		return mData;
	}
};

}

#endif
