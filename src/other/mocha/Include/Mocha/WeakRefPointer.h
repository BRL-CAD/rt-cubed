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

#ifndef MOCHA_WEAKREFPOINTER_H
#define MOCHA_WEAKREFPOINTER_H

namespace Mocha
{

/// Holds a weak reference to an object that does not stop the object from being garbage collected
template <class T>
class WeakRefPointer
{
private:
	T* mPtr;

public:
	inline WeakRefPointer( )
	{
		mPtr = 0;
	}

	inline WeakRefPointer( const WeakRefPointer<T>& vOther )
	{
		mPtr = 0;
		set( vOther.mPtr );
	}

	inline WeakRefPointer( T* vPtr )
	{
		mPtr = 0;
		set( vPtr );
	}

	inline ~WeakRefPointer( )
	{
		release( );
	}

	inline bool isNull( ) const
	{
		if ( mPtr == 0 )
			return true;

		return false;
	}

	inline bool isValid( ) const
	{
		if ( mPtr != 0 )
			return true;

		return false;
	}

	inline void release( )
	{
		if ( mPtr )
		{
			mPtr->freeWeakRef( (void**)&mPtr );
			mPtr = 0;
		}
	}

	inline void set( const WeakRefPointer<T>& vOther )
	{
		set( vOther.get( ) );
	}

	inline void set( T* vPtr )
	{
		if ( vPtr )
			vPtr->grabWeakRef( (void**)&mPtr );

		release( );

		mPtr = vPtr;
	}

	inline WeakRefPointer<T>& operator = ( const WeakRefPointer<T>& vOther )
	{
		set( vOther.mPtr );
		return *this;
	}

	inline WeakRefPointer<T>& operator = ( T* vPtr )
	{
		set( vPtr );
		return *this;
	}

	inline bool operator == ( const WeakRefPointer<T>& vOther ) const
	{
		return ( vOther.ptr == mPtr );
	}

	inline bool operator == ( T* vOther ) const
	{
		return ( vOther == mPtr );
	}

	inline bool operator != ( const WeakRefPointer<T>& vOther ) const
	{
		return ( vOther.ptr != mPtr );
	}

	inline bool operator != ( T* vOther ) const
	{
		return ( vOther != mPtr );
	}

	inline T* get( ) const
	{
		return mPtr;
	}

	inline operator T* ( ) const
	{
		return get( );
	}

	inline T* operator -> ( ) const
	{
		return get( );
	}
};

}

#endif
