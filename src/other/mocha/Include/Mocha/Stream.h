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

#ifndef MOCHA_STREAM_H
#define MOCHA_STREAM_H

#include "Mocha/Platform.h"
#include "Mocha/Object.h"

namespace Mocha
{

//--------------------------------
enum SeekLocation
{
	SEEKPOS_START = 0,
	SEEKPOS_CURRENT,
	SEEKPOS_END
};

//--------------------------------
template <typename T> void WriteStream( Stream& vStream, const T& vValue ); 
template <typename T> void ReadStream( const Stream& vStream, T& vValue ); 

//--------------------------------
/// A generic stream interface for reading/writing data
class MOCHA_EXPORT Stream : public Object
{
public:
	/// Writes data to the stream
	/*! \param vData A pointer to the data to write
		\param vSize The size of the data to write
		\return The number of bytes written */
	virtual size_t writeData( const void* vData, size_t vSize ) = 0;

	/// Reads data from the stream
	/*! \param vData A pointer to the buffer to be filled with the data
		\param vSize The number of bytes to read
		\return The number of bytes read */
	virtual size_t readData( void* vData, size_t vSize ) const = 0;

	/// Templated version of read
	template <typename T>
	inline void write( const T& vValue )
	{
		WriteStream<T>( *this, vValue );
	}

	template <typename T>
	inline void read( T& vValue ) const
	{
		ReadStream<T>( *this, vValue );
	}

	/// Templated version of write
	template <typename T>
	inline T read( ) const
	{
		T tmp;
		ReadStream<T>( *this, tmp );

		return tmp;
	}

	/// Moves the stream pointer
	/*!	\param vPosition The new position to use */
	virtual void seek( size_t vPosition ) const = 0;

	/// Gets the current stream position
	/*! \return The current stream position */
	virtual size_t getPosition( ) const = 0;

	/// Gets the total number of bytes in the stream
	/*! \return The number of bytes in the stream */
	virtual size_t getSize( ) const = 0;

	/// Gets whether or not the stream pointer has reached the end of the data
	/*! \return True if the stream pointer has reached the end of the data, false if not */
	virtual bool getEndOfStream( ) const = 0;
};

//--------------------------------
template <typename T>
inline void WriteStream( Stream& vStream, const T& vValue )
{
	vStream.writeData( &vValue, sizeof( T ) );
}

//--------------------------------
template <typename T>
inline void ReadStream( const Stream& vStream, T& vValue )
{
	vStream.readData( &vValue, sizeof( T ) );
}

//--------------------------------
template <>
inline void ReadStream<String>( const Stream& vStream, String& vString )
{
	int32 size = vStream.read<int32>( );

	vString.resize( size );
	vStream.readData( (void*)vString.c_str( ), size );
}

//--------------------------------
template <>
inline void WriteStream<String>( Stream& vStream, const String& vValue )
{
	int32 size = (int32)vValue.size( );

	vStream.write<int32>( size );
	vStream.writeData( vValue.c_str( ), size );
}

//--------------------------------
template <>
inline void WriteStream<size_t>( Stream& vStream, const size_t& vValue )
{
	uint32 v = (uint32)vValue;
	vStream.writeData( &v, sizeof( v ) );
}

//--------------------------------
template <>
inline void ReadStream<size_t>( const Stream& vStream, size_t& vValue )
{
	uint32 v;
	vStream.readData( &v, sizeof( v ) );

	vValue = (size_t)v;
}

//--------------------------------
template <>
inline void WriteStream<bool>( Stream& vStream, const bool& vValue )
{
	int8 v = ( vValue != 0 ) ? 1 : 0;
	vStream.writeData( &v, sizeof( v ) );
}

//--------------------------------
template <>
inline void ReadStream<bool>( const Stream& vStream, bool& vValue )
{
	int8 v;
	vStream.readData( &v, sizeof( v ) );

	vValue = ( v != 0 );
}

//--------------------------------
template <>
inline void WriteStream<Value>( Stream& vStream, const Value& vValue )
{
	vValue.write( vStream );
}

//--------------------------------
template <>
inline void ReadStream<Value>( const Stream& vStream, Value& vValue )
{
	vValue.read( vStream );
}

}

#endif
