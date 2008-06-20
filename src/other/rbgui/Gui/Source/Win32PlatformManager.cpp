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

#ifdef WIN32

#include <windows.h>

#include "Mocha/Math.h"

#include "RBGui/Win32PlatformManager.h"
#include "RBGui/Exception.h"

namespace RBGui
{

//--------------------------------
// Sorts directory entries by type
class Win32DirectoryEntrySorter
{
public:
	bool operator ( ) ( const DirectoryEntry& v1, const DirectoryEntry& v2 )
	{
		return ( v1.type < v2.type );
	}
};

//--------------------------------
// Sorts directory entries by type
class Win32DirectoryNameSorter
{
public:
	bool operator ( ) ( const DirectoryEntry& v1, const DirectoryEntry& v2 )
	{
		return ( v1.name < v2.name );
	}
};

//--------------------------------
Win32PlatformManager::Win32PlatformManager( )
{
	// ...
}

//--------------------------------
Win32PlatformManager::~Win32PlatformManager( )
{
	// ...
}

//--------------------------------
bool Win32PlatformManager::getDirectoryListing( const Mocha::String& vPath, DirectoryEntryList& vOut, bool vSort, bool vFilterParent )
{
	WIN32_FIND_DATA data;
	HANDLE handle;

	BOOL res = false;

	Mocha::String path = vPath;
	if ( path == "" )
		path = ".";

	// Find all files in the path

	handle = FindFirstFile( (path+"/*.*").c_str( ), &data );
	if ( handle != INVALID_HANDLE_VALUE )
		res = true;
	else
		return false;

	// Iterate over entries

	while ( res )
	{
		DirectoryEntryType t;

		if ( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			t = DIRENTRY_DIRECTORY;
		else
			t = DIRENTRY_FILE;

		Mocha::String fname = data.cFileName;

		if ( (vFilterParent == false) || ( (fname != ".") && (fname != "..") ) )
			vOut.push_back( DirectoryEntry( data.cFileName, t ) );

		res = FindNextFile( handle, &data );
	}

	FindClose( handle );

	// Sort directory entries if necessary

	if ( vSort )
	{
		// Sort entries alphabetically

		std::sort( vOut.begin( ), vOut.end( ), Win32DirectoryNameSorter( ) );

		// Sort entries by type

		std::sort( vOut.begin( ), vOut.end( ), Win32DirectoryEntrySorter( ) );
	}

	return true;
}

//--------------------------------
Mocha::String Win32PlatformManager::getCurrentWorkingDirectory( )
{
	char buffer[512];
	GetCurrentDirectory( sizeof( buffer ), buffer );
	
	return buffer;
}

//--------------------------------
void Win32PlatformManager::setClipboardText( const Mocha::String& vText )
{
	// Open the clipboard

	if ( OpenClipboard( GetActiveWindow( ) ) == FALSE )
		return;

	// Empty clipboard data

	EmptyClipboard( );

	// Create global data object

	size_t size = sizeof( char ) * (vText.size( )+1);

	HGLOBAL globalObject = GlobalAlloc( GMEM_MOVEABLE, size );
	if ( globalObject == 0 )
	{
		CloseClipboard( );
		return;
	}

	// Copy memory into object

	char* data = reinterpret_cast<char*>( GlobalLock( globalObject ) );
	
	memcpy( data, vText.c_str( ), size - sizeof( char ) );
	data[size-1] = 0;

	GlobalUnlock( globalObject );

	// Set clipboard data

	SetClipboardData( CF_TEXT, globalObject );

	// Close clipboard

	CloseClipboard( );
}

//--------------------------------
void Win32PlatformManager::getClipboardText( Mocha::String& vText )
{
	// Open the clipboard

	if ( OpenClipboard( GetActiveWindow( ) ) == FALSE )
		return;

	// Get the data from the clipboard

	HGLOBAL globalObject = GetClipboardData( CF_TEXT );
	if ( globalObject == 0 )
		return;

	// Extract data

	void* data = GlobalLock( globalObject );
	vText = reinterpret_cast<char*>( data );
	GlobalUnlock( globalObject );

	// Close clipboard

	CloseClipboard( );
}

//--------------------------------
float Win32PlatformManager::getDoubleClickTime( )
{
	UINT millsecs = GetDoubleClickTime( );
	return (millsecs / 1000.0f);
}

//--------------------------------
float Win32PlatformManager::getKeyRepeatDelay( )
{
	UINT out;
	if ( SystemParametersInfo( SPI_GETKEYBOARDDELAY, 0, &out, 0 ) == 0 )
		return 1.0f;

	return ( ((out+1) * 250) / 1000.0f );
}

//--------------------------------
float Win32PlatformManager::getKeyRepeatSpeed( )
{
	UINT out;
	SystemParametersInfo( SPI_GETKEYBOARDSPEED, 0, &out, 0 );

	float result;
	Mocha::lerp<float>( result, 2.5, 30, (float)(out / 31.0f) );

	return ( result / 1000.0f );
}

}

#endif
