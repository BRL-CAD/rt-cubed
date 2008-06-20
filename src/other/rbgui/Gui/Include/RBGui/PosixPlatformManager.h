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

#ifndef GUI_POSIXPLATFORMMANAGER_H
#define GUI_POSIXPLATFORMMANAGER_H

#include "RBGui/PlatformManager.h"

namespace RBGui
{

/// Posix/X Windows platform manager
class GUI_EXPORT PosixPlatformManager : public PlatformManager
{
public:
	PosixPlatformManager( );

	virtual ~PosixPlatformManager( );

	virtual bool getDirectoryListing( const Mocha::String& vPath, DirectoryEntryList& vOut, bool vSort, bool vFilterParent );

	virtual Mocha::String getCurrentWorkingDirectory( );

	virtual void setClipboardText( const Mocha::String& vText );

	virtual void getClipboardText( Mocha::String& vText );
};

}

#endif
