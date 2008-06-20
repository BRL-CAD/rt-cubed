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

#include <iostream>

#include "Mocha/Log.h"

namespace Mocha
{

//--------------------------------
Log::Log( const String& vLogName )
#ifdef WIN32
: mLogFile( vLogName.c_str( ), std::ios_base::out, std::ios_base::binary )
#else
: mLogFile( vLogName.c_str( ), std::ios_base::out | std::ios_base::binary )
#endif
{
	// ...
}

//--------------------------------
Log::~Log( )
{
	// ...
}

//--------------------------------
void Log::write( const String& vMessage, LogLevel vLevel )
{
	String start;
	switch ( vLevel )
	{
	case LOGLEVEL_WARNING:
		start = "(WARNING) ";
		break;

	case LOGLEVEL_ERROR:
		start = "(ERROR) ";
		break;
	}

	// Lock mutex!

	MutexScopeLock l( mMutex );

	// Write to console

	std::cout << start << vMessage << std::endl;

	// Write to log file

	mLogFile << start << vMessage << std::endl;
	mLogFile.flush( );

	// Broadcast message to listeners
	
	ListenerList::const_iterator it;
	for ( it = mListeners.begin( ); it != mListeners.end( ); it++ )
		(*it)->onLogMessage( vMessage, vLevel );
}

//--------------------------------
void Log::removeListener( LogListener* vListener )
{
	MutexScopeLock l( mMutex );

	ListenerList::iterator it = std::find( mListeners.begin( ), mListeners.end( ), vListener );
	if ( it != mListeners.end( ) )
		mListeners.erase( it );
}

//--------------------------------
void Log::addListener( LogListener* vListener )
{
	MutexScopeLock l( mMutex );
	mListeners.push_back( vListener );
}

}
