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
#include "Mocha/Stream.h"

#include "RBGui/Theme.h"
#include "RBGui/Exception.h"
#include "RBGui/Core.h"

namespace RBGui
{


//--------------------------------
Theme::Theme( )
{
	// ...
}

//--------------------------------
Theme::~Theme( )
{
	// ...
}

//--------------------------------
void Theme::setBorder( const Mocha::String& vName, Border* vBorder )
{
	mBorders[vName] = vBorder;
}

//--------------------------------
Border* Theme::getBorder( const Mocha::String& vName ) const
{
	BorderMap::const_iterator it = mBorders.find( vName );
	if ( it == mBorders.end( ) )
		return 0;

	return (*it).second;
}

//--------------------------------
void Theme::setColor( const Mocha::String& vName, const Mocha::Color& vColor )
{
	mColors[vName] = vColor;
}

//--------------------------------
Mocha::Color Theme::getColor( const Mocha::String& vName, const Mocha::Color& vDefault ) const
{
	ColorMap::const_iterator it = mColors.find( vName );
	if ( it == mColors.end( ) )
		return vDefault;

	return (*it).second;
}

//--------------------------------
void Theme::setFont( const Mocha::String& vName, Font* vFont )
{
	mFonts[vName] = vFont;
}

//--------------------------------
Font* Theme::getFont( const Mocha::String& vName ) const
{
	FontMap::const_iterator it = mFonts.find( vName );
	if ( it == mFonts.end( ) )
		return mDefaultFont;

	return (*it).second;
}

//--------------------------------
void Theme::setDefaultFont( Font* vFont )
{
	mDefaultFont = vFont;
}

//--------------------------------
Font* Theme::getDefaultFont( ) const
{
	return mDefaultFont;
}

//--------------------------------
void Theme::setTexture( const Mocha::String& vName, Texture* vTexture )
{
	mTextures[vName] = vTexture;
}

//--------------------------------
Texture* Theme::getTexture( const Mocha::String& vName ) const
{
	TextureMap::const_iterator it = mTextures.find( vName );
	if ( it == mTextures.end( ) )
		return 0;

	return (*it).second;
}

//--------------------------------
void Theme::setFloat( const Mocha::String& vName, float vValue )
{
	mFloats[vName] = vValue;
}

//--------------------------------
float Theme::getFloat( const Mocha::String& vName, float vDefault ) const
{
	FloatMap::const_iterator it = mFloats.find( vName );
	if ( it == mFloats.end( ) )
		return vDefault;

	return (*it).second;
}

//--------------------------------
void Theme::open( const Mocha::DataSection& vSection )
{
	size_t x;

	// Scan for borders

	for ( x = 0; x < vSection.getSectionCount( ); x++ )
	{
		const Mocha::DataSection& section = vSection.getSection( x );
		const Mocha::String& type = section.getType( );
	
		if ( type == "border" )
		{
			if ( section.getParamCount( ) != 1 )
				throw Exception( "Invalid token count in 'border' tag" );

			Mocha::RefPointer<Border> b = new Border( );
			b->open( section );

			setBorder( section.getParam( 0 ), b );
		}
	}

	// Scan for other components

	for ( x = 0; x < vSection.getComponentCount( ); x++ )
	{
		const Mocha::DataComponent& component = vSection.getComponent( x );
		const Mocha::String& name = component.getName( );

		size_t paramCount = component.getParamCount( );

		if ( name == "image" )
		{
			if ( paramCount != 2 )
				throw Exception( "Invalid token count in 'image' tag" );

			const Mocha::String& path = component.getParam( 1 );

			Mocha::RefPointer<Texture> img = Core::Get( ).getTextureManager( ).getTexture( path );
			setTexture( component.getParam( 0 ), img );
		}
		else if ( name == "float" )
		{
			if ( paramCount != 2 )
				throw Exception( "Invalid token count in 'float' tag" );

			setFloat( component.getParam( 0 ), component.getParamFloat( 1 ) );
		}
		else if ( name == "font" )
		{
			if ( paramCount != 3 )
				throw Exception( "Invalid token count in 'font' tag" );

			Mocha::RefPointer<Font> f = Core::Get( ).getFontManager( ).getFont( component.getParam( 1 ), component.getParamInt( 2 ) );
			setFont( component.getParam( 0 ), f );
		}
		else if ( name == "default_font" )
		{
			if ( paramCount != 2 )
				throw Exception( "Invalid token count in 'default_font' tag" );

			Mocha::RefPointer<Font> f = Core::Get( ).getFontManager( ).getFont( component.getParam( 0 ), component.getParamInt( 1 ) );
			setDefaultFont( f );
		}
		else if ( name == "color" )
		{
			if ( paramCount != 2 )
				throw Exception( "Invalid token count in 'color' tag" );

			setColor( component.getParam( 0 ), component.getParamColor( 1 ) );
		}
	}
}

}
