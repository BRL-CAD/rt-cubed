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

#ifndef MOCHA_COLOR_H
#define MOCHA_COLOR_H

#include "Mocha/Platform.h"
#include "Mocha/Stream.h"
#include "Mocha/Math.h"

namespace Mocha
{

/// A color value with red, green, blue and alpha components
class MOCHA_EXPORT Color
{
public:
	float r;

	float g;

	float b;

	float a;
	
	//-------------------------------------------------------------
	/// Constructor
	/*! \param vr The red value to use
		\param vg The green value to use
		\param vb The blue value to use
		\param va The alpha value to use */
	inline Color( float vr, float vg, float vb, float va )
		: r( vr ), g( vg ), b( vb ), a( va )
	{
		// ...
	}
	
	//-------------------------------------------------------------
	/// Copy constructor
	/*! \param other The color value to copy */
	inline Color( const Color& other )
		: r( other.r ), g( other.g ), b( other.b ), a( other.a )
	{
		// ...
	}

	//-------------------------------------------------------------
	/// Default constructor. This sets all components to 0.0
	inline Color( )
		: r( 0.0f ), g( 0.0f ), b( 0.0f ), a( 0.0f )
	{
		// ...
	}

	//-------------------------------------------------------------
	/// Sets the components from a 32 bit integer RBGA value
	/*! \param v The 32 bit integer color value */
	inline void setRGBA( int32 v )
	{
		r = (float)( ( v & 0xFF000000 ) >> 24 ) / 255.0f;
		g = (float)( ( v & 0x00FF0000 ) >> 16 ) / 255.0f;
		b = (float)( ( v & 0x0000FF00 ) >>  8 ) / 255.0f;
		a = (float)( ( v & 0x000000FF ) >>  0 ) / 255.0f;
	}

	//-------------------------------------------------------------
	/// Sets the components from a 32 bit integer ARGB value
	/*! \param v The 32 bit integer color value */
	inline void setARGB( int32 v )
	{
		a = (float)( ( v & 0xFF000000 ) >> 24 ) / 255.0f;
		r = (float)( ( v & 0x00FF0000 ) >> 16 ) / 255.0f;
		g = (float)( ( v & 0x0000FF00 ) >>  8 ) / 255.0f;
		b = (float)( ( v & 0x000000FF ) >>  0 ) / 255.0f;
	}

	//-------------------------------------------------------------
	/// Gets the components of the color as a 32 bit integer RGBA value
	/*! \return The color, as a 32 bit integer RGBA value */
	inline int32 getRGBA( ) const
	{
		int32 value = 0;
		int8 tmp;

		tmp = (int8)( r * 255.0f );
		value = tmp << 24;

		tmp = (int8)( g * 255.0f );
		value += tmp << 16;

		tmp = (int8)( b * 255.0f );
		value += tmp << 8;

		tmp = (int8)( a * 255.0f );
		value += tmp;

		return value;
	}

	//-------------------------------------------------------------
	/// Gets the components of the color as a 32 bit integer ARGB value
	/*! \return The color, as a 32 bit integer ARGB value */
	inline int32 getARGB( ) const
	{
		int32 value = 0;
		int8 tmp;

		tmp = (int8)( a * 255.0f );
		value = tmp << 24;

		tmp = (int8)( r * 255.0f );
		value += tmp << 16;

		tmp = (int8)( g * 255.0f );
		value += tmp << 8;

		tmp = (int8)( b * 255.0f );
		value += tmp;

		return value;
	}

	//-------------------------------------------------------------
	/// Equality operator
	/*! \param other The color to test with
		\return True of the colors are equal, false if they are not equal */
	inline bool operator == ( const Color& other ) const
	{
		return ( ( r == other.r ) && ( g == other.g ) && ( b == other.b ) && ( a == other.a ) );
	}

	//-------------------------------------------------------------
	/// Inequality operator
	/*! \param other The color to test with
		\return True of the colors are not equal, false if they are equal */
	inline bool operator != ( const Color& other ) const
	{
		return ( ( r != other.r ) || ( g != other.g ) || ( b != other.b ) || ( a != other.a ) );
	}

	//-------------------------------------------------------------
	/// Clamps all values to the 0 .. 1 range
	inline void saturate( )
	{
		r = Mocha::saturate( r );
		g = Mocha::saturate( g );
		b = Mocha::saturate( b );
		a = Mocha::saturate( a );
	}

	//-------------------------------------------------------------
	/// Addition operator. Adds the components together
	/*! \param other The other color to add components with
		\return The resulting color value */
	inline Color operator + ( const Color& other ) const
	{
		Color c = (*this);
		c.r += other.r;
		c.g += other.g;
		c.b += other.b;
		c.a += other.a;
		
		return c;
	}

	//-------------------------------------------------------------
	/// Addition operator. Adds the components together
	/*! \param other The other color to add components with
		\return The resulting color value */
	inline Color& operator += ( const Color& other )
	{
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		
		return (*this);
	}

	//-------------------------------------------------------------
	/// Scalar addition operator. Adds the components with a scalar
	/*! \param vScalar The scalar value to add with
		\return Reference to self */
	inline Color& operator += ( float vScalar )
	{
		r += vScalar;
		g += vScalar;
		b += vScalar;
		a += vScalar;

		return *this;
	}

	//-------------------------------------------------------------
	/// Subtraction operator. Subtracts the components from each other
	/*! \param other The other color to subtract components with
		\return The resulting color value */
	inline Color operator - ( const Color& other ) const
	{
		Color c = (*this);
		c.r -= other.r;
		c.g -= other.g;
		c.b -= other.b;
		c.a -= other.a;
		
		return c;
	}

	//-------------------------------------------------------------
	/// Scalar subtraction operator. Subtracts the components with a scalar
	/*! \param vScalar The scalar value to subtract with
		\return Reference to self */
	inline Color& operator -= ( float vScalar )
	{
		r -= vScalar;
		g -= vScalar;
		b -= vScalar;
		a -= vScalar;

		return *this;
	}

	//-------------------------------------------------------------
	/// Multiplication operator. Multiplies the components with each other
	/*! \param other The other color to multiply components with
		\return The resulting color value */
	inline Color operator * ( const Color& other ) const
	{
		Color c = (*this);
		c.r *= other.r;
		c.g *= other.g;
		c.b *= other.b;
		c.a *= other.a;
		
		return c;
	}

	//-------------------------------------------------------------
	/// Scalar multiplication operator. Multiplies the components with a scalar
	/*! \param vScalar The scalar value to multiply with
		\return The resulting color value */
	inline Color operator * ( float vScalar ) const
	{
		Color c = (*this);
		c.r *= vScalar;
		c.g *= vScalar;
		c.b *= vScalar;
		c.a *= vScalar;
		
		return c;
	}

	//-------------------------------------------------------------
	/// Scalar multiplication operator. Multiplies the components with a scalar
	/*! \param vScalar The scalar value to multiply with
		\return Reference to self */
	inline Color& operator *= ( float vScalar )
	{
		r *= vScalar;
		g *= vScalar;
		b *= vScalar;
		a *= vScalar;

		return *this;
	}

	//-------------------------------------------------------------
	/// Linearly interpolates this and another color
	/*! \param vOther The color value to interpolate with
		\param lerpval The interpolation value */
	inline void lerp( const Color& vOther, float lerpval )
	{
		r = vOther.r + ( (r - vOther.r) * lerpval );
		g = vOther.g + ( (g - vOther.g) * lerpval );
		b = vOther.b + ( (b - vOther.b) * lerpval );
		a = vOther.a + ( (a - vOther.a) * lerpval );
	}

	//-------------------------------------------------------------
	/// Linearly interpolates two colors and sets this color as the result
	/*! \param v0 The first color
		\param v1 The second color
		\param lerpval The interpolation value */
	inline void lerp( const Color& v0, const Color& v1, float lerpval )
	{
		r = v0.r + ( (v1.r - v0.r) * lerpval );
		g = v0.g + ( (v1.g - v0.g) * lerpval );
		b = v0.b + ( (v1.b - v0.b) * lerpval );
		a = v0.a + ( (v1.a - v0.a) * lerpval );
	}

	//-------------------------------------------------------------
	/// Sets this color from a HSV value
	/*! \param h The Hue value
		\param s The Saturation value
		\param v The Variance value
		\param va The Alpha value */
	void setHSVA( float h, float s, float v, float va = 1.0f );

	/// Gets the value as a Hue-Saturation-Variance value
	/*! \param h The float value that will receive the Hue
		\param s The float value that will receive the Saturation
		\param v The float value that will receive the Variance */
	void getHSV( float& h, float& s, float& v ) const;

	/// Transparent Color (0.0, 0.0, 0.0, 0.0)
	static const Color Transparent;

	/// Black Color (0.0, 0.0, 0.0, 1.0)
	static const Color Black;

	/// White Color (1.0, 1.0, 1.0, 1.0)
	static const Color White;

	/// Red Color (1.0, 0.0, 0.0, 1.0)
	static const Color Red;

	/// Green Color (0.0, 1.0, 0.0, 1.0)
	static const Color Green;

	/// Blue Color (0.0, 0.0, 1.0, 1.0)
	static const Color Blue;

	/// Yellow color (1.0, 1.0, 0.0, 1.0)
	static const Color Yellow;

	/// Magenta color (1.0, 0.0, 1.0, 1.0)
	static const Color Magenta;

	/// Gray color (0.5, 0.5, 0.5, 1.0)
	static const Color Gray;
};

//--------------------------------
template<>
inline void ReadStream<Color>( const Stream& vStream, Color& vColor )
{
	ReadStream<float>( vStream, vColor.r );
	ReadStream<float>( vStream, vColor.g );
	ReadStream<float>( vStream, vColor.b );
	ReadStream<float>( vStream, vColor.a );
}

//--------------------------------
template<>
inline void WriteStream<Color>( Stream& vStream, const Color& vValue )
{
	WriteStream<float>( vStream, vValue.r );
	WriteStream<float>( vStream, vValue.g );
	WriteStream<float>( vStream, vValue.b );
	WriteStream<float>( vStream, vValue.a );
}

//-------------------------------------------------------------
// Linear interpolation with colors
template<>
inline void lerp<Color>( Color& result, const Color& value0, const Color& value1, float lerpval )
{
	result.lerp( value0, value1, lerpval );
}

}

#endif
