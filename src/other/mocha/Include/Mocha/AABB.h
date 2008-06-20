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

#ifndef MOCHA_AABB_H
#define MOCHA_AABB_H

#include "Mocha/Math.h"
#include "Mocha/Vector3.h"
#include "Mocha/Matrix.h"
#include "Mocha/Plane.h"
#include "Mocha/Ray.h"

namespace Mocha
{

/// An axis-aligned bounding volume
class AABB
{
private:
	Vector3 min;

	Vector3 max;

	mutable Vector3 corners[8];

	mutable bool dirty;

	inline void flagDirty( )
	{
		dirty = true;
	}

	inline void updateCorners( ) const
	{
		if ( !dirty )
			return;

		corners[0]   = min;
		corners[1].x = min.x; corners[1].y = max.y; corners[1].z = min.z;
		corners[2].x = max.x; corners[2].y = max.y; corners[2].z = min.z;
		corners[3].x = max.x; corners[3].y = min.y; corners[3].z = min.z;  
		corners[4]   = max;
		corners[5].x = min.x; corners[5].y = max.y; corners[5].z = max.z;
		corners[6].x = min.x; corners[6].y = min.y; corners[6].z = max.z;
		corners[7].x = max.x; corners[7].y = min.y; corners[7].z = max.z;

		dirty = false;
	}

public:
	inline AABB( )
	{
		max = Vector3( -FLT_MAX, -FLT_MAX, -FLT_MAX );
		min = Vector3( FLT_MAX, FLT_MAX, FLT_MAX );

		flagDirty( );
	}

	/// Copy constructor
	/*! \param vOther The box to copy */
	inline AABB( const AABB& vOther )
	{
		set( vOther.min, vOther.max );
	}

	/// Constructor
	/*! \param vMin The minimum corner point of the AABB
		\param vMax The maximum corner point of the AABB */
	inline AABB( const Vector3& vMin, const Vector3& vMax )
	{
		set( vMin, vMax );
	}

	/// Resets the bounding box
	inline void reset( )
	{
		max = Vector3( -FLT_MAX, -FLT_MAX, -FLT_MAX );
		min = Vector3( FLT_MAX, FLT_MAX, FLT_MAX );

		flagDirty( );
	}

	/// Checks if the bounding box is valid (Not inverted)
	/*! \return True if the box is valid, false if not */
	inline bool isValid( ) const
	{
		return (max >= min);
	}

	/// Gets the minimum corner point of the box
	/*! \return The minimum corner point of the box */
	inline const Vector3& getMin( ) const
	{
		return min;
	}

	/// Gets the maximum corner point of the box
	/*! \return The maximum corner point of the box */
	inline const Vector3& getMax( ) const
	{
		return max;
	}

	/// Return a pointer to a list of 8 points that make up the box
	/*! \return The pointer to the list points */
	inline const Vector3* getCorners( ) const
	{
		updateCorners( );
		return &corners[0];
	}

	/// Splits the box into four smaller quadrants
	/*! \param vQ1 The box that will be setup as quadrant 1
		\param vQ2 The box that will be setup as quadrant 2
		\param vQ3 The box that will be setup as quadrant 3
		\param vQ4 The box that will be setup as quadrant 4 */
	inline void split( AABB& vQ1, AABB& vQ2, AABB& vQ3, AABB& vQ4 ) const
	{
		Vector3 mid;
		mid = (max - min) * 0.5 + min;

		vQ1.min = min;
		vQ1.max = Vector3( mid.x, max.y, mid.z );

		vQ2.min = Vector3( min.x, min.y, mid.z );
		vQ2.max = Vector3( mid.x, max.y, max.z );

		vQ3.min = Vector3( mid.x, min.y, min.z );
		vQ3.max = Vector3( max.x, max.y, mid.z );

		vQ4.min = Vector3( mid.x, min.y, mid.z );
		vQ4.max = Vector3( max.x, max.y, max.z );
	}

	/// Moves the box by the specified amount
	/*! \param vAmount The Amount to move the box by */
	inline void move( const Vector3& vAmount )
	{
		min += vAmount;
		max += vAmount;

		flagDirty( );
	}

	/// Expands the box by the specified amount
	/*! \param vAmount The amount to expand the box by */
	inline void expand( float vAmount )
	{
		min -= Vector3( vAmount, vAmount, vAmount );
		max += Vector3( vAmount, vAmount, vAmount );

		flagDirty( );
	}

	/// Shrinks the box by the specified amount
	/*! \param vAmount The amount to shrink the box by */
	inline void shrink( float vAmount )
	{
		min += Vector3( vAmount, vAmount, vAmount );
		max -= Vector3( vAmount, vAmount, vAmount );

		flagDirty( );
	}

	/// Transforms the AABB by the specified matrix
	/*! \param vMatrix The matrix to transform the box by */
	inline void transform( const Matrix& vMatrix )
	{
		if ( isValid( ) == false )
			return;

		updateCorners( );

		Vector3 tmin, tmax, temp;
		bool first = true;
		
		int i;
		for( i = 0; i < 8; i++ )
		{
			// Transform and check extents
			temp = vMatrix * corners[i];
			if( first || temp.x > tmax.x )
				tmax.x = temp.x;
			if( first || temp.y > tmax.y )
				tmax.y = temp.y;
			if( first || temp.z > tmax.z )
				tmax.z = temp.z;
			if( first || temp.x < tmin.x )
				tmin.x = temp.x;
			if( first || temp.y < tmin.y )
				tmin.y = temp.y;
			if( first || temp.z < tmin.z )
				tmin.z = temp.z;

			first = false;
		}

		set( tmin, tmax );
	}

	inline AABB& operator = ( const AABB& vOther )
	{
		set( vOther );
		return *this;
	}

	/// Sets the box as a copy of another box
	/*! \param vOther The box to copy */
	inline void set( const AABB& vOther )
	{
		min = vOther.min;
		max = vOther.max;

		flagDirty( );
	}

	/// Sets the box from the minimum and maximum corner points
	/*! \param vMin The minimum corner point to use
		\param vMax The maximum corner point to use */
	inline void set( const Vector3& vMin, const Vector3& vMax )
	{
		min = vMin;
		max = vMax;

		flagDirty( );
	}

	/// Returns whether or not this box has no size
	/*! \return True if the box has no size (It is just a point), false if it has a size */
	inline bool isZero( ) const
	{
		if ( getSize( ).isZero( ) )
			return true;

		return false;
	}

	/// Sets the center and extents of the box
	/*! \param vCenter The center point of the box
		\param vExtent The extents of the box */
	inline void setCenterExtent( const Vector3& vCenter, const Vector3& vExtent )
	{
		set( vCenter - vExtent, vCenter + vExtent );
	}

	/// Gets a Vector3 value that specifies the total size of the box
	/*! \return The size of the box as a Vector3 value */
	inline Vector3 getSize( ) const
	{
		return max - min;
	}

	/// Gets the extents of the box (The size of the box, devided in half)
	/*! \return The extents of the box as a Vector3 value */
	inline Vector3 getExtent( ) const
	{
		return getSize( ) * 0.5f;
	}

	/// Gets the center point of the box
	/*! \return The point at the center of the box */
	inline Vector3 getCenter( ) const
	{
		return (min+max) * 0.5f;
	}

	/// Returns true if the given point is inside the box
	/*! \param vPoint The point to test
		\return True if the point is inside the box, false if not */
	inline bool pointInside( const Vector3& vPoint ) const
	{
		if ( vPoint.x < min.x )
			return false;

		if ( vPoint.y < min.y )
			return false;
            
		if ( vPoint.z < min.z )
			return false;

		if ( vPoint.x > max.x )
			return false;
            
		if ( vPoint.y > max.y )
			return false;
            
		if ( vPoint.z > max.z )
			return false;

		return true;
	}

	/// Extends the box so that it includes the given point
	/*! \param vPoint The point to include in the box */
	inline void extend( const Vector3& vPoint )
	{
		if ( vPoint.x < min.x )
			min.x = vPoint.x;

		if ( vPoint.x > max.x )
			max.x = vPoint.x;

		if ( vPoint.y < min.y )
			min.y = vPoint.y;

		if ( vPoint.y > max.y )
			max.y = vPoint.y;

		if ( vPoint.z < min.z )
			min.z = vPoint.z;

		if ( vPoint.z > max.z )
			max.z = vPoint.z;

		flagDirty( );
	}

	/// Extends the box so that it includes the given box
	/*! \param vOther The other box to include inside this box */
	inline void extend( const AABB& vOther )
	{
		if ( vOther.min.x < min.x )
			min.x = vOther.min.x;

		if ( vOther.min.y < min.y )
			min.y = vOther.min.y;

		if ( vOther.min.z < min.z )
			min.z = vOther.min.z;

		if ( vOther.max.x > max.x )
			max.x = vOther.max.x;

		if ( vOther.max.y > max.y )
			max.y = vOther.max.y;

		if ( vOther.max.z > max.z )
			max.z = vOther.max.z;

		flagDirty( );
	}

	/// Returns whether or not the given box intersects this box
	/*! \param vOther True if the box intersects, false if not */
	inline bool intersects( const AABB& vOther ) const
	{
		if ( max.x < vOther.min.x )
			return false;

		if ( max.y < vOther.min.y )
			return false;
            
		if ( max.z < vOther.min.z )
			return false;

		if ( min.x > vOther.max.x )
			return false;
            
		if ( min.y > vOther.max.y )
			return false;
            
		if ( min.z > vOther.max.z )
			return false;

        return true;
	}

	/// Returns whether or not the given box is entirely contained within this box
	/*! \param other The box to test with
		\return True if the box is contained, false if not */
	inline bool contains( const AABB& other ) const
	{
		if( other.min.x < min.x )
			return false;
		if( other.min.y < min.y )
			return false;
		if( other.min.z < min.z )
			return false;

		if( other.max.x > max.x )
			return false;
		if( other.max.y > max.y )
			return false;
		if( other.max.z > max.z )
			return false;

		return true;
	}

	/// Tests whether or not the given box, transforms by a given matrix, intersects with this box
	/*! \param vOther The box to test
		\param transform The matrix to transform the given box by
		\return True if the box intersects, false if not */
	inline bool intersects( const AABB& vOther, const Matrix& transform ) const
	{
		Vector3 tmin = transform * min;
		Vector3 tmax = transform * max;
		if ( tmax.x < vOther.min.x )
			return false;

		if ( tmax.y < vOther.min.y )
			return false;
            
		if ( tmax.z < vOther.min.z )
			return false;

		if ( tmin.x > vOther.max.x )
			return false;
            
		if ( tmin.y > vOther.max.y )
			return false;
            
		if ( tmin.z > vOther.max.z )
			return false;

        return true;
	}

	/// Tests whether or not the given plane intersects with the box
	/*! \param vPlane The plane to test
		\return True if the plane intersects, false if not */
	inline bool intersects( const Plane& vPlane ) const
	{
		updateCorners( );

        PlaneSide lastSide = vPlane.getSide( corners[0] );

		int corner;
        for ( corner = 1; corner < 8; corner++ )
        {
            if ( vPlane.getSide( corners[corner] ) != lastSide )
                return true;
        }

        return false;
	}

	/// Tests if a ray intersects with the box, given a specific transformation
	/*! \param vRay The ray to test with
		\param vPoint The Vector3 value that will receive the intersection point
		\param vTransform The transform to apply to the ray before testing
		\return True if there is an intersection, false if not */
	inline bool intersects( const Ray& vRay, Vector3& vPoint, const Matrix& vTransform ) const
	{
		Ray tRay = vRay;

		Matrix mat = vTransform;
		mat.simpleInvert( );

		tRay.origin = mat * vRay.origin;
		tRay.direction = mat.rotateVector( vRay.direction );

		if ( intersects( tRay, vPoint ) )
		{
			vPoint = vTransform * vPoint;
			return true;
		}

		return false;
	}

	/// Tests if a ray intersects the box
	/*! \param vRay The ray to test with
		\param vPoint The Vector3 value that receive the point of the intersection
		\return True if there is an intersection, false if not */
	inline bool intersects( const Ray& vRay, Vector3& vPoint ) const
	{
        float t;

        const Vector3& rayorig = vRay.origin;
        const Vector3& raydir = vRay.direction;

        // Check origin inside first
        if ( rayorig > min && rayorig < max )
        {
            return true;
        }

        // Check each face in turn
        // Min x
        if (rayorig.x < min.x && raydir.x > 0)
        {
            t = (min.x - rayorig.x) / raydir.x;
            if (t > 0)
            {
                // Substitute t back into ray and check bounds and dist
                vPoint = rayorig + raydir * t;
                if (vPoint.y >= min.y && vPoint.y <= max.y &&
                    vPoint.z >= min.z && vPoint.z <= max.z )
                {
                    return true;
                }
            }
        }
        // Max x
        if (rayorig.x > max.x && raydir.x < 0)
        {
            t = (max.x - rayorig.x) / raydir.x;
            if (t > 0)
            {
                // Substitute t back into ray and check bounds and dist
                vPoint = rayorig + raydir * t;
                if (vPoint.y >= min.y && vPoint.y <= max.y &&
                    vPoint.z >= min.z && vPoint.z <= max.z )
                {
                    return true;
                }
            }
        }
        // Min y
        if (rayorig.y < min.y && raydir.y > 0)
        {
            t = (min.y - rayorig.y) / raydir.y;
            if (t > 0)
            {
                // Substitute t back into ray and check bounds and dist
                vPoint = rayorig + raydir * t;
                if (vPoint.x >= min.x && vPoint.x <= max.x &&
                    vPoint.z >= min.z && vPoint.z <= max.z )
                {
                    return true;
                }
            }
        }
        // Max y
        if (rayorig.y > max.y && raydir.y < 0)
        {
            t = (max.y - rayorig.y) / raydir.y;
            if (t > 0)
            {
                // Substitute t back into ray and check bounds and dist
                vPoint = rayorig + raydir * t;
                if (vPoint.x >= min.x && vPoint.x <= max.x &&
                    vPoint.z >= min.z && vPoint.z <= max.z )
                {
                    return true;
                }
            }
        }
        // Min z
        if (rayorig.z < min.z && raydir.z > 0)
        {
            t = (min.z - rayorig.z) / raydir.z;
            if (t > 0)
            {
                // Substitute t back into ray and check bounds and dist
                vPoint = rayorig + raydir * t;
                if (vPoint.x >= min.x && vPoint.x <= max.x &&
                    vPoint.y >= min.y && vPoint.y <= max.y )
                {
                    return true;
                }
            }
        }
        // Max z
        if (rayorig.z > max.z && raydir.z < 0)
        {
            t = (max.z - rayorig.z) / raydir.z;
            if (t > 0)
            {
                // Substitute t back into ray and check bounds and dist
                vPoint = rayorig + raydir * t;
                if (vPoint.x >= min.x && vPoint.x <= max.x &&
                    vPoint.y >= min.y && vPoint.y <= max.y )
                {
                    return true;
                }
            }
        }

        return false;
	}
};

}

#endif
