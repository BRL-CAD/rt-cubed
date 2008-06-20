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

#include "RBGui/Win32CursorManager.h"

namespace RBGui
{

//--------------------------------
Win32CursorManager::Win32CursorManager( )
{
	// ...
}

//--------------------------------
Win32CursorManager::~Win32CursorManager( )
{
	// ...
}

//--------------------------------
void Win32CursorManager::onMouseMoved( const Mocha::Vector2& vPosition )
{
	// ...
}

//--------------------------------
void Win32CursorManager::onMousePressed( MouseButtonID vButton )
{
	// ...
}

//--------------------------------
void Win32CursorManager::onMouseReleased( MouseButtonID vButton )
{
	// ...
}

//--------------------------------
void Win32CursorManager::setCursor( CursorType vType )
{
	LPCSTR cursor;
	switch ( vType )
	{
	case CURSOR_DEFAULT:
		cursor = IDC_ARROW;
		break;

	case CURSOR_HAND:
		cursor = IDC_HAND;
		break;

	case CURSOR_RESIZE:
		cursor = IDC_SIZENWSE;
		break;

	case CURSOR_TEXT:
		cursor = IDC_IBEAM;
		break;

	case CURSOR_CROSS:
		cursor = IDC_CROSS;
		break;

	case CURSOR_WAIT:
		cursor = IDC_WAIT;
		break;
	}

	SetClassLongPtr( GetActiveWindow( ), GCLP_HCURSOR, 0 );
	SetCursor( LoadCursor( 0, cursor ) );
}

//--------------------------------
void Win32CursorManager::draw( Brush& vBrush )
{
	// ...
}

}

#endif
