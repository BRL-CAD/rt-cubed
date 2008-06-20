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

#ifndef MOCHA_RECTANGLE_H
#define MOCHA_RECTANGLE_H

#include <algorithm>

#include "Mocha/Math.h"
#include "Mocha/Vector2.h"
#include "Mocha/Stream.h"

namespace Mocha
{

/// A simple 2D rectangle
class Rectangle
{
public:
	float left;

	float right;

	float top;

	float bottom;

	inline Rectangle( float vLeft, float vTop, float vRight, float vBottom )
		: left( vLeft ), top( vTop ), right( vRight ), bottom( vBottom )
	{
		// ...
	}

	inline Rectangle( const Rectangle& vOther )
		: left( vOther.left ), top( vOther.top ), right( vOther.right ), bottom( vOther.bottom )
	{
		// ...
	}

	inline Rectangle( )
		: left( 0.0f ), top( 0.0f ), right( 0.0f ), bottom( 0.0f )
	{
		// ...
	}

	inline void validate( )
	{
		if ( right < left || left > right )
			std::swap( left, right );
		if ( bottom < top || top > bottom )
			std::swap( bottom, top );
	}

	inline bool isZero( ) const
	{
		return ( ( left == 0.0f ) && ( right == 0.0f ) && ( top == 0.0f ) && ( bottom == 0.0f ) );
	}

	inline bool operator == ( const Rectangle& other ) const
	{
		return ( ( left == other.left ) && ( top == other.top ) &&
				 ( right == other.right ) && ( bottom == other.bottom ) );
	}

	inline bool operator != ( const Rectangle& other ) const
	{
		return ( ( left != other.left ) || ( top != other.top ) ||
				 ( right != other.right ) || ( bottom != other.bottom ) );
	}

	inline void translate( const Vector2& vAmount )
	{
		translate( vAmount.x, vAmount.y );
	}

	inline void translate( float vX, float vY )
	{
		setPosition( left + vX, top + vY );
	}

	inline void setPosition( const Vector2& vPoint )
	{
		setPosition( vPoint.x, vPoint.y );
	}

	inline void setPosition( float vX, float vY )
	{
		float w = getWidth( );
		float h = getHeight( );

		top = vY;
		left = vX;

		setSize( w, h );
	}

	inline Vector2 getPosition( ) const
	{
		return Vector2( left, top );
	}

	inline Vector2 getSize( ) const
	{
		return Vector2( getWidth( ), getHeight( ) );
	}

	inline void setXPosition( float vX )
	{
		float w = getWidth( );
		float h = getHeight( );

		left = vX;

		setSize( w, h );
	}

	inline void setYPosition( float vY )
	{
		float w = getWidth( );
		float h = getHeight( );

		top = vY;

		setSize( w, h );
	}

	inline float getWidth( ) const
	{
		return right - left;
	}

	inline void setWidth( float vWidth )
	{
		right = left + vWidth;
	}

	inline float getHeight( ) const
	{
		return bottom - top;
	}

	inline void setHeight( float vHeight )
	{
		bottom = top + vHeight;
	}

	inline void setSize( float vWidth, float vHeight )
	{
		setWidth( vWidth );
		setHeight( vHeight );
	}

	inline void setSize( const Vector2& vSize )
	{
		setWidth( vSize.x );
		setHeight( vSize.y );
	}

	inline void resize( float vRelX, float vRelY )
	{
		resize( Vector2( vRelX, vRelY ) );
	}

	inline void resize( const Vector2& vRel )
	{
		setWidth( getWidth( ) + vRel.x );
		setHeight( getHeight( ) + vRel.y );
	}

	inline void extend( Vector2 point )
	{
		if( left > point.x )
			left = point.x;
		
		if( top > point.y ) 
			top = point.y;
		
		if( right < point.x )
			right = point.x;
		
		if( bottom < point.y )
			bottom = point.y;
	}

	inline void shrink( int vAmount )
	{
		top += vAmount;
		bottom -= vAmount;
		left += vAmount;
		right -= vAmount;
	}

	inline void scale( float vX, float vY )
	{
		setWidth( getWidth( ) * vX );
		setHeight( getHeight( ) * vY );
	}

	inline bool pointInside( const Vector2& vPoint ) const
	{
		return pointInside( vPoint.x, vPoint.y );
	}

	inline bool pointInside( float vX, float vY ) const
	{
		if ( ( vX >= left ) && ( vY >= top ) )
		{
			if ( ( vX <= right ) && ( vY <= bottom ) )
				return true;
		}

		return false;
	}

	inline Vector2 getCenter( ) const
	{
		float centerx = left + ( getWidth( ) / 2 );
		float centery = top + ( getHeight( ) / 2 );

		return Vector2( centerx, centery );
	}

	inline Rectangle intersect( const Rectangle& other ) const
	{
		if ( (*this) == other )
			return other;

		// Check for total exclusion
		if ( ( right > other.left ) &&
			 ( left < other.right ) &&
			 ( bottom > other.top ) &&
			 ( top < other.bottom ) )
		{
			Rectangle temp;

			// Modify left
			if ( left > other.left )
				temp.left = left;
			else
				temp.left = other.left;

			// Modify right
			if ( right < other.right )
				temp.right = right;
			else
				temp.right = other.right;

			// Modify top
			if ( top > other.top )
				temp.top = top;
			else
				temp.top = other.top;

			// Modify bottom
			if ( bottom < other.bottom )
				temp.bottom = bottom;
			else
				temp.bottom = other.bottom;

			return temp;
		}
		else
		{
			return Rectangle( 0.0f, 0.0f, 0.0f, 0.0f );
		}
	}

	inline Rectangle& operator += ( const Rectangle& vOther )
	{
		top += vOther.top;
		bottom += vOther.bottom;
		left += vOther.left;
		right += vOther.right;

		return *this;
	}

	inline Rectangle operator + ( const Rectangle& vOther ) const
	{
		Rectangle r = *this;
		r += vOther;

		return r;
	}
};

//--------------------------------
template <>
inline void WriteStream<Rectangle>( Stream& vStream, const Rectangle& vValue )
{
	vStream.write( vValue.left );
	vStream.write( vValue.top );
	vStream.write( vValue.right );
	vStream.write( vValue.bottom );
}

//--------------------------------
template <>
inline void ReadStream<Rectangle>( const Stream& vStream, Rectangle& vValue )
{
	vStream.read( vValue.left );
	vStream.read( vValue.top );
	vStream.read( vValue.right );
	vStream.read( vValue.bottom );
}

}

#endif
