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

#include "Mocha/Timer.h"

#ifdef __FreeBSD__
#include <sys/time.h>
#endif

namespace Mocha
{

//--------------------------------
Timer::Timer( )
{
	reset( );
}

//--------------------------------
Timer::~Timer( )
{
	// ...
}

#ifdef WIN32

//--------------------------------------------
double Timer::getDeltaSeconds( )
{
	LARGE_INTEGER newTime;
	QueryPerformanceCounter( &newTime );

	LARGE_INTEGER tmp = newTime;
	tmp.QuadPart -= mOldTime.QuadPart;
	tmp.QuadPart *= 1000;

	mOldTime = newTime;

	return ((double)tmp.QuadPart / (double)mFrequency.QuadPart) / 1000.0f;
}

//--------------------------------------------
size_t Timer::getDelta( )
{
	LARGE_INTEGER newTime;
	QueryPerformanceCounter( &newTime );

	LARGE_INTEGER tmp = newTime;
	tmp.QuadPart -= mOldTime.QuadPart;
	tmp.QuadPart *= 1000;

	mOldTime = newTime;

	return (size_t)((double)tmp.QuadPart / (double)mFrequency.QuadPart);
}

//--------------------------------------------
void Timer::reset( )
{
	QueryPerformanceFrequency( &mFrequency );
	QueryPerformanceCounter( &mOldTime );
}

#elif defined( POSIX )

//--------------------------------------------
double Timer::getDeltaSeconds( )
{
	timeval newTime;
	gettimeofday(&newTime, NULL);

	timeval tmp = newTime;
	tmp.tv_sec -= mOldTime.tv_sec;
	tmp.tv_usec -= mOldTime.tv_usec;

	mOldTime = newTime;

	double ret = tmp.tv_sec + (tmp.tv_usec / 1000000.0);
	return ret;
}

//--------------------------------------------
size_t Timer::getDelta( )
{
	return (size_t)(this->getDeltaSeconds() * 1000);
}

//--------------------------------------------
void Timer::reset( )
{
	gettimeofday(&mOldTime, NULL);
}

#else
#error "No timer implementation"
#endif

}
