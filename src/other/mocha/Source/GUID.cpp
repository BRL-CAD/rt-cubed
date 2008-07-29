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

#include "Mocha/GUID.h"

#ifdef WIN32
#include "Windows.h"
#endif

namespace Mocha
{

//--------------------------------------------
GUID::GUID( )
{
	reset( );
}

//--------------------------------------------
GUID::GUID( const GUID& vOther )
{
	memcpy( mData, vOther.mData, sizeof( mData ) );
}

//--------------------------------------------
GUID::GUID( const String& vString )
{
	setString( vString );
}

//--------------------------------------------
GUID::~GUID( )
{
	// ...
}

//--------------------------------------------
const char* GUID::getBytes( ) const
{
	return mData;
}

//--------------------------------------------
void GUID::reset( )
{
	// Clear the GUID

	memset( mData, 0, sizeof( mData ) );
}

//--------------------------------------------
bool GUID::isValid( ) const
{
	return ( (mIntegers[0] != 0) || (mIntegers[1] != 0) || (mIntegers[2] != 0) || (mIntegers[3] != 0) );
}

//--------------------------------------------
void GUID::generate( )
{
#ifdef WIN32
	::GUID id;
	CoCreateGuid( &id );

	memcpy( mData, &id, sizeof( id ) );
#elif defined( POSIX )
	uuid_t id;
#ifdef __FreeBSD__	
	unsigned int status;		// dummy
	uuid_create(&id, &status);
#else
	uuid_generate(id);
#endif
	memcpy( mData, &id, sizeof( id ) );
#else
#error "No GUID implementation"
#endif
}

//--------------------------------------------
String GUID::getString( ) const
{
	String value;

	int a;
	for( a = 0; a < 16; a++ )
	{
		char Temp[3];

		memset( Temp, 0, 3 );
		sprintf( Temp, "%.2X", (unsigned char)mData[a] );

		value = value + String( Temp );
	}

	return value;
}

//--------------------------------------------
int8 GUID::getHexValue( char t )
{
	if( t >= '0' && t <= '9' )
	{
		return t - '0';
	}
	switch( t )
	{
	case 'a':
	case 'A':
		return 10;
	case 'b':
	case 'B':
		return 11;
	case 'c':
	case 'C':
		return 12;
	case 'd':
	case 'D':
		return 13;
	case 'e':
	case 'E':
		return 14;
	case 'f':
	case 'F':
		return 15;
	}
	return 0;
}

//--------------------------------------------
void GUID::setString( const Mocha::String& vString )
{
	// Make sure the string is the correct size

	if ( vString.size( ) != 32 )
	{
		reset( );
		return;
	}

	// Convert string into GUID

    for( int a = 0; a < 16; a ++ )
	{
		char t1 = vString[a*2];
		char t2 = vString[a*2+1];
		       
		mData[a] = (char)(getHexValue( t1 ) * 16 + getHexValue( t2 ) );
	}
}

//--------------------------------------------
String createGUID()
{
#ifdef WIN32
	::GUID GUIDStruct;
		CoCreateGuid( &GUIDStruct );
#else
	uuid_t GUIDStruct;
#ifdef __FreeBSD__	
	unsigned int status;		// dummy
	uuid_create(&GUIDStruct, &status);
#else
	uuid_generate(GUIDStruct);
#endif
#endif

	String Value;

    unsigned char Bytes[16];

	memcpy( Bytes, &GUIDStruct, sizeof( GUIDStruct ) );
	for( int a = 0; a < 16; a ++ )
	{
		char Temp[3];
		memset(Temp,0,3);
		sprintf( Temp, "%.2X", Bytes[a] );
		Value = Value + String( Temp );
	}
    
	return Value;
}

}
