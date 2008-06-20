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

#ifndef MOCHA_REFCOUNTED_H
#define MOCHA_REFCOUNTED_H

#include <algorithm>
#include <vector>

#include "Mocha/Platform.h"

namespace Mocha
{

/// Base class for all reference counted objects
class MOCHA_EXPORT RefCounted
{
private:
	typedef std::vector<void**> WeakRefList;
	WeakRefList mWeakRefs;

	size_t mRefCount;

public:
	inline RefCounted( )
		: mRefCount( 0 )
	{
		// ...
	}

	virtual ~RefCounted( )
	{
		// ...
	}

	virtual void deleteMe( )
	{
		delete this;
	}

	inline void incRef( )
	{
		mRefCount++;
	}

	inline bool decRef( )
	{
		if ( mRefCount <= 1 )
		{
			// Reset all weak references

			WeakRefList::const_iterator it;
			for ( it = mWeakRefs.begin( ); it != mWeakRefs.end( ); it++ )
				*(*it) = 0;

			// Free memory

			deleteMe( );
			return true;
		}

		// Decrement reference count

		mRefCount--;
		return false;
	}

	inline size_t getRefCount( ) const
	{
		return mRefCount;
	}

	inline size_t getWeakRefCount( ) const
	{
		return mWeakRefs.size( );
	}

	inline void grabWeakRef( void** vPtr )
	{
		mWeakRefs.push_back( vPtr );
	}

	inline void freeWeakRef( void** vPtr )
	{
		WeakRefList::iterator it = std::find( mWeakRefs.begin( ), mWeakRefs.end( ), vPtr );
		if ( it != mWeakRefs.end( ) )
			mWeakRefs.erase( it );
	}
};

}

#endif
