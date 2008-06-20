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

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Mocha/Buffer.h"

#include "RBGui/FontManager.h"
#include "RBGui/Exception.h"
#include "RBGui/Core.h"

#define GLYPH_LIST "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!?@#$%^&*()_-+|\\<>/:;'=~`[]{}.,\" "
#define GLYPH_PAD_SPACE 2

namespace RBGui
{

//--------------------------------
FontManager::FontManager( )
{
	// ...
}

//--------------------------------
FontManager::~FontManager( )
{
	// ...
}

//--------------------------------------------
static void getRequiredTextureSize( Font* vFont, FT_Face vFace, const Mocha::String& vText, int& vTexWidth, int& vTexHeight )
{
	int maxGlyphHeight = 0;

	int texSizeX = 16;
	int texSizeY = 16;

	int width;

	int cur_x = 0;
	int cur_y = maxGlyphHeight;

	int vTextSize = (int)vText.size( );

	int i;
	for ( i = 0; i < vTextSize; i++ )
	{
		// load-up required glyph

		if ( FT_Load_Char( vFace, vText[i], FT_LOAD_RENDER  ) )
		{
			// skip errors
			continue;
		}

		// if this glyph is taller than all others so far, update height and re-calculate cur_y

		if ( vFace->glyph->bitmap.rows + GLYPH_PAD_SPACE > maxGlyphHeight )
		{
			maxGlyphHeight = vFace->glyph->bitmap.rows + GLYPH_PAD_SPACE;
			cur_y = (i + 1) * maxGlyphHeight;
		}

		width = vFace->glyph->bitmap.width + GLYPH_PAD_SPACE;
		cur_x += width;

		// check for fit

		if ( cur_x >= texSizeX )
		{
			texSizeX += 16;

			cur_x = width;
			cur_y += maxGlyphHeight;

			if ( cur_y >= texSizeY )
			{
				texSizeY += maxGlyphHeight * 2;

				cur_x = 0;
				cur_y = maxGlyphHeight;

				i = (unsigned int)-1;
			}
		}
	}

	vTexWidth = texSizeX;
	vTexHeight = texSizeY;

	vFont->setMaxGlyphHeight( maxGlyphHeight );
}

//--------------------------------------------
static void copyGlyph( FT_Bitmap* vBitmap, Mocha::int32* vBuffer, int vWidth )
{
	int i;
	for ( i = 0; i < vBitmap->rows; i++ )
	{
		int j;
		for ( j = 0; j < vBitmap->width; j++ )
		{
			Mocha::int8* bytebuff = (Mocha::int8*)( &vBuffer[j] );

			*bytebuff++ = 0xFF;
			*bytebuff++ = 0xFF;
			*bytebuff++ = 0xFF;
			*bytebuff = vBitmap->buffer[ (i * vBitmap->pitch) + j ];
		}

		vBuffer += vWidth;
	}
}

//--------------------------------------------
static void renderGlyphs( Font* vFont, FT_Face vFace, const Mocha::String& vText, Mocha::int32* vBuffer, int vTexSize )
{
	GlyphMap& glyphs = vFont->getGlyphMap( );
	FT_GlyphSlot slot = vFace->glyph;

	int count = (int)vText.size( );
	int width;

	int cur_x = 0;
	int cur_y = 0;

	int maxBearingY = 0;

	int x;
	for ( x = 0; x < count; x++ )
	{
		if ( FT_Load_Char( vFace, vText[x], FT_LOAD_RENDER ) )
			continue;

		width = slot->bitmap.width + GLYPH_PAD_SPACE;
		
		// see if we need to wrap to next row
		if ( ( cur_x + width ) >= vTexSize )
		{
			cur_x = 0;
			cur_y += vFont->getMaxGlyphHeight( );
		}

		// calculate offset into buffer for this glyph
		Mocha::int32* dest_buffer = vBuffer + ( cur_y * vTexSize ) + cur_x;
		copyGlyph( &slot->bitmap, dest_buffer, vTexSize );

		// Setup the glyph data
		Mocha::Rectangle rect;
		rect.left	= (float)cur_x;
		rect.top = (float)cur_y;
		rect.right = (float)( cur_x + width - GLYPH_PAD_SPACE );
		rect.bottom = (float)( cur_y + vFont->getMaxGlyphHeight( ) - GLYPH_PAD_SPACE );

		float offsetX = (float)( slot->metrics.horiBearingX >> 6 );
		float offsetY = -(float)( slot->metrics.horiBearingY >> 6 );

		glyphs[ vText[x] ] = Glyph( rect, (float)(slot->advance.x >> 6), offsetX, offsetY );

		cur_x += width;

		// Check and update maximum bearingY value
		if ( ( slot->metrics.horiBearingY >> 6 ) > maxBearingY )
			maxBearingY = ( slot->metrics.horiBearingY >> 6 );
	}

	vFont->setMaxBearingY( maxBearingY );
}

//--------------------------------------------
static void decode( Font* vFont, const Mocha::Stream& vStream, size_t vSize )
{
	// Open the freetype file data

	FT_Library lib;
	FT_Face face;

	if ( FT_Init_FreeType( &lib ) )
		throw Exception( "Unable to initialize FreeType" );

	int size = vStream.getSize( );

	Mocha::Buffer fontBuffer;
	fontBuffer.allocate( size );

	vStream.readData( fontBuffer, size );

	if ( FT_New_Memory_Face( lib, (FT_Byte*)fontBuffer.get( ), fontBuffer.getSize( ), 0, &face ) )
		throw Exception( "Unable to load font" );

	if ( FT_Set_Char_Size( face, 0, vSize * 64, 96, 96 ) )
		throw Exception( "Unable to set font size" );

	// Get the size of the texture

	int texWidth;
	int texHeight;
	getRequiredTextureSize( vFont, face, GLYPH_LIST, texWidth, texHeight );

	// Create and initialize the texture

	Mocha::RefPointer<Texture> tex = Core::Get( ).getTextureManager( ).createTexture( Mocha::Vector2( texWidth, texHeight ) );
	
	// Clear texture and render glyphs

	void* buffer = tex->lock( );

	memset( buffer, 0, texWidth * texHeight * sizeof( Mocha::int32 ) );
	renderGlyphs( vFont, face, GLYPH_LIST, (Mocha::int32*)buffer, texWidth );

	tex->unlock( );

	// Store texture in font

	vFont->setTexture( tex );
}

//--------------------------------
Font* FontManager::loadFont( const Mocha::String& vName, size_t vSize )
{
	// Open the file stream

	Mocha::RefPointer<Mocha::Stream> stream = Core::Get( ).getResourceManager( ).getResource( vName );
	if ( stream == 0 )
		throw Exception( "Unable to load file " + vName );

	// Create font and decode from stream

	Font* font = new Font( );
	decode( font, *stream, vSize );

	// All done!

	return font;
}

//--------------------------------
Font* FontManager::getFont( const Mocha::String& vName, size_t vSize )
{
	// Try to find font in list

	FontList::const_iterator it;
	for ( it = mFonts.begin( ); it != mFonts.end( ); it++ )
	{
		const FontEntry& entry = (*it);
		if ( (entry.name == vName) && (entry.size == vSize) )
			return entry.font;
	}

	// Load the font

	Mocha::RefPointer<Font> font = loadFont( vName, vSize );

	// Add font entry and return

	mFonts.push_back( FontEntry( vName, vSize, font ) );
	return font;
}

//--------------------------------
void FontManager::flush( )
{
	FontList::iterator it = mFonts.begin( );
	while ( it != mFonts.end( ) )
	{
		if ( (*it).font->getRefCount( ) == 1 )
			it = mFonts.erase( it );
		else
			it++;
	}
}

}
