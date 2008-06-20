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

#ifndef MOCHA_SPHERE_H
#define MOCHA_SPHERE_H

#include "Mocha/Vector3.h"
#include "Mocha/Plane.h"
#include "Mocha/Ray.h"

namespace Mocha
{

/// A sphere in 3D space
class Sphere
{
public:
	/// The center point of the sphere
	Vector3 center;

	/// The radius of the sphere
	float radius;

	/// Constructor
	/*! \param vCenter The center point of the sphere
		\param vRadius The radius of the sphere */
	inline Sphere( const Vector3& vCenter, float vRadius )
	{
		center = vCenter;
		radius = vRadius;
	}

	/// Copy constructor
	/*! \param vOther The sphere to copy */
	inline Sphere( const Sphere& vOther )
	{
		center = vOther.center;
		radius = vOther.radius;
	}

	/// Default constructor
	inline Sphere( )
	{
		radius = 0.0f;
	}

	/// Gets the squared radius of the sphere
	/*! \return The radius of the sphere, squared */
	inline float radiusSquared( ) const
	{
		return radius * radius;
	}

	/// Tests if the given sphere intersects this sphere
	/*! \param vOther The sphere to test with
		\return True if there is an intersection, false otherwise */
	inline bool intersects( const Sphere& vOther ) const
	{
		float total = radius + vOther.radius;
		if ( center.squaredDistance( vOther.center ) <= ( total * total ) )
			return true;

		return false;
	}

	/// Tests if the given plane intersects the sphere
	/*! \param vPlane The plane to test with
		\return True if there is an intersection, false otherwise */
	inline bool intersects( const Plane& vPlane ) const
	{
		if ( abs( vPlane.normal % center ) <= radius )
			return true;

		return false;
	}

	/// Tests to see if a line segments intesects the sphere
	/*! \param v1 First point of line segment
		\param v2 Second point of line segment
		\param vPoint1 The Vector3 value to receive the point of the intersection 
		\return True if there is an intersection, false otherwise */
	inline bool intersects( const Vector3& v1, const Vector3& v2, Vector3& vPoint1 ) const
	{
		float a, b, c, d;

		Vector3 posDelta = v1 - center;
		Vector3 dir = v2 - v1;
		dir.normalize( );

		a = dir % dir;
		b = (posDelta % dir) * 2;
		c = (posDelta % posDelta) - radiusSquared( );

        d = b * b - 4 * a * c;

		if ( d < 0.0f )
			return false;

		d = sqrt( d );
		a *= 2;

		float t1;
		float t2;

		t1 = (-b + d) / a;
		t2 = (-b - d) / a;

		if ( t1 < 0 && t2 < 0)
			return false;

		vPoint1 = v1 + (dir * t2);
		return true;
	}

	/// Tests to see if a ray intersects the sphere
	/*! \param vRay The ray to test with
		\param vPoint The Vector3 to receive the point of the intersection
		\return True if there is an intersection, false otherwise */
	inline bool intersects( const Mocha::Ray& vRay, Vector3& vPoint ) const
	{
		return intersects( vRay.origin, vRay.origin + (vRay.direction * 100000.0f), vPoint ); 
	}
};

}

#endif
