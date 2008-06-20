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

#ifndef GUI_PLATFORMMANAGER_H
#define GUI_PLATFORMMANAGER_H

#include <vector>

#include "Mocha/Object.h"
#include "Mocha/Stream.h"

#include "RBGui/Platform.h"
#include "RBGui/GuiDefines.h"

namespace RBGui
{

//--------------------------------
enum DirectoryEntryType
{
	DIRENTRY_DIRECTORY = 0,
	DIRENTRY_FILE
};

//--------------------------------
struct DirectoryEntry
{
public:
	inline DirectoryEntry( const Mocha::String& vName, DirectoryEntryType vType )
		: name( vName ), type( vType )
	{
		// ...
	}

	inline DirectoryEntry( const DirectoryEntry& vOther )
		: type( vOther.type ), name( vOther.name )
	{
		// ...
	}

	DirectoryEntryType type;

	Mocha::String name;
};

//--------------------------------
typedef std::vector<DirectoryEntry> DirectoryEntryList;

//--------------------------------
/// Provides an abstraction for common platform specific functions
class GUI_EXPORT PlatformManager : public Mocha::Object
{
public:
	/// Gets a list of directory entries in a given path
	/*! \param vPath The path of the directory entries to list
		\param vOut The list to be filled with the directory entries. See DirectEntry
		\param vSort Whether or not to sort entries alphabetically and by type
		\param vFilterParent Whether or not to filter out the parent directory entry
		\return True on success, false on failure */
	virtual bool getDirectoryListing( const Mocha::String& vPath, DirectoryEntryList& vOut, bool vSort = false, bool vFilterParent = false ) = 0;

	/// Gets the current working directory
	/*! \param The full path to the current directory */
	virtual Mocha::String getCurrentWorkingDirectory( ) = 0;

	/// Sets the system clipboard text
	/*! \param vText The text to copy to the clipboard */
	virtual void setClipboardText( const Mocha::String& vText ) = 0;

	/// Gets text from the system clipboard
	/*! \param Reference to the string to receive the clipboard text */
	virtual void getClipboardText( Mocha::String& vText ) = 0;

	/// Gets the number of seconds between clicks for a mouse click to be considered a double click
	virtual float getDoubleClickTime( ) = 0;

	/// Gets the key repeat delay, in seconds
	virtual float getKeyRepeatDelay( ) = 0;

	/// Gets the key repeat speed, in seconds
	virtual float getKeyRepeatSpeed( ) = 0;
};

}

#endif
