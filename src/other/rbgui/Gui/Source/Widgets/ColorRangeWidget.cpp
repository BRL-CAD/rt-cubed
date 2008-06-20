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

#include "RBGui/Exception.h"

#include "RBGui/Widgets/ColorRangeWidget.h"

#define HALF_ARROW 8

namespace RBGui
{

//--------------------------------------------
ColorRangeWidget::ColorRangeWidget( GuiManager* vManager )
: Widget( vManager ), mGradientType( GRADIENT_HORIZONTAL ), mValue( 0.0f )
{
	// ...
}

//--------------------------------------------
ColorRangeWidget::~ColorRangeWidget( )
{
	// ...
}

//--------------------------------------------
void ColorRangeWidget::onRectangleChanged( )
{
	const Mocha::Rectangle& r = getClientRectangle( );
	if ( r.getWidth( ) > r.getHeight( ) )
		mGradientType = GRADIENT_HORIZONTAL;
	else
		mGradientType = GRADIENT_VERTICAL;
}

//--------------------------------------------
void ColorRangeWidget::addRange( const Mocha::Color& vColor1, const Mocha::Color& vColor2 )
{
	ColorRange range;
	range.color1 = vColor1;
	range.color2 = vColor2;

	addRange( range );
}

//--------------------------------------------
void ColorRangeWidget::addRange( const ColorRange& vRange )
{
	mRanges.push_back( vRange );
	flagDirty( );
}

//--------------------------------------------
const ColorRange& ColorRangeWidget::getRange( size_t vIndex ) const
{
	if ( vIndex >= getRangeCount( ) )
		throw Exception( "Invalid color range index" );

	return mRanges[vIndex];
}

//--------------------------------------------
size_t ColorRangeWidget::getRangeCount( ) const
{
	return mRanges.size( );
}

//--------------------------------------------
void ColorRangeWidget::setValue( float vValue )
{
	mValue = Mocha::clamp( vValue, 0.0f, 1.0f );
	flagDirty( );
}

//--------------------------------------------
float ColorRangeWidget::getValue( ) const
{
	return mValue;
}

//--------------------------------------------
void ColorRangeWidget::updateValue( const Mocha::Vector2& vPoint )
{
	Mocha::Rectangle r = getClientRectangle( );

	r.setPosition( 0.0f, 0.0f );
	r.shrink( (HALF_ARROW/2)+1 );

	if ( mGradientType == GRADIENT_HORIZONTAL )
		mValue = Mocha::clamp( (vPoint.x-HALF_ARROW/2) / r.getWidth( ), 0.0f, 1.0f );
	else
		mValue = Mocha::clamp( (vPoint.y-HALF_ARROW/2) / r.getHeight( ), 0.0f, 1.0f );

	onChanged( );
	flagDirty( );
}

//--------------------------------------------
void ColorRangeWidget::onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	updateValue( vPoint );
	mDragging = true;
}

//--------------------------------------------
void ColorRangeWidget::onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	mDragging = false;
}

//--------------------------------------------
void ColorRangeWidget::onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	if ( mDragging )
		updateValue( vPoint );
}

//--------------------------------------------
void ColorRangeWidget::onChanged( )
{
	Mocha::ValueList v;
	v.push_back( mValue );

	doCallback( v );
}

//--------------------------------------------
void ColorRangeWidget::clear( )
{
	mRanges.clear( );
}

//--------------------------------------------
void ColorRangeWidget::drawGradients( Brush& vBrush ) const
{
	Mocha::Rectangle client = getClientRectangle( );
	client.shrink( (HALF_ARROW/2)+1 );

	size_t count = getRangeCount( );
	vBrush.setTexture( 0 );

    size_t x;
	for ( x = 0; x < count; x++ )
	{
		Mocha::Rectangle r;

		if ( mGradientType == GRADIENT_HORIZONTAL )
		{
			r.left = (client.getWidth( )/count)	* (x/(float)count) + client.left;
			r.right = (client.getWidth( )/count) * ((x+1)/(float)count) + client.left;
			r.top = client.top;
			r.bottom = client.bottom;
		}
		else
		{
			r.top = client.getHeight( ) * (x/(float)count) + client.top;
			r.bottom = client.getHeight( ) * ((x+1)/(float)count) + client.top;
			r.left = client.left;
			r.right = client.right;
		}

		vBrush.drawGradient( r, mGradientType, mRanges[x].color1, mRanges[x].color2 );
	}
}

//--------------------------------------------
void ColorRangeWidget::onDraw( Brush& vBrush ) const
{
	// Get client rectangle

	const Mocha::Rectangle& client = getClientRectangle( );
	Mocha::Rectangle clip = vBrush.getClipRegion( );

	// Get theme

	Theme* theme = getRenderTheme( );
	if ( theme == 0 )
		return;

	// Get the images to use

	Texture* image = theme->getTexture( "ColorRangeArrow" );
	Texture* checker = theme->getTexture( "Checker" );

	Mocha::Rectangle r;
	Mocha::Rectangle uv;

	// Draw outline

	r = getClientRectangle( );
	r.shrink( HALF_ARROW/2 );

	vBrush.setTexture( 0 );
	vBrush.setColor( Mocha::Color( 0.0f, 0.0f, 0.0f, 1.0f ) );
	vBrush.setBlendMode( BRUSHBLEND_ALPHA );
	vBrush.drawRectangle( r );

	r.shrink( 1 );

	// Draw checker background

	if ( checker )
	{
		vBrush.setClipRegion( r.intersect( clip ) );
		vBrush.setColor( Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ) );
		vBrush.setTexture( checker );
		vBrush.drawTiledRectangle( r );
	}

	// Draw the gradients

	drawGradients( vBrush );

	// Draw the arrow

	if ( image )
	{
		if ( mGradientType == GRADIENT_HORIZONTAL )
		{
			r.setPosition( r.left + (mValue * r.getWidth( )) - HALF_ARROW, client.top );
			r.setSize( HALF_ARROW*2, HALF_ARROW*2 );

			uv.setPosition( 0.0f, 0.0f );
			uv.setSize( 1.0f, 0.5f );
		}
		else
		{
			r.setPosition( client.left, client.top + (mValue * r.getHeight( )) - HALF_ARROW/2 );
			r.setSize( HALF_ARROW*2, HALF_ARROW*2 );

			uv.setPosition( 0.0f, 0.5f );
			uv.setSize( 1.0f, 0.5f );
		}

		vBrush.setClipRegion( client.intersect( clip ) );

		vBrush.setTexture( image );
		vBrush.drawRectangle( r, uv );
	}
}

//--------------------------------------------
Mocha::String ColorRangeWidget::getClassName( ) const
{
	return "ColorRange";
}

//--------------------------------------------
Widget* ColorRangeWidget::factory( GuiManager* vManager )
{
	return new ColorRangeWidget( vManager );
}

}
