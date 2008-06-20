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

#ifndef MOCHA_PLANE_H
#define MOCHA_PLANE_H

#include "Mocha/Vector3.h"
#include "Mocha/Ray.h"

namespace Mocha
{

//--------------------------------
enum PlaneSide
{
	PLANESIDE_NONE,
	PLANESIDE_POSITIVE,
	PLANESIDE_NEGATIVE
};

//--------------------------------
/// A plane in 3D space
class Plane
{
public:
	Vector3 normal;

	Vector3 origin;

	float d;

	inline Plane( )
	{
		d = 0.0f;
	}

	inline Plane( const Vector3& vOrigin, const Vector3& vNormal ) 
	{
		normal = vNormal;
		origin = vOrigin;

		d = -( normal.x * origin.x + normal.y * origin.y + normal.z * origin.z );
	}

	inline Plane( const Vector3& p1, const Vector3& p2, const Vector3& p3 )
	{
		set( p1, p2, p3 );
	}

	inline Plane( const Plane& vOther )
	{
		normal = vOther.normal;
		origin = vOther.origin;
		d = vOther.d;
	}

	inline bool isFrontFacingTo( const Vector3& direction ) const
	{
		double dot = normal.dotProduct(direction);
		return ( dot <= 0.0f );
	}

	inline void set( const Vector3& p1, const Vector3& p2, const Vector3& p3 )
	{
		normal = ( p2 - p1 ).crossProduct( p3 - p1 );
		normal.normalize( );

		origin = p1;

		// D = -dot( normal, origin )
		d = -( normal.x * origin.x + normal.y * origin.y + normal.z * origin.z );
	}

	inline PlaneSide getSide( const Vector3& point ) const
	{
        double dist = getDistance( point );

        if ( dist < 0.0f )
            return PLANESIDE_NEGATIVE;

        if ( dist > 0.0 )
            return PLANESIDE_POSITIVE;

        return PLANESIDE_NONE;
	}

	inline double getDistance( const Vector3& point ) const
	{
		return ( point.dotProduct( normal ) ) + d;
	}

	inline bool intersects( const Ray& vRay, Vector3& point ) const
	{
		float dp = vRay.direction.dotProduct( normal );
		if( fabs( dp ) < 0.0001f )
		{
			return false;
		}

		float t = -(vRay.origin.dotProduct( normal ) + d) / dp;
		if( t >= 0 )
		{
			point = vRay.origin + (vRay.direction * t);
			return true;
		}
		return false;
	}
};

}

#endif
