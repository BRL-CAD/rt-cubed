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

#include "RBGui/BrushCursorManager.h"
#include "RBGui/Brush.h"
#include "RBGui/Core.h"

namespace RBGui
{

//--------------------------------
BrushCursorManager::BrushCursorManager( )
: mCursorType( CURSOR_DEFAULT )
{
	// ...
}

//--------------------------------
BrushCursorManager::~BrushCursorManager( )
{
	// ...
}

//--------------------------------
void BrushCursorManager::onMouseMoved( const Mocha::Vector2& vPosition )
{
	mMousePos = vPosition;
}

//--------------------------------
void BrushCursorManager::onMousePressed( MouseButtonID vButton )
{
	// ...
}

//--------------------------------
void BrushCursorManager::onMouseReleased( MouseButtonID vButton )
{
	// ...
}

//--------------------------------
void BrushCursorManager::setCursor( CursorType vType )
{
	mCursorType = vType;
}

//--------------------------------
void BrushCursorManager::draw( Brush& vBrush )
{
	const CursorEntry& cursor = mCursors[mCursorType];
	if ( cursor.texture )
	{
		// Setup rectangle

		Mocha::Rectangle rect;
		rect.setSize( cursor.texture->getSize( ) );
		rect.setPosition( mMousePos - cursor.hotspot );

		// Draw the cursor

		vBrush.setBlendMode( cursor.blendMode );
		vBrush.setTexture( cursor.texture );
		vBrush.drawRectangle( rect );
	}
}

//--------------------------------
void BrushCursorManager::setCursorType( CursorType vType, Texture* vTexture, const Mocha::Vector2& vHotSpot, BrushBlendMode vBlendMode )
{
	mCursors[vType] = CursorEntry( vTexture, vHotSpot, vBlendMode );
}

//--------------------------------
void BrushCursorManager::setCursorType( CursorType vType, const Mocha::String& vTexName, const Mocha::Vector2& vHotSpot, BrushBlendMode vBlendMode )
{
	Mocha::RefPointer<Texture> tex = Core::Get( ).getTextureManager( ).getTexture( vTexName );
	setCursorType( vType, tex, vHotSpot, vBlendMode );
}

}
