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

#ifndef MOCHA_RAY_H
#define MOCHA_RAY_H

#include "Mocha/Vector3.h"

namespace Mocha
{

/// A 3D ray with origin and direction
class Ray
{
public:
	/// The origin of the ray
	Vector3 origin;

	/// The direction of the ray
	Vector3 direction;

	/// Constructor
	/*! \param orig The origin of the ray
		\param dir The direction of the ray */
	inline Ray( const Vector3& orig, const Vector3& dir )
	{
		origin = orig;
		direction = dir;
	}

	/// Copy constructor
	/*! \param other The ray to copy */
	inline Ray( const Ray& other )
	{
		origin = other.origin;
		direction = other.direction;
	}

	/// Default constructor
	inline Ray( )
	{
		// ...
	}

	/// Gets a point along the ray at the given time
	/*! \param t The time value to use
		\return The point along the ray at the given time */
	inline Vector3 getPoint( float t ) const
	{
		return origin + ( direction * t );
	}
};

}

#endif
