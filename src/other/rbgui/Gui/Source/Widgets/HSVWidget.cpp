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

#include "RBGui/Widgets/HSVWidget.h"

namespace RBGui
{

//--------------------------------------------
HSVWidget::HSVWidget( GuiManager* vManager )
: Widget( vManager ), mDragging( false ), mHue( 0.0f )
{
	// ...
}

//--------------------------------------------
HSVWidget::~HSVWidget( )
{
	// ...
}

//--------------------------------------------
void HSVWidget::setHue( float vHue )
{
	mHue = vHue;
	flagDirty( );
}

//--------------------------------------------
float HSVWidget::getHue( ) const
{
	return mHue;
}

//--------------------------------------------
Mocha::Color HSVWidget::getColor( ) const
{
	Mocha::Color result;

	float sat = mPoint.y / getClientRectangle( ).getHeight( );
	float lum = mPoint.x / getClientRectangle( ).getWidth( );
	
	result.setHSVA( mHue, 1.0f-sat, lum, 1 );
	return result;
}

//--------------------------------------------
void HSVWidget::onColorPicked( const Mocha::Color& vColor )
{
	Mocha::ValueList v;
	v.push_back( vColor );

	doCallback( v );
}

//--------------------------------------------
void HSVWidget::setPoint( const Mocha::Vector2& vPoint )
{
	mPoint = vPoint * getRectangle( ).getSize( );
	flagDirty( );
}

//--------------------------------------------
void HSVWidget::onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	mPoint.x = Mocha::clamp( vPoint.x, 0, getClientRectangle( ).getWidth( ) );
	mPoint.y = Mocha::clamp( vPoint.y, 0, getClientRectangle( ).getHeight( ) );

	Mocha::Color c = getColor( );
	onColorPicked( c );

	mDragging = true;
	flagDirty( );
}

//--------------------------------------------
void HSVWidget::onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	mDragging = false;
	flagDirty( );
}

//--------------------------------------------
void HSVWidget::onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	if ( mDragging )
	{
		mPoint.x = Mocha::clamp( vPoint.x, 0, getClientRectangle( ).getWidth( ) );
		mPoint.y = Mocha::clamp( vPoint.y, 0, getClientRectangle( ).getHeight( ) );

		Mocha::Color c = getColor( );
		onColorPicked( c );

		flagDirty( );
	}
}

//--------------------------------------------
void HSVWidget::onDraw( Brush& vBrush ) const
{
	vBrush.setTexture( 0 );

	// Draw a colored rectangle

	Mocha::Color c;
	c.setHSVA( mHue, 1.0f, 1.0f );

	vBrush.setBlendMode( BRUSHBLEND_ALPHA );
	vBrush.drawColorRectangle( getClientRectangle( ),
							   c,
							   c,
							   Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ),
							   Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ) );

	vBrush.setBlendMode( BRUSHBLEND_MODULATE );
	vBrush.drawColorRectangle( getClientRectangle( ),
							   Mocha::Color( 0.0f, 0.0f, 0.0f, 1.0f ),
							   Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ),
							   Mocha::Color( 0.0f, 0.0f, 0.0f, 1.0f ),
							   Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ) );

	// Draw the cross hair

	if ( mDragging == false )
	{
		Mocha::Vector2 point = mPoint + getClientRectangle( ).getPosition( );

		vBrush.setColor( Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ) );
		vBrush.setBlendMode( BRUSHBLEND_INVERT );

		Mocha::Rectangle r;

		r.setPosition( point - Mocha::Vector2( 2.0f, 0.0f ) );
		r.setSize( 5, 1 );

		vBrush.drawRectangle( r );

		r.setPosition( point - Mocha::Vector2( 0.0f, 2.0f ) );
		r.setSize( 1, 5 );

		vBrush.drawRectangle( r );
	}
}

//--------------------------------------------
CursorType HSVWidget::getCursor( ) const
{
	return CURSOR_CROSS;
}

//--------------------------------------------
Mocha::String HSVWidget::getClassName( ) const
{
	return "HSVWidget";
}

//--------------------------------------------
Widget* HSVWidget::factory( GuiManager* vManager )
{
	return new HSVWidget( vManager );
}

}
