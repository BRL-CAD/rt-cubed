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

#ifndef MOCHA_EVENT_H
#define MOCHA_EVENT_H

#ifdef WIN32
#define _WINSOCKAPI_
#include <windows.h>
#elif defined( POSIX )
#include <semaphore.h>
#endif

#include "Mocha/Platform.h"

namespace Mocha
{

/// Event-based thread synchronization primitive
class MOCHA_EXPORT Event
{
private:

#ifdef WIN32
	HANDLE mHandle;
#elif defined( POSIX )
	sem_t *mHandle;
#endif

public:
	/// Constructor
    Event( );

	/// Destructor
	~Event( );

	/// Signals the event
	void raise( );

	/// Waits for the event to be signaled
	/*! \param vTime The amount of time to wait. Use -1 to wait forever.
		\return True if the event was signaled while waiting, false if a timeout occurred */
	bool wait( int vTime = -1 ) const;
};

}

#endif
