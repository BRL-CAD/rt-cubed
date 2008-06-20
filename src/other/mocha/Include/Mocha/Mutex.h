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

#ifndef MOCHA_MUTEX_H
#define MOCHA_MUTEX_H

#ifdef WIN32
#define _WIN32_WINNT 0x0400
#define _WINSOCKAPI_
#include <windows.h>
#undef _WIN32_WINNT
#elif defined( POSIX )
#include <pthread.h>
#endif

#include "Mocha/Platform.h"


namespace Mocha
{

//--------------------------------------------
/// Encapsulates a mutex object for thread synchronization
class MOCHA_EXPORT Mutex
{
private:

#ifdef WIN32
	CRITICAL_SECTION mCritSection;
#elif defined( POSIX )
	pthread_mutex_t	mCritSection;
#endif

public:
	Mutex( );

	~Mutex( );

	/// Locks the mutex, blocks until access is granted
	void lock( );

	/// Unlocks the mutex
	void unlock( );

	/// Tries to enter the mutex, but does not block
	/*! \return True if the mutex was entered, false if not */
	bool request( );
};

//--------------------------------------------
class MutexScopeLock
{
private:
	Mutex* mMutex;

public:
	inline MutexScopeLock( )
	{
		mMutex = 0;
	}

	inline MutexScopeLock( Mutex* vMutex ) : mMutex( vMutex )
	{
		if ( mMutex )
			mMutex->lock( );
	}

	inline MutexScopeLock( Mutex& vMutex ) : mMutex( &vMutex )
	{
		mMutex->lock( );
	}

	inline ~MutexScopeLock( )
	{
		if ( mMutex )
			mMutex->unlock( );
	}
};

}

#endif
