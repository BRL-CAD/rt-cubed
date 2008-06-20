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

#ifndef MOCHA_MATH_H
#define MOCHA_MATH_H

#include "Mocha/Platform.h"

#include <math.h>
#include <float.h>

#undef min
#undef max

//////////////////////////////////////////////////////////////

// Aliases for matrix components

#define M11 m[0][0]
#define M12 m[0][1]
#define M13 m[0][2]
#define M14 m[0][3]
#define M21 m[1][0]
#define M22 m[1][1]
#define M23 m[1][2]
#define M24 m[1][3]
#define M31 m[2][0]
#define M32 m[2][1]
#define M33 m[2][2]
#define M34 m[2][3]
#define M41 m[3][0]
#define M42 m[3][1]
#define M43 m[3][2]
#define M44 m[3][3]

//////////////////////////////////////////////////////////////

// We provide an alias here for many common math functions
// so that we may easily provide optimizations for them on
// certain platforms.

namespace Mocha
{

//--------------------------------------------
const float PI = (3.1415926535897932384626433832795028841971693993751f);
const float RADIAN = 57.2957795f;
const float TINY = (0.0000001f);

//--------------------------------------------
inline float acos( float x )
{
	if(x >  1.0f) x =  1.0f;
	if(x < -1.0f) x = -1.0f;
	return (float)::acos( x );
}

//--------------------------------------------
inline float cos( float x )
{
	return (float)::cos( x );
}

//--------------------------------------------
inline float abs( float x )
{
	return (float)::fabs( x );
}

//--------------------------------------------
inline float tan( float x )
{
	return (float)::tan( x );
}

//--------------------------------------------
inline float sin( float x )
{
	return (float)::sin( x );
}

//--------------------------------------------
inline float sqrt( float n )
{
	return (float)::sqrt( n );
}

//--------------------------------------------
inline float floor( float n )
{
	return (float)::floor( n );
}

//--------------------------------------------
inline float fsign( float n )
{
	if ( n < 0.0f )
		return -1.0f;

	return 1.0f;
}

//--------------------------------------------
inline bool checkRange( int vValue, int vLow, int vHigh )
{
	return ( (vValue >= vLow) && (vValue <= vHigh) );
}

//--------------------------------------------
inline bool checkRange( float vValue, float vLow, float vHigh )
{
	return ( (vValue >= vLow) && (vValue <= vHigh) );
}

//--------------------------------------------
inline float clamp( float value, float min = 0.0f, float max = 1.0f, float adjust = 0.0f )
{
	if ( value < min )
		value = min;
	else if ( value >= max )
		value = max - adjust;

	return value;
}

//--------------------------------------------
inline float saturate( float value )
{
	if ( value < 0.0f )
		value = 0.0f;
	else if ( value > 1.0f )
		value = 1.0f;

	return value;
}

//--------------------------------------------
inline float min( float vvalue, float vmin )
{
	if ( vvalue < vmin )
		return vvalue;

	return vmin;
}

//--------------------------------------------
inline float max( float vvalue, float vmax )
{
	if ( vvalue > vmax )
		return vvalue;

	return vmax;
}

//--------------------------------------------
inline int fround( float v )
{
	return (int)(v + 0.5f);
}

//--------------------------------------------
inline float radtodeg( float v )
{
	return v * RADIAN;
}

//--------------------------------------------
inline float degtorad( float v )
{
	return v / RADIAN;
}

//--------------------------------------------
inline float floatModulos( float Value, float Base )
{
	// Try returing the result of 'fmod()' and see the problems!

	if( Value >= Base )
		Value -= static_cast<int>(Value / Base) * Base;
	if( Value < 0 )
		Value += (static_cast<int>(-Value / Base) + 1) * Base;
	return Value;
}

//--------------------------------------------
inline bool fuzzycmp( float v1, float v2, float vAmount = 0.00001 )
{
	if ( fabs( v1 - v2 ) <= vAmount )
		return true;

	return false;
}

//--------------------------------------------
inline float shortestRotationDistance( float Value1, float Value2 )
{
	// Direct Route

	float directRoute = abs( Value1 - Value2 );

	// Indirect Route

	float indirectRouteA = abs( Value1 - 360 ) + abs( Value2 );
	float indirectRouteB = abs( Value1 ) + abs( Value2 - 360 );
	float indirectRoute = ( indirectRouteA < indirectRouteB ) ? indirectRouteA : indirectRouteB;
	
	return ( directRoute < indirectRoute ) ? directRoute : indirectRoute;
}

//--------------------------------------------
inline bool shortestRotationIsInverted( float Value1, float Value2 )
{
	// Direct Route

	float directRoute = abs( Value1 - Value2 );

	// Indirect Route

	float indirectRouteA = abs( Value1 - 360 ) + abs( Value2 );
	float indirectRouteB = abs( Value1 ) + abs( Value2-360 );
	float indirectRoute = ( indirectRouteA < indirectRouteB ) ? indirectRouteA : indirectRouteB;
	
	return (directRoute < indirectRoute) ? false : true;
}

//--------------------------------------------
inline float gravitateAngle( float vVar, float vDesired, float vDelta, float vAdjust = 1.0f )
{	
	float shortestDist = shortestRotationDistance( vDesired, vVar );
	
	if( shortestRotationIsInverted( vDesired, vVar ) )
	{
		if( vVar < vDesired )
		{
			vVar -= (shortestDist * vAdjust) * vDelta;
		}
		else if( vVar > vDesired )
		{
			vVar += (shortestDist * vAdjust) * vDelta;
		}
	}
	else
	{
		if( vVar < vDesired )
		{
			vVar += (shortestDist * vAdjust) * vDelta;
			if( vVar > vDesired )
				vVar = vDesired;
		}
		else if( vVar > vDesired )
		{
			vVar -= (shortestDist * vAdjust) * vDelta;
			if( vVar < vDesired )
				vVar = vDesired;
		}
	}

	return floatModulos( vVar, 360.0f );
}

//--------------------------------------------
inline float gravitateValue( float vVar, float vDesired, float vDelta, float vAdjust = 1.0f )
{
	if( vVar < vDesired )
	{
		vVar += ((vDesired - vVar) * vAdjust) * vDelta;
		if( vVar > vDesired )
			vVar = vDesired;
	}
	else if( vVar > vDesired )
	{
		vVar -= ((vVar - vDesired) * vAdjust) * vDelta;
		if( vVar < vDesired )
			vVar = vDesired;
	}

	return vVar;
}

//--------------------------------------------
template <class T>
inline void lerp( T& result, const T& value0, const T& value1, float lerpval )
{
	// ...
}

//--------------------------------------------
template <>
inline void lerp<int>( int& result, const int& value0, const int& value1, float lerpval )
{
	result = fround( (float)value0 + ( ( (float)value1 - (float)value0 ) * lerpval ) );
}

//--------------------------------------------
template <>
inline void lerp<float>( float& result, const float& value0, const float& value1, float lerpval )
{
	result = value0 + ( ( value1 - value0 ) * lerpval );
}

}

#endif
