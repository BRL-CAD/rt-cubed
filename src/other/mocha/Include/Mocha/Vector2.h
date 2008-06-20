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

#ifndef MOCHA_VECTOR2_H
#define MOCHA_VECTOR2_H

#include <vector>

#include "Mocha/Math.h"
#include "Mocha/Stream.h"
#include "Mocha/Vector2.h"

namespace Mocha
{

/// A two-component floating point vector
class Vector2
{
public:
	float x;

	float y;

	inline Vector2( float vX, float vY )
		: x( vX ), y( vY )
	{
		// ...
	}

	inline Vector2( const Vector2& vOther )
		: x( vOther.x ), y( vOther.y )
	{
		// ...
	}

	inline Vector2( )
		: x( 0.0f ), y( 0.0 )
	{
		// ...
	}

	inline void translate( float vX, float vY )
	{
		x += vX;
		y += vY;
	}

	inline Vector2 operator + ( const Vector2& vOther ) const
	{
		Vector2 tmp;
		tmp.x = x + vOther.x;
		tmp.y = y + vOther.y;

		return tmp;
	}

	inline Vector2& operator += ( const Vector2& vOther )
	{
		x += vOther.x;
		y += vOther.y;

		return *this;
	}

	inline Vector2 operator - ( const Vector2& vOther ) const
	{
		Vector2 tmp;
		tmp.x = x - vOther.x;
		tmp.y = y - vOther.y;

		return tmp;
	}

	inline Vector2 operator - ( ) const
	{
		Vector2 tmp( -x, -y );
		return tmp;
	}

	inline Vector2& operator -= ( const Vector2& vOther )
	{
		x -= vOther.x;
		y -= vOther.y;

		return *this;
	}

	inline Vector2& operator = ( const Vector2& vOther )
	{
		x = vOther.x;
		y = vOther.y;

		return *this;
	}

	inline Vector2 operator * ( float v ) const
	{
		Vector2 vec;
		vec.x = x * v;
		vec.y = y * v;

		return vec;
	}

	inline Vector2 operator * ( const Vector2& v ) const
	{
		Vector2 vec;
		vec.x = x * v.x;
		vec.y = y * v.y;

		return vec;
	}

	inline Vector2& operator * ( const Vector2& v )
	{
		x *= v.x;
		y *= v.y;

		return *this;
	}

	inline Vector2 operator / ( float v ) const
	{
		Vector2 vec;
		vec.x = x / v;
		vec.y = y / v;

		return vec;
	}

	inline Vector2 operator / ( const Vector2& v ) const
	{
		Vector2 vec;
		vec.x = x / v.x;
		vec.y = y / v.y;

		return vec;
	}

	inline Vector2& operator /= ( const Vector2& v )
	{
		x /= v.x;
		y /= v.y;

		return *this;
	}

	inline float length( ) const
	{
		return (float)sqrt( x*x + y*y );
	}
	
	inline void setLength( float f )
	{
		float temp = length( );
		x *= f / temp;
		y *= f / temp;
	}

	inline float squaredLength( ) const
	{
		return x*x + y*y;
	}

	inline float distance( const Vector2& other ) const
	{
		float x1 = other.x-x;
		float y1 = other.y-y;

		return sqrt( x1*x1 + y1*y1 );				
	}

	inline float squaredDistance( const Vector2& other ) const
	{
		float x1 = other.x-x;
		float y1 = other.y-y;

		return x1*x1 + y1*y1;				
	}

	inline void lerp( const Vector2& vOther, float lerpval )
	{
		x = vOther.x + ( (x - vOther.x) * lerpval );
		y = vOther.y + ( (y - vOther.y) * lerpval );
	}

	inline void lerp( const Vector2& v0, const Vector2& v1, float lerpval )
	{
		x = v0.x + ( (v1.x - v0.x) * lerpval );
		y = v0.y + ( (v1.y - v0.y) * lerpval );
	}

	inline bool operator == ( const Vector2& vOther ) const
	{
		return ( ( x == vOther.x ) && ( y == vOther.y ) );
	}

	inline bool operator != ( const Vector2& vOther ) const
	{
		return ( ( x != vOther.x ) || ( y != vOther.y ) );
	}
};

//--------------------------------
template<>
inline void lerp<Vector2>( Vector2& result, const Vector2& value0, const Vector2& value1, float lerpval )
{
	result.lerp( value0, value1, lerpval );
}

//--------------------------------
template<>
inline void ReadStream<Vector2>( const Stream& vStream, Vector2& vValue )
{
	ReadStream<float>( vStream, vValue.x );
	ReadStream<float>( vStream, vValue.y );
}

//--------------------------------
template<>
inline void WriteStream<Vector2>( Stream& vStream, const Vector2& vValue )
{
	WriteStream<float>( vStream, vValue.x );
	WriteStream<float>( vStream, vValue.y );
}

//--------------------------------
typedef std::vector<Vector2> Vector2List;

}

#endif
