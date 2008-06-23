/*
-----------------------------------------------------------------------------
This source file is part of the Right Brain Games GUI
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

#ifdef POSIX

#include "RBGui/PosixPlatformManager.h"

namespace RBGui
{

//--------------------------------
PosixPlatformManager::PosixPlatformManager( )
{
	// ...
}

//--------------------------------
PosixPlatformManager::~PosixPlatformManager( )
{
	// ...
}

//--------------------------------
bool PosixPlatformManager::getDirectoryListing( const Mocha::String& vPath, DirectoryEntryList& vOut, bool vSort, bool vFilterParent )
{
	return false;
}

//--------------------------------
Mocha::String PosixPlatformManager::getCurrentWorkingDirectory( )
{
	// ...
}

//--------------------------------
void PosixPlatformManager::setClipboardText( const Mocha::String& vText )
{
	// ...
}

//--------------------------------
void PosixPlatformManager::getClipboardText( Mocha::String& vText )
{
	vText = "";
}

float PosixPlatformManager::getDoubleClickTime( )
{
	// ...
}

float PosixPlatformManager::getKeyRepeatDelay( )
{
	/// \todo mafm: HACK to get it running quickly
	return 250.0f;
}

float PosixPlatformManager::getKeyRepeatSpeed( )
{
	/// \todo mafm: HACK to get it running quickly
	return 0.5f;
}

}



#endif
