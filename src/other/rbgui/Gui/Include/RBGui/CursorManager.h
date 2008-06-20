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

#ifndef GUI_CURSORMANAGER_H
#define GUI_CURSORMANAGER_H

#include "Mocha/Object.h"

#include "RBGui/GuiDefines.h"
#include "RBGui/InputDefines.h"

namespace RBGui
{

class Brush;

/// Manages the rendering of a GUI mouse cursor
class GUI_EXPORT CursorManager : public Mocha::Object
{
public:
	/// Called when the mouse cursor has moved
	/*! \param vPosition The new position of the cursor */
	virtual void onMouseMoved( const Mocha::Vector2& vPosition ) = 0;

	/// Called when a mouse button has been pressed
	/*! \param vButton The button ID that was pressed. See MouseButtonID */
	virtual void onMousePressed( MouseButtonID vButton ) = 0;

	/// Called when a mouse button has been released
	/*! \param vButton The button ID that was pressed. See MouseButtonID */
	virtual void onMouseReleased( MouseButtonID vButton ) = 0;

	/// Sets the mouse cursor to use. See CursorType
	virtual void setCursor( CursorType vType ) = 0;

	/// Draws the mouse cursor
	virtual void draw( Brush& vBrush ) = 0;
};

}

#endif
