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

#ifndef MOCHA_MATRIX_H
#define MOCHA_MATRIX_H

#include "Mocha/Quaternion.h"

namespace Mocha
{

// Some of this code was borrowed from the Nebula Device.
// http://nebuladevice.cubik.org

/// A 4x4 component 3D matrix
class Matrix
{
public:
	float m[4][4];

	/// Constructor
	inline Matrix( )
	{
		// ...
	}

	/// Copy constructor
	inline Matrix( const Matrix& other )
	{
		M11 = other.M11;
		M12 = other.M12;
		M13 = other.M13;
		M14 = other.M14;

		M21 = other.M21;
		M22 = other.M22;
		M23 = other.M23;
		M24 = other.M24;

		M31 = other.M31;
		M32 = other.M32;
		M33 = other.M33;
		M34 = other.M34;

		M41 = other.M41;
		M42 = other.M42;
		M43 = other.M43;
		M44 = other.M44;
	}

	/// Constructor
	inline Matrix( float _m11, float _m12, float _m13, float _m14,
                    float _m21, float _m22, float _m23, float _m24,
                    float _m31, float _m32, float _m33, float _m34,
                    float _m41, float _m42, float _m43, float _m44 )
	{
		M11 = _m11; M12 = _m12; M13 = _m13; M14 = _m14;
		M21 = _m21; M22 = _m22; M23 = _m23; M24 = _m24;
		M31 = _m31; M32 = _m32; M33 = _m33; M34 = _m34;
		M41 = _m41; M42 = _m42; M43 = _m43; M44 = _m44;
	}

	/// Constructor. Builds rotation matrix from quaternion
	inline Matrix( const Quaternion& q )
	{
		set( q );
	}

	/// Sets matrix to identity
	inline void ident( )
	{
		M11 = 1.0;
		M12 = 0.0;
		M13 = 0.0;
		M14 = 0.0;

		M21 = 0.0;
		M22 = 1.0;
		M23 = 0.0;
		M24 = 0.0;

		M31 = 0.0;
		M32 = 0.0;
		M33 = 1.0;
		M34 = 0.0;

		M41 = 0.0;
		M42 = 0.0;
		M43 = 0.0;
		M44 = 1.0;
	}

	/// Sets matrix from raw float values
	inline void set( float _m11, float _m12, float _m13, float _m14,
                     float _m21, float _m22, float _m23, float _m24,
                     float _m31, float _m32, float _m33, float _m34,
                     float _m41, float _m42, float _m43, float _m44 )
	{
		M11 = _m11; M12 = _m12; M13 = _m13; M14 = _m14;
		M21 = _m21; M22 = _m22; M23 = _m23; M24 = _m24;
		M31 = _m31; M32 = _m32; M33 = _m33; M34 = _m34;
		M41 = _m41; M42 = _m42; M43 = _m43; M44 = _m44;
	}

	/// Builds the matrix values from a quaternion
	inline void set( const Quaternion& q )
	{
		float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

		x2 = q.x + q.x;  y2 = q.y + q.y;  z2 = q.z + q.z;
		xx = q.x * x2;   xy = q.x * y2;   xz = q.x * z2;
		yy = q.y * y2;   yz = q.y * z2;   zz = q.z * z2;
		wx = q.w * x2;   wy = q.w * y2;   wz = q.w * z2;

		m[0][0] = 1.0f - (yy + zz);
		m[1][0] = xy - wz;
		m[2][0] = xz + wy;

		m[0][1] = xy + wz;
		m[1][1] = 1.0f - (xx + zz);
		m[2][1] = yz - wx;

		m[0][2] = xz - wy;
		m[1][2] = yz + wx;
		m[2][2] = 1.0f - (xx + yy);

		m[3][0] = m[3][1] = m[3][2] = 0.0f;
		m[0][3] = m[1][3] = m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/// Transposes the matrix
	inline void transpose( )
	{
		#undef v_swap
		#define v_swap( x, y ) { float t = x; x = y; y = t; }

		v_swap( M12, M21 );
		v_swap( M13, M31 );
		v_swap( M14, M41 );
		v_swap( M23, M32 );
		v_swap( M24, M42 );
		v_swap( M34, M43 );
	}

	inline float det( )
	{
		return
		  (M11 * M22 - M12 * M21) * (M33 * M44 - M34 * M43)
		 -(M11 * M23 - M13 * M21) * (M32 * M44 - M34 * M42)
		 +(M11 * M24 - M14 * M21) * (M32 * M43 - M33 * M42)
		 +(M12 * M23 - M13 * M22) * (M31 * M44 - M34 * M41)
		 -(M12 * M24 - M14 * M22) * (M31 * M43 - M33 * M41)
		 +(M13 * M24 - M14 * M23) * (M31 * M42 - M32 * M41);
	}

	/// Inverts the matrix using a simple, quick algorithm
	inline void simpleInvert( )
	{
		float s = det( );
		if ( s == 0.0f )
			return;

		s = 1.0f/s;

		set(
				s * ((M22 * M33) - (M23 * M32)),
				s * ((M32 * M13) - (M33 * M12)),
				s * ((M12 * M23) - (M13 * M22)),
				0.0f,
				s * ((M23 * M31) - (M21 * M33)),
				s * ((M33 * M11) - (M31 * M13)),
				s * ((M13 * M21) - (M11 * M23)),
				0.0f,
				s * ((M21 * M32) - (M22 * M31)),
				s * ((M31 * M12) - (M32 * M11)),
				s * ((M11 * M22) - (M12 * M21)),
				0.0f,
				s * (M21*(M33*M42 - M32*M43) + M22*(M31*M43 - M33*M41) + M23*(M32*M41 - M31*M42)),
				s * (M31*(M13*M42 - M12*M43) + M32*(M11*M43 - M13*M41) + M33*(M12*M41 - M11*M42)),
				s * (M41*(M13*M22 - M12*M23) + M42*(M11*M23 - M13*M21) + M43*(M12*M21 - M11*M22)),
				1.0f
			);
	}

	/// Multiplies the matrix with another using a simple algorithm
	inline void simpleMultiply( const Matrix& other )
	{
		int i;
		for (i=0; i<4; i++) {
			float mi0 = m[i][0];
			float mi1 = m[i][1];
			float mi2 = m[i][2];

			m[i][0] = mi0*other.m[0][0] + mi1*other.m[1][0] + mi2*other.m[2][0];
			m[i][1] = mi0*other.m[0][1] + mi1*other.m[1][1] + mi2*other.m[2][1];
			m[i][2] = mi0*other.m[0][2] + mi1*other.m[1][2] + mi2*other.m[2][2];
		}

		m[3][0] += other.m[3][0];
		m[3][1] += other.m[3][1];
		m[3][2] += other.m[3][2];

		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/// Does a full inversion of the matrix values
	inline void invert( )
	{
		float s = det( );
		if ( s == 0.0 )
			return;

		s = 1/s;

		set(
			s*(M22*(M33*M44 - M34*M43) + M23*(M34*M42 - M32*M44) + M24*(M32*M43 - M33*M42)),
			s*(M32*(M13*M44 - M14*M43) + M33*(M14*M42 - M12*M44) + M34*(M12*M43 - M13*M42)),
			s*(M42*(M13*M24 - M14*M23) + M43*(M14*M22 - M12*M24) + M44*(M12*M23 - M13*M22)),
			s*(M12*(M24*M33 - M23*M34) + M13*(M22*M34 - M24*M32) + M14*(M23*M32 - M22*M33)),
			s*(M23*(M31*M44 - M34*M41) + M24*(M33*M41 - M31*M43) + M21*(M34*M43 - M33*M44)),
			s*(M33*(M11*M44 - M14*M41) + M34*(M13*M41 - M11*M43) + M31*(M14*M43 - M13*M44)),
			s*(M43*(M11*M24 - M14*M21) + M44*(M13*M21 - M11*M23) + M41*(M14*M23 - M13*M24)),
			s*(M13*(M24*M31 - M21*M34) + M14*(M21*M33 - M23*M31) + M11*(M23*M34 - M24*M33)),
			s*(M24*(M31*M42 - M32*M41) + M21*(M32*M44 - M34*M42) + M22*(M34*M41 - M31*M44)),
			s*(M34*(M11*M42 - M12*M41) + M31*(M12*M44 - M14*M42) + M32*(M14*M41 - M11*M44)),
			s*(M44*(M11*M22 - M12*M21) + M41*(M12*M24 - M14*M22) + M42*(M14*M21 - M11*M24)),
			s*(M14*(M22*M31 - M21*M32) + M11*(M24*M32 - M22*M34) + M12*(M21*M34 - M24*M31)),
			s*(M21*(M33*M42 - M32*M43) + M22*(M31*M43 - M33*M41) + M23*(M32*M41 - M31*M42)),
			s*(M31*(M13*M42 - M12*M43) + M32*(M11*M43 - M13*M41) + M33*(M12*M41 - M11*M42)),
			s*(M41*(M13*M22 - M12*M23) + M42*(M11*M23 - M13*M21) + M43*(M12*M21 - M11*M22)),
			s*(M11*(M22*M33 - M23*M32) + M12*(M23*M31 - M21*M33) + M13*(M21*M32 - M22*M31))
		);
	}

	/// Transforms a 3D point by the matrix values
	inline Vector3 operator * ( const Vector3& v ) const
	{
		float d = 1.0f / (M14*v.x + M24*v.y + M34*v.z + M44);
		return Vector3(
			(M11*v.x + M21*v.y + M31*v.z + M41) * d,
			(M12*v.x + M22*v.y + M32*v.z + M42) * d,
			(M13*v.x + M23*v.y + M33*v.z + M43) * d
		);
	}

	/// Multiplies the matrix with another to combine them
	inline Matrix operator * ( const Matrix& other ) const
	{
		return Matrix(
				m[0][0]*other.m[0][0] + m[0][1]*other.m[1][0] + m[0][2]*other.m[2][0] + m[0][3]*other.m[3][0],
				m[0][0]*other.m[0][1] + m[0][1]*other.m[1][1] + m[0][2]*other.m[2][1] + m[0][3]*other.m[3][1],
				m[0][0]*other.m[0][2] + m[0][1]*other.m[1][2] + m[0][2]*other.m[2][2] + m[0][3]*other.m[3][2],
				m[0][0]*other.m[0][3] + m[0][1]*other.m[1][3] + m[0][2]*other.m[2][3] + m[0][3]*other.m[3][3],

				m[1][0]*other.m[0][0] + m[1][1]*other.m[1][0] + m[1][2]*other.m[2][0] + m[1][3]*other.m[3][0],
				m[1][0]*other.m[0][1] + m[1][1]*other.m[1][1] + m[1][2]*other.m[2][1] + m[1][3]*other.m[3][1],
				m[1][0]*other.m[0][2] + m[1][1]*other.m[1][2] + m[1][2]*other.m[2][2] + m[1][3]*other.m[3][2],
				m[1][0]*other.m[0][3] + m[1][1]*other.m[1][3] + m[1][2]*other.m[2][3] + m[1][3]*other.m[3][3],

				m[2][0]*other.m[0][0] + m[2][1]*other.m[1][0] + m[2][2]*other.m[2][0] + m[2][3]*other.m[3][0],
				m[2][0]*other.m[0][1] + m[2][1]*other.m[1][1] + m[2][2]*other.m[2][1] + m[2][3]*other.m[3][1],
				m[2][0]*other.m[0][2] + m[2][1]*other.m[1][2] + m[2][2]*other.m[2][2] + m[2][3]*other.m[3][2],
				m[2][0]*other.m[0][3] + m[2][1]*other.m[1][3] + m[2][2]*other.m[2][3] + m[2][3]*other.m[3][3],

				m[3][0]*other.m[0][0] + m[3][1]*other.m[1][0] + m[3][2]*other.m[2][0] + m[3][3]*other.m[3][0],
				m[3][0]*other.m[0][1] + m[3][1]*other.m[1][1] + m[3][2]*other.m[2][1] + m[3][3]*other.m[3][1],
				m[3][0]*other.m[0][2] + m[3][1]*other.m[1][2] + m[3][2]*other.m[2][2] + m[3][3]*other.m[3][2],
				m[3][0]*other.m[0][3] + m[3][1]*other.m[1][3] + m[3][2]*other.m[2][3] + m[3][3]*other.m[3][3]
			);
	}

	/// Multiplies the matrix with another
	inline const Matrix& operator *= ( const Matrix& m1 )
	{
		int i;
		for (i=0; i<4; i++) {
			float mi0 = m[i][0];
			float mi1 = m[i][1];
			float mi2 = m[i][2];
			float mi3 = m[i][3];

			m[i][0] = mi0*m1.m[0][0] + mi1*m1.m[1][0] + mi2*m1.m[2][0] + mi3*m1.m[3][0];
			m[i][1] = mi0*m1.m[0][1] + mi1*m1.m[1][1] + mi2*m1.m[2][1] + mi3*m1.m[3][1];
			m[i][2] = mi0*m1.m[0][2] + mi1*m1.m[1][2] + mi2*m1.m[2][2] + mi3*m1.m[3][2];
			m[i][3] = mi0*m1.m[0][3] + mi1*m1.m[1][3] + mi2*m1.m[2][3] + mi3*m1.m[3][3];
		}

		return *this;
	}

	/// Builds a left-handed matrix looking at a specified point
	/*! \param at The point to look at
		\param up The up-vector */
	inline void lookAtLH( const Vector3& at, const Vector3& up )
	{
		Vector3 eye( M41, M42, M43 );

		Vector3 zaxis = at - eye;
		zaxis.normalize( );

		Vector3 xaxis = up * zaxis;
		xaxis.normalize( );

		Vector3 yaxis = zaxis * xaxis;

		M11 = xaxis.x; M12 = yaxis.x; M13 = zaxis.x; M14 = 0.0f;
		M21 = xaxis.y; M22 = yaxis.y; M23 = zaxis.y; M24 = 0.0f;
		M31 = xaxis.z; M32 = yaxis.z; M33 = zaxis.z; M34 = 0.0f;
	}

	/// Builds a right-handed matrix looking at a specified point
	/*! \param at The point to look at
		\param up The up-vector */
	inline void lookAtRH( const Vector3& at, const Vector3& up )
	{
		Vector3 eye( M41, M42, M43 );

		Vector3 zaxis = at - eye;
		zaxis.normalize( );

		Vector3 xaxis = up * zaxis;
		xaxis.normalize( );

		Vector3 yaxis = zaxis * xaxis;

		M11 = xaxis.x; M12 = xaxis.y; M13 = xaxis.z; M14 = 0.0f;
		M21 = yaxis.x; M22 = yaxis.y; M23 = yaxis.z; M24 = 0.0f;
		M31 = zaxis.x; M32 = zaxis.y; M33 = zaxis.z; M34 = 0.0f;
	}

	inline void lookDirectionLH( const Vector3& dir, const Vector3& up )
	{
		Vector3 zaxis = -dir;
		zaxis.normalize( );

		Vector3 xaxis = up * zaxis;
		xaxis.normalize( );

		Vector3 yaxis = zaxis * xaxis;

		M11 = xaxis.x; M12 = yaxis.x; M13 = zaxis.x; M14 = 0.0f;
		M21 = xaxis.y; M22 = yaxis.y; M23 = zaxis.y; M24 = 0.0f;
		M31 = xaxis.z; M32 = yaxis.z; M33 = zaxis.z; M34 = 0.0f;
	}

	inline void lookDirectionRH( const Vector3& dir, const Vector3& up )
	{
		Vector3 zaxis = -dir;
		zaxis.normalize( );

		Vector3 xaxis = up * zaxis;
		xaxis.normalize( );

		Vector3 yaxis = zaxis * xaxis;

		M11 = xaxis.x; M12 = xaxis.y; M13 = xaxis.z; M14 = 0.0f;
		M21 = yaxis.x; M22 = yaxis.y; M23 = yaxis.z; M24 = 0.0f;
		M31 = zaxis.x; M32 = zaxis.y; M33 = zaxis.z; M34 = 0.0f;
	}

	inline void perspectiveFovLH( float fovY, float aspect, float zn, float zf )
	{
		float h = (float)( 1.0 / tan( fovY * 0.5f ) );
		float w = h / aspect;

		M11 = w;			M12 = 0.0f;		M13 = 0.0f;					M14 = 0.0f;
		M21 = 0.0f;		M22 = h;			M23 = 0.0f;					M24 = 0.0f;
		M31 = 0.0f;		M32 = 0.0f;		M33 = zf/(zf-zn);			M34 = 1.0f;
		M41 = 0.0f;		M42 = 0.0f;		M43 = -zn*(zf/(zf-zn));	M44 = 0.0f;
	}

	inline void perspectiveFovRH( float fovY, float aspect, float zn, float zf ) {
		float h = (float)( 1.0 / tan( fovY * 0.5f ) );
		float w = h / aspect;

		M11 = w;			M12 = 0.0f;		M13 = 0.0f;					M14 = 0.0f;
		M21 = 0.0f;		M22 = h;			M23 = 0.0f;					M24 = 0.0f;
		M31 = 0.0f;		M32 = 0.0f;		M33 = zf/(zn-zf);			M34 = -1.0f;
		M41 = 0.0f;		M42 = 0.0f;		M43 = zn*(zf/(zn-zf));	M44 = 0.0f;
	}

	/// Gets the origin of the matrix
	inline Vector3 getPosition( ) const
	{
		return Vector3( M41, M42, M43 );
	}

	/// Sets the origin of the matrix
	inline void setPosition( const Vector3& v )
	{
		M41 = v.x;
		M42 = v.y;
		M43 = v.z;
	}

	/// Translates the matrix by a relative amount
	inline void translate( const Vector3& v )
	{
		M41 += v.x;
		M42 += v.y;
		M43 += v.z;
	}

	/// Rotates a vector
	inline Vector3 rotateVector( const Vector3& v ) const
	{
		return Vector3(
			M11 * v.x + M21 * v.y + M31 * v.z,
			M12 * v.x + M22 * v.y + M32 * v.z,
			M13 * v.x + M23 * v.y + M33 * v.z
		);
	}

	/// Transforms a point through the matrix
	inline Vector3 transform( const Vector3& v ) const
	{
		return rotateVector( v ) + getPosition( );
	}

	/// Sets the matrix scale
	inline void setScale( const Vector3& s ) {
			m[0][0] = s.x;
			m[1][1] = s.y;
			m[2][2] = s.z;
	}

	/// Scales the matrix
	inline void scale( const Vector3& s ) {
		int i;
		for ( i = 0; i < 4; i++ ) {
			m[i][0] *= s.x;
			m[i][1] *= s.y;
			m[i][2] *= s.z;
		}
	}

	/// Builds a rotation matrix along the X axis
	inline void buildRotationX( float angle )
	{
        ident();
        float cosval = cos(angle);
		float sinval = sin(angle);

		m[1][1] = cosval;
		m[2][2] = cosval;
		m[1][2] = -sinval;
		m[2][1] = sinval;
	}

	/// Builds a rotation matrix along the Y axis
	inline void buildRotationY( float angle )
	{
        ident();
        float cosval = cos(angle);
		float sinval = sin(angle);

		m[0][0] = cosval;
		m[2][2] = cosval;
		m[0][2] = sinval;
		m[2][0] = -sinval;
	}

	/// Builds a rotation matrix along the Z axis
	inline void buildRotationZ( float angle )
	{
        ident();
        float cosval = cos(angle);
		float sinval = sin(angle);

		m[0][0] = cosval;
		m[1][1] = cosval;
		m[0][1] = -sinval;
		m[1][0] = sinval;
	}
};

}

#endif
