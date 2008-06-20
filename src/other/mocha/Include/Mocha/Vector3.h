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

#ifndef MOCHA_VECTOR3_H
#define MOCHA_VECTOR3_H

#include "Mocha/Math.h"
#include "Mocha/Stream.h"

namespace Mocha
{

/// A three-component floating point vector
class Vector3
{
public:
	float x;

	float y;

	float z;

	inline Vector3( )
		: x( 0.0f ), y( 0.0f ), z( 0.0f )
	{
		// ...
	}

	inline Vector3( float vX, float vY, float vZ )
		: x( vX ), y( vY ), z( vZ )
	{
		// ...
	}
	
	inline Vector3( const Vector3& vOther )
		: x( vOther.x ), y( vOther.y ), z( vOther.z )
	{
		// ...
	}

	inline void set( float vX, float vY, float vZ )
	{
		x = vX;
		y = vY;
		z = vZ;
	}
	
	inline Vector3 operator + ( const Vector3& other ) const
	{
		return Vector3( x+other.x, y+other.y, z+other.z );
	}
	
	inline const Vector3& operator += ( const Vector3& other )
	{
		x += other.x;
		y += other.y;
		z += other.z;
		
		return *this;
	}
	
	inline Vector3 operator - ( const Vector3& other ) const
	{
		return Vector3( x-other.x, y-other.y, z-other.z ); 
	}

	inline Vector3 operator - ( ) const
	{
		Vector3 tmp( -x, -y, -z );
		return tmp;
	}
	
	inline const Vector3& operator -= ( const Vector3& other )
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		
		return *this;
	}

	inline Vector3 operator * ( float s ) const
	{
		return Vector3( x*s, y*s, z*s );
	}
	
	inline Vector3 operator / ( const Vector3& other ) const
	{
		return Vector3( x / other.x, y / other.y, z / other.z );
	}

	inline Vector3 operator /= ( const Vector3& other )
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return (*this);
	}

	inline Vector3 operator * ( const Vector3& other ) const
	{
		return Vector3( x * other.x, y * other.y, z * other.z );
	}

	inline Vector3 operator *= ( const Vector3& other )
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return (*this);
	}

	inline Vector3 crossProduct( const Vector3& other ) const
	{
		return Vector3(
			( y * other.z ) - ( z * other.y ),
			( z * other.x ) - ( x * other.z ),
			( x * other.y ) - ( y * other.x )
		);
	}
	
	inline float operator % ( const Vector3& other ) const
	{
		return dotProduct( other );
	}

	inline float dotProduct( const Vector3& other ) const
	{
		return ( x * other.x ) + ( y * other.y ) + ( z * other.z );
	}

	inline bool isZero( ) const
	{
		if ( ( x == 0.0f ) && ( y == 0.0f ) && ( z == 0.0f ) )
			return true;

		return false;
	}
	
	inline const Vector3& operator *= ( float s )
	{
		x *= s;
		y *= s;
		z *= s;
		
		return *this;
	}

	inline const Vector3& operator /= ( float s )
	{
		x /= s;
		y /= s;
		z /= s;
		
		return *this;
	}

	inline float length( ) const
	{
		return (float)sqrt( x*x + y*y + z*z );
	}

	inline void setLength( float f )
	{
		float temp = length( );
		x *= f / temp;
		y *= f / temp;
		z *= f / temp;
	}

	inline float squaredLength( ) const
	{
		return x*x + y*y + z*z;
	}
	
	inline float distance( const Vector3& other ) const
	{
		float x1 = other.x-x;
		float y1 = other.y-y;
		float z1 = other.z-z;

		return sqrt( x1*x1 + y1*y1 + z1*z1 );		
	}

	inline float squaredDistance( const Vector3& other ) const
	{
		float x1 = other.x-x;
		float y1 = other.y-y;
		float z1 = other.z-z;

		return x1*x1 + y1*y1 + z1*z1;				
	}

	inline Vector3 midpoint( const Vector3& vOther ) const
	{
		Vector3 res;
		res.x = (x + vOther.x) / 2;
		res.y = (y + vOther.y) / 2;
		res.z = (z + vOther.z) / 2;

		return res;
	}

	inline Vector3& normalize( )
	{
		float l = length( );
		
		if ( l > TINY ) {
			x /= l;
			y /= l;
			z /= l;
		}

		return (*this);
	}

	inline void lerp( const Vector3& vOther, float lerpval )
	{
		x = vOther.x + ( (x - vOther.x) * lerpval );
		y = vOther.y + ( (y - vOther.y) * lerpval );
		z = vOther.z + ( (z - vOther.z) * lerpval );
	}

	inline void lerp( const Vector3& v0, const Vector3& v1, float lerpval )
	{
		x = v0.x + ( (v1.x - v0.x) * lerpval );
		y = v0.y + ( (v1.y - v0.y) * lerpval );
		z = v0.z + ( (v1.z - v0.z) * lerpval );
	}

	inline Vector3 operator / ( float v ) const
	{
		Vector3 tmp = *this;
		tmp.x /= v;
		tmp.y /= v;
		tmp.z /= v;

		return tmp;
	}

	inline bool isZeroLength( ) const
	{
		float sqlen = (x * x) + (y * y) + (z * z);
		return (sqlen < (1e-06 * 1e-06));
	}

	inline float getXRotation( ) const
	{
		return (float)atan2( -y, sqrt( (x * x) + (z * z) ) );
	}

	inline float getYRotation( ) const
	{
		return (float)atan2( x, z );
	}
	
	inline bool operator == ( const Vector3& other ) const
	{
		return ( ( x == other.x ) && ( y == other.y ) && ( z == other.z ) );
	}

	inline bool operator < ( const Vector3& other ) const
	{
		return ( ( x < other.x ) && ( y < other.y ) && ( z < other.z ) );
	}

	inline bool operator <= ( const Vector3& other ) const
	{
		return ( ( x <= other.x ) && ( y <= other.y ) && ( z <= other.z ) );
	}

	inline bool operator > ( const Vector3& other ) const
	{
		return ( ( x > other.x ) && ( y > other.y ) && ( z > other.z ) );
	}

	inline bool operator >= ( const Vector3& other ) const
	{
		return ( ( x >= other.x ) && ( y >= other.y ) && ( z >= other.z ) );
	}

	inline bool operator != ( const Vector3& other ) const
	{
		return ( ( x != other.x ) || ( y != other.y ) || ( z != other.z ) );
	}
	
	inline Vector3 normalizedCopy( ) const
	{
		Vector3 tmp( *this );
		tmp.normalize( );
		
		return tmp;
	}

	inline bool fuzzyCompare( float vValue, float vThreshold = 0.00001f ) const
	{
		return ( fuzzycmp( x, vValue, vThreshold ) && fuzzycmp( y, vValue, vThreshold ) && fuzzycmp( z, vValue, vThreshold ) );
	}
};

//--------------------------------
template<>
inline void lerp<Vector3>( Vector3& result, const Vector3& value0, const Vector3& value1, float lerpval )
{
	result.lerp( value0, value1, lerpval );
}

//--------------------------------
template<>
inline void ReadStream<Vector3>( const Stream& vStream, Vector3& vValue )
{
	ReadStream<float>( vStream, vValue.x );
	ReadStream<float>( vStream, vValue.y );
	ReadStream<float>( vStream, vValue.z );
}

//--------------------------------
template<>
inline void WriteStream<Vector3>( Stream& vStream, const Vector3& vValue )
{
	WriteStream<float>( vStream, vValue.x );
	WriteStream<float>( vStream, vValue.y );
	WriteStream<float>( vStream, vValue.z );
}

}

#endif
