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

#ifndef GUI_GUIDEFINES_H
#define GUI_GUIDEFINES_H

#include "Mocha/Platform.h"

#include "RBGui/Platform.h"

namespace RBGui
{

//--------------------------------
enum TextAlignmentMode
{
	TEXTALIGN_LEFT = 0,
	TEXTALIGN_RIGHT,
	TEXTALIGN_CENTER,
	TEXTALIGN_TOP,
	TEXTALIGN_BOTTOM
};

//--------------------------------
enum CursorType
{
	CURSOR_DEFAULT = 0,
	CURSOR_RESIZE,
	CURSOR_CROSS,
	CURSOR_HAND,
	CURSOR_TEXT,
	CURSOR_WAIT,

	CURSOR_TYPE_COUNT
};

//--------------------------------
inline Mocha::String TextAlignmentModeToString( TextAlignmentMode vMode )
{
	switch ( vMode )
	{
	case TEXTALIGN_LEFT:
		return "left";

	case TEXTALIGN_RIGHT:
		return "right";

	case TEXTALIGN_CENTER:
		return "center";

	case TEXTALIGN_TOP:
		return "top";

	case TEXTALIGN_BOTTOM:
		return "bottom";
	}

	return "";
}

//--------------------------------
inline TextAlignmentMode StringToTextAlignmentMode( const Mocha::String& vMode )
{
	if ( vMode == "left" )
		return TEXTALIGN_LEFT;
	else if ( vMode == "right" )
		return TEXTALIGN_RIGHT;
	else if ( vMode == "center" )
		return TEXTALIGN_CENTER;
	else if ( vMode == "top" )
		return TEXTALIGN_TOP;
	else if ( vMode == "bottom" )
		return TEXTALIGN_BOTTOM;

	return TEXTALIGN_CENTER;
}

//--------------------------------
enum BrushBlendMode
{
	BRUSHBLEND_NONE = 0,
	BRUSHBLEND_MODULATE,
	BRUSHBLEND_DISCARDALPHA,
	BRUSHBLEND_INVERT,
	BRUSHBLEND_ALPHA
};

//--------------------------------
enum BrushFilterMode
{
	BRUSHFILTER_NEAREST = 0,
	BRUSHFILTER_LINEAR
};

//--------------------------------
enum GradientType
{
	GRADIENT_HORIZONTAL = 0,
	GRADIENT_VERTICAL
};

}

#endif
