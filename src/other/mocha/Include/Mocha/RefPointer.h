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

#ifndef MOCHA_REFPTR_H
#define MOCHA_REFPTR_H

namespace Mocha
{

/// Holds a reference to an object
template <class T>
class RefPointer
{
private:
	T* mPtr;

public:
	inline RefPointer( )
	{
		mPtr = 0;
	}

	inline RefPointer( const RefPointer<T>& vOther )
	{
		mPtr = 0;
		set( vOther.mPtr );
	}

	inline RefPointer( T* vPtr )
	{
		mPtr = 0;
		set( vPtr );
	}

	inline ~RefPointer( )
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
			mPtr->decRef( );
			mPtr = 0;
		}
	}

	inline void set( const RefPointer<T>& vOther )
	{
		set( vOther.get( ) );
	}

	inline void set( T* vPtr )
	{
		if ( vPtr )
			vPtr->incRef( );

		release( );

		mPtr = vPtr;
	}

	inline RefPointer<T>& operator = ( const RefPointer<T>& vOther )
	{
		set( vOther.mPtr );
		return *this;
	}

	inline RefPointer<T>& operator = ( T* vPtr )
	{
		set( vPtr );
		return *this;
	}

	inline bool operator == ( const RefPointer<T>& vOther ) const
	{
		return ( vOther.mPtr == mPtr );
	}

	inline bool operator == ( T* vOther ) const
	{
		return ( vOther == mPtr );
	}

	inline bool operator != ( const RefPointer<T>& vOther ) const
	{
		return ( vOther.mPtr != mPtr );
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
