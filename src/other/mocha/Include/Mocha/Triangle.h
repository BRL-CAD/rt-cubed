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

#ifndef MOCHA_TRIANGLE_H
#define MOCHA_TRIANGLE_H

#include <list>

#include "Mocha/Matrix.h"
#include "Mocha/Plane.h"
#include "Mocha/Ray.h"

namespace Mocha
{

/// A 3D triangle with support for ray intersection
class Triangle
{
public:
	Vector3 points[3];

	Plane plane;

	int tag;

	inline Triangle( )
	{
		tag = 0;
	}

	inline Triangle( const Triangle& other )
	{
		points[0] = other.points[0];
		points[1] = other.points[1];
		points[2] = other.points[2];

		tag = other.tag;

		calculate( );
	}

	inline Triangle( const Vector3& point1, const Vector3& point2, const Vector3& point3, int t = 0 )
	{
		points[0] = point1;
		points[1] = point2;
		points[2] = point3;

		tag = t;
		
		calculate( );
	}

	inline bool pointInside( const Vector3& vPoint ) const
	{
		Vector3 p1 = points[0] - vPoint;
		p1.normalize( );

		Vector3 p2 = points[1] - vPoint;
		p2.normalize( );

		Vector3 p3 = points[2] - vPoint;
		p3.normalize( );

		float v1 = acos( p1 % p2 );
		float v2 = acos( p2 % p3 );
		float v3 = acos( p3 % p1 );

		float val = v1 + v2 + v3;
		if ( fuzzycmp( val, (2*PI) ) )
			return true;

		return false;
	}

	inline bool pointOnPlane( const Vector3& vPoint ) const
	{
		float d = (float)plane.getDistance( vPoint );
		if ( fuzzycmp( d, 0.0f ) )
			return true;

		return false;
	}

	inline void calculate( )
	{
		plane.set( points[0], points[1], points[2] );
	}

	bool rayIntersect( const Ray &ray, const Matrix& matrix, bool flipped, Vector3& outPoint, Vector3& outNormal )
	{
		const double epsilon = 0.0000001f;

		Vector3 orig = ray.origin;
		Vector3 dir = ray.direction;

		Vector3 edge1, edge2, tvec, pvec, qvec;
		double det,inv_det;

		dir.normalize();

		Vector3 point0_transformed = matrix * points[0];

		if( !flipped )
		{
			edge1 = (matrix * points[1]) - point0_transformed;
			edge2 = (matrix * points[2]) - point0_transformed;
		}
		else
		{
			edge1 = (matrix * points[2]) - point0_transformed;
			edge2 = (matrix * points[1]) - point0_transformed;
		}

		pvec = dir.crossProduct(edge2);

		det = edge1.dotProduct(pvec);

		if (det < epsilon)
			return false;

		tvec = orig - (matrix * points[0]);

		outPoint.x = tvec.dotProduct(pvec);
		if ( (outPoint.x < 0.0) || (outPoint.x > det) )
			return false;

		qvec = tvec.crossProduct(edge1);

		outPoint.y = dir.dotProduct(qvec);
		if ( (outPoint.y < 0.0) || ((outPoint.x + outPoint.y) > det) )
			return false;

		outPoint.z = edge2.dotProduct(qvec);

		inv_det = 1.0f / det;

		outPoint.x *= (float)inv_det;
		outPoint.y *= (float)inv_det;
		outPoint.z *= (float)inv_det;

		Vector3 Final_Point = orig + (dir * outPoint.z);
		outPoint = Final_Point;

		outNormal = edge1.crossProduct( edge2 );

		return true;
	}
};

}

#endif
