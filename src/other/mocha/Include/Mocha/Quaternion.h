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

#ifndef MOCHA_QUATERNION_H
#define MOCHA_QUATERNION_H

#include "Mocha/Stream.h"
#include "Mocha/Vector3.h"
#include "Mocha/Math.h"

namespace Mocha
{

// Some of this code was borrowed from the Nebula Device.
// http://nebuladevice.cubik.org

/// A rotation in 3D space represented as a 4 component quaternion vector
class Quaternion
{
public:
	float x;

	float y;

	float z;

	float w;
		
	inline Quaternion( )
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
		w = 1.0;
	}
	
	inline Quaternion( float _x, float _y, float _z, float _w )
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	inline Quaternion( const Vector3& vRotation )
	{
		setRotation( vRotation );
	}
	
	inline Quaternion( const Quaternion& other )
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}
	
	inline void ident( )
	{
		x = 0.0;
		y = 0.0;
		z = 0.0;
		w = 1.0;
	}

	inline void set( float _x, float _y, float _z, float _w )
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	
	inline void scale( float s )
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
	}

	inline float norm( )
	{
		return x*x + y*y + z*z + w*w;
	}
	
	inline float magnitude( )
	{
		float n = norm( );
		if ( n > 0.0f )
			return sqrt( n );
		else
			return 0.0f;
	}
	
	inline void normalize( )
	{
		float l = magnitude( );
		if ( l > 0.0f )
			scale( 1.0f / l );
		else
			ident( );					
	}

	inline Quaternion operator * ( const Quaternion& other ) const
	{
		return Quaternion( w*other.x + x*other.w + y*other.z - z*other.y,
							w*other.y + y*other.w + z*other.x - x*other.z,
							w*other.z + z*other.w + x*other.y - y*other.x,
							w*other.w - x*other.x - y*other.y - z*other.z );
	}

	inline Quaternion& operator * ( float s )
	{
		scale( s );
		return *this;
	}

	inline bool operator == ( const Quaternion& other ) const
	{
		return ( ( x == other.x ) && ( y == other.y ) && ( z == other.z ) && ( w == other.w ) );
	}
	
	inline bool operator != ( const Quaternion& other ) const
	{
		return ( ( x != other.x ) || ( y != other.y ) || ( z != other.z ) || ( w != other.w ) );
	}
	
	inline const Quaternion& operator += ( const Quaternion& other )
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		
		return *this;
	}
	
	inline const Quaternion& operator -= ( const Quaternion& other )
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		
		return *this;
	}
	
	inline const Quaternion& operator *= ( const Quaternion& other )
	{
		float qx = w*other.x + x*other.w + y*other.z - z*other.y;
		float qy = w*other.y + y*other.w + z*other.x - x*other.z;
		float qz = w*other.z + z*other.w + x*other.y - y*other.x;
		float qw = w*other.w - x*other.x - y*other.y - z*other.z;
		
		x = qx;
		y = qy;
		z = qz;
		w = qw;

		return *this;
	}
	
	inline Vector3 rotate( const Vector3& v ) const
	{
		Quaternion q(	v.x * w + v.z * y - v.y * z,
							v.y * w + v.x * z - v.z * x,
							v.z * w + v.y * x - v.x * y,
							v.x * x + v.y * y + v.z * z	);

		return Vector3(w * q.x + x * q.w + y * q.z - z * q.y,
							w * q.y + y * q.w + z * q.x - x * q.z,
							w * q.z + z * q.w + x * q.y - y * q.x);
	}
	
	inline void setFromAxes( const Vector3& from, const Vector3& to )
	{
		Vector3 c( from * to );
		set( c.x, c.y, c.z, from % to );
		w += 1.0f;
		if( w <= TINY ) {
			if ( ( from.z * from.z ) > ( from.x * from.x ) )
				set( 0, from.z, -from.y, w );
			else 
				set( from.y, -from.x, 0, w );
		}
		
		normalize( ); 
	}

	inline void fromAxisAngle( const Vector3& axis, float angle )
	{
		float halfAngle = angle * 0.5f;
		float fsin = sin( halfAngle );

		x = fsin * axis.x;
		y = fsin * axis.y;
		z = fsin * axis.z;
		w = cos( halfAngle );
	}
	
	inline void setRotationX( float a )
	{
		float sin_a = sin( a * 0.5f );
		float cos_a = cos( a * 0.5f );

		x = sin_a;
		y = 0.0f;
		z = 0.0f;
		w = cos_a;
	}

	inline void setRotationY( float a )
	{
		float sin_a = sin( a * 0.5f );
		float cos_a = cos( a * 0.5f );

		x = 0.0f;
		y = sin_a;
		z = 0.0f;
		w = cos_a;
	}

	inline void setRotationZ( float a )
	{
		float sin_a = sin( a * 0.5f );
		float cos_a = cos( a * 0.5f );

		x = 0.0f;
		y = 0.0f;
		z = sin_a;
		w = cos_a;
	}

	inline void setRotation( const Vector3& vec )
	{
		Quaternion qx;
		Quaternion qy;
		Quaternion qz;

		qx.setRotationX( vec.x );
		qy.setRotationY( vec.y );
		qz.setRotationZ( vec.z );

		*this = qz * qy * qx;
	}

	void fromAxes( Vector3 xaxis, Vector3 yaxis, Vector3 zaxis )
	{
		float kRot[3][3];
		kRot[0][0] = xaxis.x;
		kRot[1][0] = xaxis.y;
		kRot[2][0] = xaxis.z;
		
		kRot[0][1] = yaxis.x;
		kRot[1][1] = yaxis.y;
		kRot[2][1] = yaxis.z;

		kRot[0][2] = zaxis.x;
		kRot[1][2] = zaxis.y;
		kRot[2][2] = zaxis.z;

		float fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
		float fRoot;

		if ( fTrace > 0.0 )
		{
			fRoot = sqrt(fTrace + 1.0f);
			w = 0.5f * fRoot;
			fRoot = 0.5f / fRoot;

			x = (kRot[2][1]-kRot[1][2]) * fRoot;
			y = (kRot[0][2]-kRot[2][0]) * fRoot;
			z = (kRot[1][0]-kRot[0][1]) * fRoot;
		}
		else
		{
			size_t s_iNext[3] = { 1, 2, 0 };
			size_t i = 0;
			
			if ( kRot[1][1] > kRot[0][0] )
				i = 1;
			if ( kRot[2][2] > kRot[i][i] )
				i = 2;
			size_t j = s_iNext[i];
			size_t k = s_iNext[j];

			fRoot = sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
			
			float* apkQuat[3] = { &x, &y, &z };
			*apkQuat[i] = 0.5f * fRoot;

			fRoot = 0.5f / fRoot;
			w = (kRot[k][j]-kRot[j][k])*fRoot;
			*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
			*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
		}
	}

	inline void slerp( const Quaternion& q0, const Quaternion& q1, float l )
	{
		float fScale1;
		float fScale2;
		
		Quaternion A = q0;
		Quaternion B = q1;

		// compute dot product, aka cos(theta):
		float fCosTheta = A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w;

		if (fCosTheta < 0.0f) {
			// flip start quaternion
			A.x = -A.x; A.y = -A.y; A.z = -A.z; A.w = -A.w;
			fCosTheta = -fCosTheta;
		}

		if ((fCosTheta + 1.0f) > 0.05f) {
			// If the quaternions are close, use linear interploation
			if ((1.0f - fCosTheta) < 0.05f) {
				fScale1 = 1.0f - l;
				fScale2 = l;
			}
			else { 
				// Otherwise, do spherical interpolation
				float fTheta    = acos(fCosTheta);
				float fSinTheta = sin(fTheta);
				fScale1 = sin( fTheta * (1.0f-l) ) / fSinTheta;
				fScale2 = sin( fTheta * l ) / fSinTheta;
			}
		}
		else {
			B.x = -A.y;
			B.y =  A.x;
			B.z = -A.w;
			B.w =  A.z;
			fScale1 = sin( PI * (0.5f - l) );
			fScale2 = sin( PI * l );
		}

		x = fScale1 * A.x + fScale2 * B.x;
		y = fScale1 * A.y + fScale2 * B.y;
		z = fScale1 * A.z + fScale2 * B.z;
		w = fScale1 * A.w + fScale2 * B.w;
	}
	
	inline void lerp( const Quaternion& q0, const Quaternion& q1, float l )
	{
		slerp( q0, q1, l );
	}
};

//--------------------------------
template <>
inline void lerp<Quaternion>( Quaternion& result, const Quaternion& value0, const Quaternion& value1, float lerpval )
{
	result.lerp( value0, value1, lerpval );
}

//--------------------------------
template<>
inline void ReadStream<Quaternion>( const Stream& vStream, Quaternion& vValue )
{
	ReadStream<float>( vStream, vValue.x );
	ReadStream<float>( vStream, vValue.y );
	ReadStream<float>( vStream, vValue.z );
	ReadStream<float>( vStream, vValue.w );
}

//--------------------------------
template<>
inline void WriteStream<Quaternion>( Stream& vStream, const Quaternion& vValue )
{
	WriteStream<float>( vStream, vValue.x );
	WriteStream<float>( vStream, vValue.y );
	WriteStream<float>( vStream, vValue.z );
	WriteStream<float>( vStream, vValue.w );
}

}

#endif

