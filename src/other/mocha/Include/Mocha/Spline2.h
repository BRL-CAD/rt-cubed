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

#ifndef MOCHA_SPLINE2_H
#define MOCHA_SPLINE2_H

#include "Mocha/Vector2.h"

namespace Mocha
{

/// A spline composed of a list of 2D points
class Spline2
{
private:
    Vector2List mBasePoints;

	Vector2List mTesPoints;

public:
	inline Spline2( )
	{
		// ...
	}

	inline ~Spline2( )
	{
		// ...
	}

	/// Removes all points from the spline
	inline void clear( )
	{
		mBasePoints.clear( );
	}

	/// Adds a point to the spline
	inline void addPoint( const Vector2& vPoint )
	{
		mBasePoints.push_back( vPoint );
	}

	/// Inserts a point within the spline
	inline void insertPoint( size_t vAfter, Vector2& vPoint )
	{
        mBasePoints.insert( mBasePoints.begin() + vAfter, vPoint );
	}

	/// Removes a point from the spline
	inline void removePoint( size_t vIndex )
	{
        mBasePoints.erase( mBasePoints.begin() + vIndex );
	}

	/// Gets the list of ponts
	inline Vector2List& getPointList( )
	{
		return mBasePoints;
	}

	/// Sets the spline points
	inline void setPoints( const Vector2List& vPoints )
	{
		mBasePoints = vPoints;
	}

	/// Tesselates the spline
	/*! \param vRes The resolution of the tessellation */
	inline Vector2List& tessellate( int vRes )
	{
        mTesPoints.resize( (int)((int)(mBasePoints.size( )-1) * pow( (float)2, vRes ) + 1) );

		// Prepopulate output

		int step = (int)pow( (float)2, vRes );

		int a;
		for( a = 0; a < (int)mBasePoints.size( ); a ++ )
		{
			mTesPoints[a*step] = mBasePoints[a];
		}

		int res;
		for( res = vRes; res > 0; res -- )
		{
            int step = (int)pow( (float)2, res );
			int hstep = step / 2;

			// Interpolate 1

			int a;

			for( a = hstep; a < (int)mTesPoints.size(); a += step )
			{
				if( (a - hstep >= 0) && (a+hstep < (int)mTesPoints.size()) )
				{
					mTesPoints[a] = (mTesPoints[a-hstep] + mTesPoints[a+hstep]) * 0.5f;
				}
			}

			// Interpolate 2

			for( a = 0; a < (int)mTesPoints.size(); a += step )
			{
				if( (a - hstep >= 0) && (a+hstep < (int)mTesPoints.size()) )
				{
					Vector2 Temp = (mTesPoints[a-hstep] + mTesPoints[a+hstep]) * 0.5f;
					mTesPoints[a] = (mTesPoints[a] + Temp) * 0.5f;
				}
			}
		}

		return mTesPoints;
	}

	/// Gets the list of tessellated points
	inline Vector2List& getTessellatePointList( )
	{
		return mTesPoints;
	}

	/// Samples a value along the Y axis
	inline float sampleY( float vY ) const
	{
		if( mTesPoints.size() < 2 )
			return 0;

		if( vY <= mTesPoints.front().y )
			return mTesPoints.front().x;

		if( vY >= mTesPoints.back().y )
			return mTesPoints.back().x;

		int a;
       	for( a = 1; a < (int)mTesPoints.size(); a ++ )
		{
			if( mTesPoints[a].y >= vY )
			{
				float y1 = mTesPoints[a-1].y;
				float x1 = mTesPoints[a-1].x;
				float y2 = mTesPoints[a].y;
				float x2 = mTesPoints[a].x;

				float p = (vY - y1) / (y2-y1);

				return (x2 - x1) * p + x1;
			}
		}

		return 0.0f;
	}
};

}

#endif
