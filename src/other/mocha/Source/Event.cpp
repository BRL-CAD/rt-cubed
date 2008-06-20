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

#include "Mocha/Event.h"
#include "Mocha/Exception.h"

namespace Mocha
{

#ifdef WIN32

//--------------------------------------------
Event::Event( )
{
	mHandle = CreateEvent( 0, 0, 0, 0 );
	if ( mHandle == 0 )
		throw Mocha::Exception( "Unable to create Win32 Event handle" );
}

//--------------------------------------------
Event::~Event( )
{
	if ( mHandle )
		CloseHandle( mHandle );
}

//--------------------------------------------
void Event::raise( )
{
	SetEvent( mHandle );
}

//--------------------------------------------
bool Event::wait( int vTime ) const
{
	if ( vTime < 0 )
		vTime = INFINITE;

	DWORD res = WaitForSingleObject( mHandle, vTime );
	if ( res == WAIT_TIMEOUT )
		return false;

	return true;
}

#elif defined( POSIX )

//--------------------------------------------
Event::Event( )
{
	sem_init(mHandle, 0, 0);
//	if ( !mHandle )
//		throw Mocha::Exception( "Unable to create POSIX Event 
//handle" );
}

//--------------------------------------------
Event::~Event( )
{
//	if ( !mHandle )
		sem_destroy(mHandle);
}

//--------------------------------------------
void Event::raise( )
{
	sem_post(mHandle);
}

//--------------------------------------------
bool Event::wait( int vTime ) const
{
	sem_wait(mHandle);
	return true;
}

#else
#error "No event implementation"
#endif

}
