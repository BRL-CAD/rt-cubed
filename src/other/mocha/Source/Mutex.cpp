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

#include "Mocha/Mutex.h"

#ifdef POSIX
#include <pthread.h>
#ifdef __FreeBSD__
#include <pthread_np.h>
#endif
#endif

namespace Mocha
{

#ifdef WIN32

//--------------------------------------------
Mutex::Mutex( )
{
	InitializeCriticalSection( &mCritSection );
}

//--------------------------------------------
Mutex::~Mutex( )
{
	DeleteCriticalSection( &mCritSection );
}

//--------------------------------------------
void Mutex::lock( )
{
	EnterCriticalSection( &mCritSection );
}

//--------------------------------------------
void Mutex::unlock( )
{
	LeaveCriticalSection( &mCritSection );
}

//--------------------------------------------
bool Mutex::request( )
{
	return (TryEnterCriticalSection( &mCritSection ) == 0);
}

#elif defined( POSIX )

//--------------------------------------------
Mutex::Mutex( )
{
	pthread_mutexattr_t mutexattr;
	#ifdef __FreeBSD__
	pthread_mutexattr_setkind_np(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
	#else
	pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);
	#endif
	pthread_mutex_init(&mCritSection, &mutexattr);
	pthread_mutexattr_destroy(&mutexattr);
}

//--------------------------------------------
Mutex::~Mutex( )
{
	pthread_mutex_destroy( &mCritSection );
}

//--------------------------------------------
void Mutex::lock( )
{
	pthread_mutex_lock(&mCritSection);
}

//--------------------------------------------
void Mutex::unlock( )
{
	pthread_mutex_unlock(&mCritSection);
}

//--------------------------------------------
bool Mutex::request( )
{
	return (pthread_mutex_trylock( &mCritSection ) == 0);
}

#else
#error "No Mutex implementation"
#endif

}
