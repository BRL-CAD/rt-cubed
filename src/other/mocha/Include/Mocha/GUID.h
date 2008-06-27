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

#ifndef MOCHA_GUID_H
#define MOCHA_GUID_H

#include <string.h>
#include "Mocha/Platform.h"

namespace Mocha
{

/// A globally unique identifier. This can be used to generate a 128 bit unique ID for objects
class MOCHA_EXPORT GUID
{
private:
	union
	{
		char mData[16];
		unsigned int mIntegers[4];
	};

	int8 getHexValue( char t );

public:
	/// Constructor. NOTE: This does not generate the GUID, it only initializes the class. Call generate to create a unique ID.
	GUID( );

	/// Copy constructor
	/*! \param vOther The other GUID to copy */
	GUID( const GUID& vOther );

	/// Set constructor
	/*! \param vOther The other GUID to copy */
	GUID( const String& vString );

	/// Destructor
	~GUID( );

	/// Returns the bytes of the GUID
	/*! \return The 16 byte array of GUID data */
	const char* getBytes( ) const;

	/// Resets the GUID
	void reset( );

	/// Generates a new globally unique GUID
	void generate( );

	/// Tests to see if the GUID is valid
	/*! \return True if the GUID is valid, false if not */
	bool isValid( ) const;

	/// Gets the GUID as a string
	/*! \return The GUID, converted to a string */
	String getString( ) const;

	/// Sets the GUID from a string
	void setString( const Mocha::String& vString );

	/// Equal operator
	inline bool operator == ( const GUID& vOther ) const
	{
		return ( memcmp( mData, vOther.mData, sizeof( mData ) ) == 0 );
	}

	/// Not equal operator
	inline bool operator != ( const GUID& vOther ) const
	{
		return ( memcmp( mData, vOther.mData, sizeof( mData ) ) != 0 );
	}

	/// Assignment operator
	inline void operator = ( const GUID& vOther )
	{
		memcpy( mData, vOther.mData, sizeof( mData ) );
	}

	/// Less-than operator. Used for ordered mapping
	inline bool operator < ( const GUID& vOther ) const
	{
		int x;
		for ( x = 0; x < 4; x++ )
		{
			if ( mIntegers[x] != vOther.mIntegers[x] )
				return (mIntegers[x] < vOther.mIntegers[x]);
		}

		return false;
	}
};

}

#endif
