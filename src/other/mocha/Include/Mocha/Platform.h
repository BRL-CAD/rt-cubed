/*
-----------------------------------------------------------------------------
This source file is part of Mocha
For the latest info, see http://www.rightbraingames.com/

Copyright (c) 2000-2006 Right Brain Games Inc.

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


#ifndef MOCHA_PLATFORM_H
#define MOCHA_PLATFORM_H

#include <vector>
#include <string>

#ifdef POSIX
#ifdef __FreeBSD__
#include <uuid.h>
#else
#include <uuid/uuid.h>
#endif
#endif

namespace Mocha
{

typedef std::string String;
typedef std::vector<String> StringList;

typedef char int8;
typedef short int16;
typedef int int32;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef float real32;
typedef double real64;

#ifdef MOCHA_STATIC
	#define MOCHA_EXPORT
#else
	#ifdef MOCHA
		#ifdef WIN32
			#define MOCHA_EXPORT __declspec(dllexport)
		#else
			#define MOCHA_EXPORT
		#endif
	#else
		#ifdef WIN32
			#define MOCHA_EXPORT __declspec(dllimport)
		#else
			#define MOCHA_EXPORT
		#endif
	#endif
#endif

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#pragma warning (disable : 4251)

// disable: forcing value to bool 'true' or 'false'
// We don't freaking care.
#pragma warning (disable : 4800)

//--------------------------------
MOCHA_EXPORT extern Mocha::uint16 HostToNetwork16( Mocha::uint16 vValue );

//--------------------------------
MOCHA_EXPORT extern Mocha::uint32 HostToNetwork32( Mocha::uint32 vValue );

//--------------------------------
MOCHA_EXPORT extern Mocha::uint16 NetworkToHost16( Mocha::uint16 vValue );

//--------------------------------
MOCHA_EXPORT extern Mocha::uint32 NetworkToHost32( Mocha::uint32 vValue );

}

#endif
