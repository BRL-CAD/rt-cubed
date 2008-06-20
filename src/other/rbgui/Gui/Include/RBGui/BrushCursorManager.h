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

#ifndef GUI_BRUSHCURSORMANAGER_H
#define GUI_BRUSHCURSORMANAGER_H

#include "Mocha/Vector2.h"
#include "Mocha/RefPointer.h"

#include "RBGui/CursorManager.h"
#include "RBGui/Texture.h"

namespace RBGui
{

class GUI_EXPORT BrushCursorManager : public CursorManager
{
private:
	Mocha::Vector2 mMousePos;

	CursorType mCursorType;

	class CursorEntry
	{
	public:
		inline CursorEntry( )
			: blendMode( BRUSHBLEND_ALPHA )
		{
			// ...
		}

		inline CursorEntry( Texture* vTexture, const Mocha::Vector2& vHotSpot, BrushBlendMode vBlendMode )
			: texture( vTexture ), hotspot( vHotSpot ), blendMode( vBlendMode )
		{
			// ...
		}

		Mocha::RefPointer<Texture> texture;

		BrushBlendMode blendMode;

		Mocha::Vector2 hotspot;
	};

	CursorEntry mCursors[CURSOR_TYPE_COUNT];

public:
	BrushCursorManager( );

	virtual ~BrushCursorManager( );

	virtual void onMouseMoved( const Mocha::Vector2& vPoint );

	virtual void onMousePressed( MouseButtonID vButton );

	virtual void onMouseReleased( MouseButtonID vButton );

	virtual void setCursor( CursorType vType );

	virtual void draw( Brush& vBrush );

	void setCursorType( CursorType vType, Texture* vTexture, const Mocha::Vector2& vHotSpot = Mocha::Vector2( ), BrushBlendMode vBlendMode = BRUSHBLEND_ALPHA );

	void setCursorType( CursorType vType, const Mocha::String& vTexName, const Mocha::Vector2& vHotSpot = Mocha::Vector2( ), BrushBlendMode vBlendMode = BRUSHBLEND_ALPHA );
};

}

#endif
