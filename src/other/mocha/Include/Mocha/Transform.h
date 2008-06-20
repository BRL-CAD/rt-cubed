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

#ifndef MOCHA_TRANSFORM_H
#define MOCHA_TRANSFORM_H

#include "Mocha/Math.h"
#include "Mocha/Vector3.h"
#include "Mocha/Quaternion.h"
#include "Mocha/Matrix.h"
#include "Mocha/Stream.h"

namespace Mocha
{

class Transform
{
protected:
	Quaternion mRotation;

	Vector3 mPosition;
	
	Vector3 mScale;

	// Cached transformation

	mutable Matrix mCache;

	mutable bool mDirty;

	inline void update( ) const
	{
		// First clear the local transformation

		mCache.ident( );

		// Set the transform scale

		mCache.setScale( mScale );

		// Create a rotation matrix and multiply it
		// into the local transformation to rotate it

		mCache *= Matrix( mRotation );

		// Set the position

		mCache.setPosition( mPosition );

		// All done!

		mDirty = false;
	}

	inline void flagUpdate( )
	{
		mDirty = true;
	}

public:
	inline Transform( )
		: mScale( 1.0f, 1.0f, 1.0f ), mDirty( false )
	{
		mCache.ident( );
	}

	inline Transform( const Transform& vOther )
		: mScale( vOther.mScale ), mRotation( vOther.mRotation ), mPosition( vOther.mPosition ), mDirty( false )
	{
		mCache.ident( );
	}

	inline ~Transform( )
	{
		// ...
	}

	inline void set( const Vector3& vPosition, const Vector3& vScale, const Quaternion& vRotation )
	{
		mPosition = vPosition;
		mRotation = vRotation;
		mScale = vScale;
		flagUpdate( );
	}

	inline void translate( const Vector3& vAmount )
	{
		mPosition += vAmount;
		flagUpdate( );
	}

	inline void setPosition( const Vector3& vTranslation )
	{
		mPosition = vTranslation;
		flagUpdate( );
	}

	inline const Vector3& getPosition( ) const
	{
		return mPosition;
	}

	inline void scale( const Vector3& vAmount )
	{
		mScale.x *= vAmount.x;
		mScale.y *= vAmount.y;
		mScale.z *= vAmount.z;
		flagUpdate( );
	}

	inline void setScale( float vValue )
	{
		mScale = Vector3( vValue, vValue, vValue );
		flagUpdate( );
	}

	inline void setScale( const Vector3& vScale )
	{
		mScale = vScale;
		flagUpdate( );
	}

	inline const Vector3& getScale( ) const
	{
		return mScale;
	}

	inline void rotateEuler( const Vector3& vAmount )
	{
		Quaternion q;
		q.setRotation( vAmount );

		rotate( q );
	}

	inline void rotate( const Quaternion& vAmount )
	{
		mRotation *= vAmount;
		flagUpdate( );
	}

	inline void setRotationEuler( const Vector3& vRotation )
	{
		Quaternion q;
		q.setRotation( vRotation );

		setRotation( q );
	}

	inline void setRotation( const Quaternion& vRotation )
	{
		mRotation = vRotation;
		flagUpdate( );
	}

	inline const Quaternion& getRotation( ) const
	{
		return mRotation;
	}

	inline void setMatrix( const Matrix& vMatrix )
	{
		mCache = vMatrix;
		mDirty = false;
	}

	inline const Matrix& getMatrix( ) const
	{
		if ( mDirty )
			update( );

		return mCache;
	}
};

//--------------------------------
template<>
inline void lerp<Transform>( Transform& result, const Transform& value0, const Transform& value1, float lerpval )
{
	Vector3 pos;
	lerp( pos, value0.getPosition( ), value1.getPosition( ), lerpval );

	Vector3 scale;
	lerp( scale, value0.getScale( ), value1.getScale( ), lerpval );

	Quaternion rot;
	lerp( rot, value0.getRotation( ), value1.getRotation( ), lerpval );

	result.set( pos, scale, rot );
}

//--------------------------------
template <>
inline void ReadStream<Transform>( const Stream& vStream, Transform& vValue )
{
	vValue.setPosition( vStream.read<Vector3>( ) );
	vValue.setRotation( vStream.read<Quaternion>( ) );
	vValue.setScale( vStream.read<Vector3>( ) );
}

//--------------------------------
template <>
inline void WriteStream<Transform>( Stream& vStream, const Transform& vTransform )
{
	vStream.write<Vector3>( vTransform.getPosition( ) );
	vStream.write<Quaternion>( vTransform.getRotation( ) );
	vStream.write<Vector3>( vTransform.getScale( ) );
}

}

#endif
