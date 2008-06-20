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

#include "Mocha/Thread.h"
#include "Mocha/Exception.h"

#define STACK_SIZE 4096

namespace Mocha
{

#ifdef WIN32

//--------------------------------
// Entry point for the Win32 thread
DWORD WINAPI Thread::threadProc( LPVOID vParam )
{
	// Get the thread object from the param

	Thread* thread = (Thread*)vParam;

	// Run the thread task

	thread->run( );
	thread->mFinished = true;

	// All done!

	return 0;
}

//--------------------------------
Thread::Thread( )
: mThreadHandle( 0 ), mSignalled( false ), mFinished( false )
{
	// ...
}

//--------------------------------
Thread::~Thread( )
{
	// Flag thread as signalled

	mSignalled = true;

	// Wait for thread to finish

	if ( mThreadHandle )
	{
		// Wait for the thread to exit and close its handle

		WaitForSingleObject( mThreadHandle, INFINITE );
		CloseHandle( mThreadHandle );
	}
}

//--------------------------------
void Thread::setPriority( ThreadPriority vWhich )
{
	switch ( vWhich )
	{
	case THREADPRIORITY_LOW:
        SetThreadPriority( mThreadHandle, THREAD_PRIORITY_BELOW_NORMAL );
		break;

	case THREADPRIORITY_MEDIUM:
		SetThreadPriority( mThreadHandle, THREAD_PRIORITY_NORMAL );
		break;

	case THREADPRIORITY_HIGH:
		SetThreadPriority( mThreadHandle, THREAD_PRIORITY_ABOVE_NORMAL );
		break;
	}
}

//--------------------------------
void Thread::start( )
{
	mSignalled = false;
	mFinished = false;

	// Create the thread

	unsigned int thrdaddr;
	mThreadHandle =	 (HANDLE)_beginthreadex( NULL,    // security
											 STACK_SIZE,	  
											 (unsigned (__stdcall *)(void *))threadProc,
											 this,    // arglist
											 0,       // init_flags
											 &thrdaddr );

	if ( mThreadHandle == 0 )
		throw Exception( "Unable to spawn thread" );
}

//--------------------------------
void Thread::signal( bool vWait )
{
	mSignalled = true;
	if ( vWait && mThreadHandle )
		WaitForSingleObject( mThreadHandle, INFINITE );
}

//--------------------------------
void Thread::wait( int vTimeout ) const
{
	if ( vTimeout < 0 )
		vTimeout = INFINITE;

	WaitForSingleObject( mThreadHandle, vTimeout );
}


//--------------------------------
void Thread::sleep( int vTime )
{
	Sleep( vTime );
}

#elif defined( POSIX )

//--------------------------------
// Entry point for the pthread
void* Thread::threadProc( void* vParam )
{
	// Get the thread object from the param

	Thread* thread = (Thread*)vParam;

	// Run the thread task

	thread->run( );
	thread->mFinished = true;

	pthread_mutex_lock( &thread->mCondMutex );
	pthread_cond_signal(&thread->mCond);
	pthread_mutex_unlock( &thread->mCondMutex );
	// All done!

	return 0;
}

//--------------------------------
Thread::Thread( )
: mThreadHandle( 0 ), mSignalled( false ), mFinished( false )
{
	pthread_cond_init(&mCond, NULL);
	pthread_mutex_init(&mCondMutex, NULL);
}

//--------------------------------
Thread::~Thread( )
{
	// Flag thread as signalled

	mSignalled = true;

	// Wait for thread to finish

	if ( mThreadHandle )
	{
		// Wait for the thread to exit and close its handle

		pthread_join(mThreadHandle, NULL);
	}

	pthread_cond_destroy(&mCond);
	pthread_mutex_destroy(&mCondMutex);
}

//--------------------------------
void Thread::setPriority( ThreadPriority vWhich )
{
	struct sched_param param;
	int policy = SCHED_RR;

	switch ( vWhich )
	{
	case THREADPRIORITY_LOW:
		param.sched_priority = 10;
		break;

	case THREADPRIORITY_MEDIUM:
		param.sched_priority = 0;
		break;

	case THREADPRIORITY_HIGH:
		param.sched_priority = -10;
		break;
	}

	pthread_setschedparam(mThreadHandle, policy, &param);
}

//--------------------------------
void Thread::start( )
{
	mSignalled = false;
	mFinished = false;

	// Create the thread

	unsigned int thrdaddr;

	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);
	pthread_attr_setstacksize(&threadAttr, 120*1024);
	pthread_create(&mThreadHandle, &threadAttr, threadProc, this);
	pthread_attr_destroy(&threadAttr);
}

//--------------------------------
void Thread::signal( bool vWait )
{
	mSignalled = true;
	if ( vWait && mThreadHandle )
		this->wait( INFINITE );
}

//--------------------------------
void Thread::wait( int vTimeout ) const
{
	if(mFinished)
		return;
	if ( vTimeout < 0 )
		vTimeout = INFINITE;
	if(vTimeout == INFINITE)
	{
		pthread_join(mThreadHandle, NULL);
	}
	else
	{
		timeval now;
		gettimeofday(&now, NULL);
		
		timespec time;
		time.tv_sec = now.tv_sec + (vTimeout / 1000);
		time.tv_nsec = ((vTimeout % 1000) * 1000000) +
			(now.tv_usec * 1000);


		pthread_mutex_lock( (pthread_mutex_t*)&mCondMutex );
		pthread_cond_timedwait((pthread_cond_t*) &mCond, 
			(pthread_mutex_t*) &mCondMutex, &time);
		pthread_mutex_unlock((pthread_mutex_t*)&mCondMutex);
	}
}


//--------------------------------
void Thread::sleep( int vTime )
{
	usleep(vTime * 1000);
}

#else
#error "No thread implementation"
#endif

//--------------------------------
bool Thread::getSignalled( ) const
{
	return mSignalled;
}

//--------------------------------
bool Thread::getFinished( ) const
{
	return mFinished;
}

}
