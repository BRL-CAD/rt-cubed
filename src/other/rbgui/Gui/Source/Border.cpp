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

#include "Mocha/DataSection.h"

#include "RBGui/Exception.h"
#include "RBGui/Border.h"
#include "RBGui/Core.h"

namespace RBGui
{


//--------------------------------
Border::Border( )
: mGradientType( GRADIENT_VERTICAL ), mRenderCenter( false ), mTileCenter( false ), mTileEdges( false )
{
	// ...
}

//--------------------------------
Border::~Border( )
{
	// ...
}

//--------------------------------
bool Border::hasState( const Mocha::String& vName ) const
{
	StateMap::const_iterator it = mStates.find( vName );
	if ( it == mStates.end( ) )
		return false;

	return true;
}

//--------------------------------
void Border::setGradientType( GradientType vType )
{
	mGradientType = vType;
}

//--------------------------------
GradientType Border::getGradientType( ) const
{
	return mGradientType;
}

//--------------------------------
void Border::setPart( BorderPart vID, const Mocha::Rectangle& vRect )
{
	mParts[vID] = vRect;
	if( vID == BORDER_CENTER )
		mRenderCenter = true;
}

//--------------------------------
const Mocha::Rectangle& Border::getPart( BorderPart vID ) const
{
	return mParts[vID];
}

//--------------------------------
void Border::setClientAdjust( const Mocha::Rectangle& vAdjust )
{
	mClientAdjust = vAdjust;
}

//--------------------------------
const Mocha::Rectangle& Border::getClientAdjust( ) const
{
	return mClientAdjust;
}

//--------------------------------
void Border::draw( Brush& vGuiBrush, const Mocha::Rectangle& vRect, bool vBackground, bool vCloseButton, bool vClosePressed, const Mocha::String& vState )
{
	// Get the border state to use

	GuiBorderState& state = getState( vState );

	// Render the texture if one is provided

	if ( state.texture )
	{
		// Bind state texture

		vGuiBrush.setTexture( state.texture );

		// Use nearest filtering

		vGuiBrush.setFilterMode( BRUSHFILTER_NEAREST );

		// Modulate with white

		vGuiBrush.setColor( Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ) );
		vGuiBrush.beginGlyphs( );

		// Render top left corner

		Mocha::Rectangle rect;
		Mocha::Rectangle uv;

		uv = mParts[BORDER_TOPLEFT];
		rect = uv;

		rect.translate( vRect.getPosition( ) );
		vGuiBrush.addGlyph( rect, uv, false );

		// Render top right corner

		uv = mParts[BORDER_TOPRIGHT];
		rect = uv;

		rect.setPosition( vRect.getWidth( ) - uv.getWidth( ) + vRect.left, vRect.top );
		vGuiBrush.addGlyph( rect, uv, false );

		// Render bottom left corner

		uv = mParts[BORDER_BOTTOMLEFT];
		rect = uv;

		rect.setPosition( vRect.left, vRect.getHeight( ) - uv.getHeight( ) + vRect.top );
		vGuiBrush.addGlyph( rect, uv, false );

		// Render bottom right corner

		uv = mParts[BORDER_BOTTOMRIGHT];
		rect = uv;

		rect.setPosition( vRect.left + vRect.getWidth( ) - uv.getWidth( ), vRect.getHeight( ) - uv.getHeight( ) + vRect.top );
		vGuiBrush.addGlyph( rect, uv, false );

		// We're done drawing glyphs if we're tiling edges

		if ( mTileEdges )
			vGuiBrush.endGlyphs( );

		// Render top edge

		uv = mParts[BORDER_TOP];
		rect = uv;

		rect.setPosition( vRect.left + mParts[BORDER_TOPLEFT].getWidth( ), vRect.top );
		rect.setWidth( vRect.getWidth( ) - (mParts[BORDER_TOPLEFT].getWidth( ) + mParts[BORDER_TOPRIGHT].getWidth( )) );

		if ( mTileEdges )
			vGuiBrush.drawTiledRectangle( rect, uv );
		else
			vGuiBrush.addGlyph( rect, uv, false );

		// Render bottom edge

		uv = mParts[BORDER_BOTTOM];
		rect = uv;

		rect.setPosition( vRect.left + mParts[BORDER_BOTTOMLEFT].getWidth( ), vRect.getHeight( ) - uv.getHeight( ) + vRect.top );
		rect.setWidth( vRect.getWidth( ) - (mParts[BORDER_BOTTOMLEFT].getWidth( ) + mParts[BORDER_BOTTOMRIGHT].getWidth( )) );

		if ( mTileEdges )
			vGuiBrush.drawTiledRectangle( rect, uv );
		else
			vGuiBrush.addGlyph( rect, uv, false );

		// Render left edge

		uv = mParts[BORDER_LEFT];
		rect = uv;

		rect.setPosition( vRect.left, mParts[BORDER_TOPLEFT].getHeight( ) + vRect.top );
		rect.setHeight( vRect.getHeight( ) - (mParts[BORDER_TOPLEFT].getHeight( ) + mParts[BORDER_BOTTOMLEFT].getHeight( )) );

		if ( mTileEdges )
			vGuiBrush.drawTiledRectangle( rect, uv );
		else
			vGuiBrush.addGlyph( rect, uv, false );

		// Render right edge

		uv = mParts[BORDER_RIGHT];
		rect = uv;

		rect.setPosition( vRect.left + vRect.getWidth( ) - uv.getWidth( ), mParts[BORDER_TOPRIGHT].getHeight( ) + vRect.top );
		rect.setHeight( vRect.getHeight( ) - (mParts[BORDER_TOPRIGHT].getHeight( ) + mParts[BORDER_BOTTOMRIGHT].getHeight( )) );

		if ( mTileEdges )
			vGuiBrush.drawTiledRectangle( rect, uv );
		else
			vGuiBrush.addGlyph( rect, uv, false );

		// Render the center if necessary

		if( mRenderCenter )
		{
			uv = mParts[BORDER_CENTER];

			if ( mTileCenter == false )
			{
				rect = vRect + mClientAdjust;

				vGuiBrush.setFilterMode( BRUSHFILTER_LINEAR );
				vGuiBrush.addGlyph( rect, uv, false );
			}
			else
			{
				// Render everything batched so far

				vGuiBrush.endGlyphs( );

				// Draw tiled background

				vGuiBrush.drawTiledRectangle( vRect + mClientAdjust, uv );
			}
		}

		// Render everything batched (Will do nothing if we already ended glyphs earlier)

		vGuiBrush.endGlyphs( );
	}

	// Draw button

	if ( vCloseButton && state.closeButton )
	{
		Mocha::Rectangle rect;
		rect.setSize( state.closeButton->getSize( ) * Mocha::Vector2( 0.5f, 1.0f ) );
		rect.setPosition( vRect.getWidth( ) + mCloseButtonPos.x, vRect.top + mCloseButtonPos.y );

		Mocha::Rectangle uv;
		uv.setPosition( ( vClosePressed ? 1.0f : 0.0f ) * 0.5f, 0.0f );
		uv.setSize( 0.5f, 1.0f );

		vGuiBrush.setTexture( state.closeButton );
		vGuiBrush.setColor( Mocha::Color::White );
		vGuiBrush.drawRectangle( rect, uv );
	}

	// Clear client region

	if ( vBackground && (mRenderCenter == false) )
	{
		vGuiBrush.setTexture( 0 );
		vGuiBrush.drawGradient( vRect + mClientAdjust, mGradientType, state.bgColor1, state.bgColor2 );
	}
}

//--------------------------------
bool Border::pointInButton( const Mocha::Vector2& vPoint, const Mocha::Rectangle& vBorderRect, const Mocha::String& vState ) const
{
	const GuiBorderState& state = getState( vState );

	if ( state.closeButton )
	{
		Mocha::Rectangle rect;
		rect.setSize( state.closeButton->getSize( ) * Mocha::Vector2( 0.5f, 1.0f ) );
		rect.setPosition( vBorderRect.right + mCloseButtonPos.x, vBorderRect.top + mCloseButtonPos.y );

		return rect.pointInside( vPoint );
	}

	return false;
}

//--------------------------------
void Border::drawBackground( Brush& vGuiBrush, const Mocha::Rectangle& vRect, const Mocha::String& vState )
{
	GuiBorderState& state = getState( vState );
	vGuiBrush.drawGradient( vRect + mClientAdjust, mGradientType, state.bgColor1, state.bgColor2 );
}

//--------------------------------
void Border::setBackgroundColor1( const Mocha::Color& vColor, const Mocha::String& vState )
{
	getState( vState ).bgColor1 = vColor;
}

//--------------------------------
const Mocha::Color& Border::getBackgroundColor1( const Mocha::String& vState ) const
{
	return getState( vState ).bgColor1;
}

//--------------------------------
void Border::setBackgroundColor2( const Mocha::Color& vColor, const Mocha::String& vState )
{
	getState( vState ).bgColor2 = vColor;
}

//--------------------------------
const Mocha::Color& Border::getBackgroundColor2( const Mocha::String& vState ) const
{
	return getState( vState ).bgColor2;
}

//--------------------------------
void Border::setTextOffset( const Mocha::Vector2& vPos )
{
	mTextPos = vPos;
}

//--------------------------------
const Mocha::Vector2& Border::getTextOffset( ) const
{
	return mTextPos;
}

//--------------------------------
void Border::setMinSize( const Mocha::Vector2& vSize )
{
	mMinSize = vSize;
}

//--------------------------------
const Mocha::Vector2& Border::getMinSize( ) const
{
	return mMinSize;
}

//--------------------------------
void Border::setCloseButtonOffset( const Mocha::Vector2& vPosition )
{
	mCloseButtonPos = vPosition;
}

//--------------------------------
const Mocha::Vector2& Border::getCloseButtonOffset( )
{
	return mCloseButtonPos;
}

//--------------------------------
Border::GuiBorderState& Border::getState( const Mocha::String& vName )
{
	return mStates[vName];
}

//--------------------------------
const Border::GuiBorderState& Border::getState( const Mocha::String& vName ) const
{
	return mStates[vName];
}

//--------------------------------
void Border::setTexture( Texture* vTexture, const Mocha::String& vState )
{
	// Set the texture on the given state

	getState( vState ).texture = vTexture;
}

//--------------------------------
void Border::setCloseButton( Texture* vTexture, const Mocha::String& vState )
{
	// Set the texture on the given state

	getState( vState ).closeButton = vTexture;
}

//--------------------------------
void Border::open( const Mocha::DataSection& vSection )
{
	size_t x;
	for ( x = 0; x < vSection.getComponentCount( ); x++ )
	{
		const Mocha::DataComponent& component = vSection.getComponent( x );
		const Mocha::String& name = component.getName( );

		size_t paramCount = component.getParamCount( );

		if ( name == "part" )
		{
			if ( paramCount != 2 )
				throw Exception( "Invalid token count in 'part' tag" );

			const Mocha::String& part = component.getParam( 0 );

			BorderPart id;
			if ( part == "top" )
				id = BORDER_TOP;
			else if ( part == "bottom" )
				id = BORDER_BOTTOM;
			else if ( part == "left" )
				id = BORDER_LEFT;
			else if ( part == "right" )
				id = BORDER_RIGHT;
			else if ( part == "topleft" )
				id = BORDER_TOPLEFT;
			else if ( part == "topright" )
				id = BORDER_TOPRIGHT;
			else if ( part == "bottomleft" )
				id = BORDER_BOTTOMLEFT;
			else if ( part == "bottomright" )
				id = BORDER_BOTTOMRIGHT;
			else if ( part == "center" )
				id = BORDER_CENTER;
			else
				throw Exception( "Invalid border part name '" + part + "'" );

			setPart( id, component.getParamRectangle( 1 ) );
		}
		else if ( name == "gradient_type" )
		{
			if ( paramCount != 1 )
				throw Exception( "Invalid token count in 'gradient_type' tag" );

			const Mocha::String& type = component.getParam( 0 );

			if ( type == "vertical" )
				setGradientType( GRADIENT_VERTICAL );
			else if ( type == "horizontal" )
				setGradientType( GRADIENT_HORIZONTAL );
			else
				throw Exception( "Invalid gradient type '" + type + "'" );
		}
		else if ( name == "tile_center" )
		{
			mTileCenter = true;
		}
		else if ( name == "tile_edges" )
		{
			mTileEdges = true;
		}
		else if ( name == "adjust" )
		{
			if ( paramCount != 1 )
				throw Exception( "Invalid token count in 'adjust' tag" );

			setClientAdjust( component.getParamRectangleLTRB( 0 ) );
		}
		else if ( name == "bgcolor1" )
		{
			if ( paramCount == 2 )
			{
				setBackgroundColor1( component.getParamColor( 1 ), component.getParam( 0 ) );
			}
			else if ( paramCount == 1 )
			{
				setBackgroundColor1( component.getParamColor( 0 ) );
			}
			else
				throw Exception( "Invalid token count in 'bgcolor1' tag" );
		}
		else if ( name == "bgcolor2" )
		{
			if ( paramCount == 2 )
			{
				setBackgroundColor2( component.getParamColor( 1 ), component.getParam( 0 ) );
			}
			else if ( paramCount == 1 )
			{
				setBackgroundColor2( component.getParamColor( 0 ) );
			}
			else
				throw Exception( "Invalid token count in 'bgcolor1' tag" );
		}
		else if ( name == "minsize" )
		{
			if ( paramCount != 1 )
				throw Exception( "Invalid token count in 'minsize' tag" );

			setMinSize( component.getParamVector2( 0 ) );
		}
		else if ( name == "textoffset" )
		{
			if ( paramCount != 1 )
				throw Exception( "Invalid token count in 'textpos' tag" );

			setTextOffset( component.getParamVector2( 0 ) );
		}
		else if ( name == "closebuttonoffset" )
		{
			if ( paramCount != 1 )
				throw Exception( "Invalid token count in 'closebuttonpos' tag" );

			setCloseButtonOffset( component.getParamVector2( 0 ) );
		}
		else if ( name == "closebutton" )
		{
			if ( paramCount == 1 )
				setCloseButton( Core::Get( ).getTextureManager( ).getTexture( component.getParam( 0 ) ) );
			else if ( paramCount == 2 )
				setCloseButton( Core::Get( ).getTextureManager( ).getTexture( component.getParam( 1 ) ), component.getParam( 0 ) );
			else
				throw Exception( "Invalid token count in 'closebutton' tag" );
		}
		else if ( name == "texture" )
		{
			if ( paramCount == 1 )
				setTexture( Core::Get( ).getTextureManager( ).getTexture( component.getParam( 0 ) ) );
			else if ( paramCount == 2 )
				setTexture( Core::Get( ).getTextureManager( ).getTexture( component.getParam( 1 ) ), component.getParam( 0 ) );
			else
				throw Exception( "Invalid token count in 'texture' tag" );
		}
	}
}

}
