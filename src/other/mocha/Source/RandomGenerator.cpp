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

#include "Mocha/RandomGenerator.h"
#include "Mocha/Math.h"

#define MAX_NUMBER		0xFFFFFFFF
#define MT_IA           397
#define MT_IB           (MT_LEN - MT_IA)
#define UPPER_MASK      0x80000000
#define LOWER_MASK      0x7FFFFFFF
#define MATRIX_A        0x9908B0DF
#define TWIST(b,i,j)    ((b)[i] & UPPER_MASK) | ((b)[j] & LOWER_MASK)
#define MAGIC(s)        (((s)&1)*MATRIX_A)

namespace Mocha
{

//--------------------------------
RandomGenerator::RandomGenerator( )
{
	mIndex = MT_LEN * sizeof( unsigned long );
}

//--------------------------------
RandomGenerator::RandomGenerator( int vSeed )
{
	seed( vSeed );
}

//--------------------------------
RandomGenerator::~RandomGenerator( )
{
	// ...
}

//--------------------------------
void RandomGenerator::seed( int vValue )
{
    mBuffer[0]= vValue & 0xffffffffUL;

	int mti;
    for ( mti = 1; mti < MT_LEN; mti++ )
	{
        mBuffer[mti] = (1812433253UL * (mBuffer[mti-1] ^ (mBuffer[mti-1] >> 30)) + mti); 

        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */

        mBuffer[mti] &= 0xffffffffUL;

        /* for >32 bit machines */
    }

	mIndex = MT_LEN * sizeof( unsigned long );
	mBuffer[0] = 0x80000000UL;
}

//--------------------------------
unsigned long RandomGenerator::random( )
{
    unsigned long * b = mBuffer;
    int idx = mIndex;
    unsigned long s;
    int i;
	
    if ( idx >= MT_LEN * sizeof( unsigned long ) )
    {
        idx = 0;
        i = 0;

        for ( ; i < MT_IB; i++ )
		{
            s = TWIST( b, i, i+1 );
            b[i] = b[i + MT_IA] ^ (s >> 1) ^ MAGIC(s);
        }

        for ( ; i < MT_LEN-1; i++ )
		{
            s = TWIST( b, i, i+1 );
            b[i] = b[i - MT_IB] ^ (s >> 1) ^ MAGIC(s);
        }
        
        s = TWIST(b, MT_LEN-1, 0);
        b[MT_LEN-1] = b[MT_IA-1] ^ (s >> 1) ^ MAGIC(s);
    }

    mIndex = idx + sizeof(unsigned long);
    return *(unsigned long *)((unsigned char *)b + idx);
}

//--------------------------------
float RandomGenerator::randomFloatPlusMinus( float vValue )
{
	return (randomFloat( ) * 2.0f - 1.0f) * vValue;
}

//--------------------------------
float RandomGenerator::randomRange( float vLow, float vHigh )
{
	float res;
	lerp( res, vLow, vHigh, randomFloat( ) );

	return res;
}

//--------------------------------
bool RandomGenerator::randomBool( )
{
	return (randomFloat( ) > 0.5f);
}

//--------------------------------
float RandomGenerator::randomFloat( )
{
	return (float)random( ) / MAX_NUMBER;
}

}
