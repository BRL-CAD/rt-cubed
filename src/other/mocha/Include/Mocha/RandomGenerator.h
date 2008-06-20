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

#ifndef MOCHA_RANDOMGENERATOR_H
#define MOCHA_RANDOMGENERATOR_H

#include "Mocha/Platform.h"

#define MT_LEN 624

namespace Mocha
{

/// Simple class for generating high quality random values.
class MOCHA_EXPORT RandomGenerator
{
private:
	unsigned long mBuffer[MT_LEN];

	int mIndex;

public:
	/// Constructor (This does not seed the random generator. Use seed( value ) before using)
	RandomGenerator( );

	/// Constructor
	/*! \param vSeed The random seed value to use */
	RandomGenerator( int vSeed );

	/// Destructor
	~RandomGenerator( );

	/// Seeds the random generator
	/*! \param vValue The value to seed the random generator with */
	void seed( int vValue );

	/// Produces a random integer value
	/*! \return A random integer value */
	unsigned long random( );

	/// Produces a random floating point value within range [vLow, vHigh]
	/*! \param vLow The low range of the value to generate
		\param vHigh The high range of the value to generate
		\return The random floating point value */
	float randomRange( float vLow, float vHigh );

	/// Produces a floating point random value in range [-vValue, vValue]
	/*! \param The value to scale the random value by
		\return The random floating point value */
	float randomFloatPlusMinus( float vValue );

	/// Produces a random boolean value
	bool randomBool( );

	/// Produces a random floating point value
	/*! \return A random floating point value */
	float randomFloat( );
};

}

#endif
