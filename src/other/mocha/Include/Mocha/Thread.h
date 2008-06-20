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

#ifndef MOCHATHREAD_H
#define MOCHATHREAD_H

#include "Mocha/Platform.h"
#include "Mocha/Object.h"

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#include <process.h>
#else

#include <pthread.h>
#define INFINITE      0xFFFFFFFF
#endif

namespace Mocha
{

//--------------------------------
enum ThreadPriority
{
	THREADPRIORITY_BACKROUND = 0,
	THREADPRIORITY_LOW,
	THREADPRIORITY_MEDIUM,
	THREADPRIORITY_HIGH
};

//--------------------------------
/// Abstraction class for a hardware thread
class MOCHA_EXPORT Thread : public Object
{
private:

#ifdef WIN32
	static DWORD WINAPI threadProc( LPVOID vParam );
	HANDLE mThreadHandle;
#endif

#ifdef POSIX
	static void* threadProc( void* vParam);

	pthread_t mThreadHandle;
	pthread_cond_t mCond;
	pthread_mutex_t mCondMutex;
#endif

	bool mFinished;

	bool mSignalled;

protected:
	virtual void run( ) = 0;

	void sleep( int vTime = 0 );

public:
	Thread( );

	virtual ~Thread( );

	/// Sets the priority level of the thread (See ThreadPriority)
	void setPriority( ThreadPriority vWhich );

	/// Gets whether or not the thread has been signalled to stop running
	bool getSignalled( ) const;
	
	/// Gets whether or not the thread has finished running
	bool getFinished( ) const;

	/// Request the thread to stop running
	/*! \param vWait True to block until the thread is done, false to return immediately */
	void signal( bool vWait = false );

	/// Start executing the thread
	void start( );

	/// Wait for the thread to finish running
	/*! \param vTimeout The maximum amount of time to wait, in milliseconds. Use -1 to wait forever */
	void wait( int vTimeout = -1 ) const;
};

}

#endif
