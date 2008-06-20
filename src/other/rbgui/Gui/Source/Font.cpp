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

#include "Mocha/StringTools.h"

#include "RBGui/Font.h"
#include "RBGui/Brush.h"
#include "RBGui/Exception.h"

namespace RBGui
{

//--------------------------------
Font::Font( )
: mMaxGlyphHeight( 0 ), mMaxBearingY( 0 ), mFontSize( 0 )
{
	clearGlyphs( );

	// Preallocate space for efficient line processing

	mLineList.reserve( 256 );
}

//--------------------------------
Font::~Font( )
{
	// ...
}

//--------------------------------
void Font::setFontSize( size_t vSize )
{
	mFontSize = vSize;
}

//--------------------------------
size_t Font::getFontSize( ) const
{
	return mFontSize;
}

//--------------------------------
void Font::setMaxGlyphHeight( size_t vValue )
{
	mMaxGlyphHeight = vValue;
}

//--------------------------------
size_t Font::getMaxGlyphHeight( ) const
{
	return mMaxGlyphHeight;
}

//--------------------------------
void Font::setMaxBearingY( int vValue )
{
	mMaxBearingY = vValue;
}

//--------------------------------
int Font::getMaxBearingY( ) const
{
	return mMaxBearingY;
}

//--------------------------------
size_t Font::getNumGlyphs( ) const
{
	return mGlyphs.size( );
}

//--------------------------------
void Font::setGlyph( size_t vChar, const Glyph& vGlyph )
{
	mGlyphs[vChar] = vGlyph;
}

//--------------------------------
void Font::clearGlyphs( )
{
	mGlyphs.clear( );

	// Create the default glyph (Used incase a particular character does not exist)

	Glyph g;
	g.mSpace = 0;

	setGlyph( 0, g );
}

//--------------------------------
float Font::getTextWidth( const Mocha::String& vText ) const
{
	size_t count = (unsigned int)vText.size( );
	float width = 0.0f;

	size_t x;
	for ( x = 0; x < count; x++ )
	{
		const Glyph& g = getGlyph( vText[x] );
		width += g.mSpace;
	}

	return width;
}

//--------------------------------
float Font::getTextHeight( const Mocha::String& vText ) const
{
	size_t count = vText.size( );
	if ( count == 0 )
		return 0.0f;

	float height = (float)getMaxGlyphHeight( );

	size_t x;
	for ( x = 0; x < count; x++ )
	{
		if ( vText[x] == '\n' )
			height += getMaxGlyphHeight( );
	}
	

	return height;
}

//--------------------------------
float Font::getTextHeight( const Mocha::String& vText, float vWidth ) const
{
	LineInfoList tmp;
	processText( vText, true, vWidth, tmp );

	return getMaxGlyphHeight( ) * (float)tmp.size( );
}

//--------------------------------
void Font::getTextSize( const Mocha::String& vText, Mocha::Vector2& vSize ) const
{
	size_t count = vText.size( );
	float xtmp;

	vSize.y = (float)mMaxGlyphHeight;
	vSize.x = 0.0f;

	xtmp = 0.0f;

	size_t x;
	for ( x = 0; x < count; x++ )
	{
		char c = vText[x];
		if ( c == '\n' )
		{
			vSize.y += mMaxGlyphHeight;
			xtmp = 0.0f;
		}
		else
		{
			const Glyph& g = getGlyph( vText[x] );
			xtmp += g.mSpace;
		}

		if ( xtmp > vSize.x )
			vSize.x = xtmp;
	}
}

//--------------------------------
int Font::getCharacterIndexAt( const Mocha::String& vText, const Mocha::Rectangle& vRect, bool vWrap, const Mocha::Vector2& vCursorLoc ) const
{
	LineInfoList lines;
	processText( vText, vWrap, vRect.getWidth( ), lines );

	return getCharacterIndexAt( lines, vRect.getPosition( ), vCursorLoc );
}

//--------------------------------
int Font::getCharacterIndexAt( const LineInfoList& vLines, const Mocha::Vector2& vLoc, const Mocha::Vector2& vPos ) const
{
	float currentX = vLoc.x;
	float currentY = vLoc.y;// + mMaxBearingY;

	size_t count = vLines.size( );
	int index = 0;

	Mocha::Vector2 pos = vPos;

	if ( pos.y < vLoc.y )
		pos.y = vLoc.y;

	float bottom = vLoc.y + (vLines.size( ) * mMaxGlyphHeight);
	if ( pos.y > bottom )
		pos.y = bottom - 1;

	// Go through each line

	LineInfoList::const_iterator it;
	for ( it = vLines.begin( ); it != vLines.end( ); it++ )
	{
		const LineInfo& li = (*it);

		const Mocha::String& text = li.text;

		// Make sure there is a possibility of the character being on this line

		if ( ( pos.y >= currentY ) && ( pos.y < currentY + getMaxGlyphHeight( ) ) )
		{
			// If the position is beyond the width of the line, just pick the last character
			
			if ( pos.x >= ( vLoc.x + li.width ) )
			{
				index += (int)li.text.size( );

				if ( it != vLines.end( )-1 )
					index -= 1;

				return index;
			}

			// If the position is before the first character, just pick first character

			if ( pos.x <= vLoc.x )
				return index;

			// Go through each character of that line
			
			Mocha::String::const_iterator it;
			for ( it = text.begin( ); it != text.end( ); it++ )
			{
				const Glyph& g = getGlyph( (*it) );
				float w = g.mRect.getWidth( );

				Mocha::Rectangle r;
				r.setPosition( currentX, currentY );
				r.setSize( w + ( g.mSpace - w ), (float)getMaxGlyphHeight( ) );
				r.translate( g.mOffsetX, 0 );

				// See if the Mocha::Vector2 is within the character rectangle
				
				if ( r.pointInside( pos ) )
				{
					// Approximate which index to use
					
					float vXPoint = pos.x - r.left;
					if ( vXPoint >= ( r.getWidth( ) / 1.5 ) )
						index += 1;

					if ( index < 0 )
						index = 0;

					return index;
				}

				// Increase total number of characters processed
				
				index++;

				currentX += g.mSpace;
			}
		}
		else
			index += (int)text.size( );

		currentX = vLoc.x;
		currentY += getMaxGlyphHeight( );
	}

	// No character found.
	
	return -1;
}

//--------------------------------
Mocha::Vector2 Font::getCharacterPosition( const Mocha::String& vText, const Mocha::Rectangle& vRect, bool vWrap, int vIndex ) const
{
	LineInfoList lines;
	processText( vText, vWrap, vRect.getWidth( ), lines );

	return getCharacterPosition( lines, vIndex, vRect.getPosition( ) );
}

//--------------------------------
Mocha::Vector2 Font::getCharacterPosition( const LineInfoList& vLines, int vIndex, const Mocha::Vector2& vPos ) const
{
	Mocha::Rectangle r;

	// Current character index
	int c = 0;

	float currentY = vPos.y;
	float currentX = vPos.x;

	LineInfoList::const_iterator it;
	for ( it = vLines.begin( ); it != vLines.end( ); it++ )
	{
		// Get current line of text
		const Mocha::String& line = (*it).text;
		int len = (int)line.size( );
	
		// Make sure the character is in this line
		if ( ( c + len ) >= vIndex )
		{
			Mocha::String::const_iterator it;
			for ( it = line.begin( ); it != line.end( ); it++ )
			{
				const Glyph& g = getGlyph( (*it) );

				// See if this is the index we want
				if ( c == vIndex )
					return Mocha::Vector2( currentX + g.mOffsetX, currentY );
				else
					currentX += g.mSpace;

				c++;
			}
		}
		else
			c += len;

		// Increase Y location
		if ( it != vLines.end( ) - 1 )
		{
			currentY += getMaxGlyphHeight( );
			currentX = vPos.x;
		}
	}

	// Just return the current location
	return Mocha::Vector2( currentX, currentY );
}

//--------------------------------
void Font::render( Brush& vBrush, const Mocha::String& vText, const Mocha::Color& vColor, const Mocha::Vector2& vPos, bool vSelection, int vSelectionStart, int vSelectionEnd ) const
{
	int count = vText.size( );

	float currentX = vPos.x;
	float currentY = vPos.y;

	const Mocha::Vector2 tsize = mTexture->getSize( );
	Mocha::Rectangle r;

	int x;
	for ( x = 0; x < count; x++ )
	{
		const Glyph& g = getGlyph( vText[x] );
		r.setPosition( currentX, currentY );

		if ( vSelection == false )
		{
			r.setSize( g.mRect.getWidth( ), g.mRect.getHeight( ) );
			r.translate( g.mOffsetX, g.mOffsetY + mMaxBearingY );

			Mocha::Rectangle uvr = g.mRect;

			uvr.left /= tsize.x;
			uvr.right /= tsize.x;
			uvr.top /= tsize.y;
			uvr.bottom /= tsize.y;

			vBrush.addGlyph( r, uvr );
		}
		else
		{
			r.setSize( g.mSpace, mMaxGlyphHeight );
			r.setPosition( r.left, r.top );

			if ( (x >= vSelectionStart) && (x < vSelectionEnd) )
				vBrush.addGlyph( r, Mocha::Rectangle( ) );
		}

		currentX += g.mSpace;
	}
}

//--------------------------------
Mocha::Vector2 calculatePos( const Mocha::Rectangle& vRect, float vWidth, float vHeight, TextAlignmentMode vHorzAlign, TextAlignmentMode vVertAlign )
{
	float rwidth = vRect.getWidth( );
	float rheight = vRect.getHeight( );

	float posx;
	float posy;

	// Adjust for horizontal alignment
	switch ( vHorzAlign )
	{
	case TEXTALIGN_LEFT:
		posx = vRect.left;
		break;

	case TEXTALIGN_RIGHT:
		posx = vRect.right - vWidth;
		break;

	case TEXTALIGN_CENTER:
		posx  = (vRect.left + ( rwidth / 2 )) - ( vWidth / 2 );
		break;
	}

	// Adjust for vertical alignment
	switch ( vVertAlign )
	{
	case TEXTALIGN_TOP:
		posy = vRect.top;
		break;

	case TEXTALIGN_BOTTOM:
		posy = vRect.bottom - vHeight;
		break;

	case TEXTALIGN_CENTER:
		posy  = (vRect.top + ( rheight / 2 )) - ( vHeight / 2 );
		break;
	}

	return Mocha::Vector2( posx, posy );
}

//--------------------------------
inline bool isDelim( char c )
{
	return ( ( c == ' ' ) || ( c == '\n' ) );
}

//--------------------------------
void Font::processText( const Mocha::String& vText, bool vWrap, float vWidth, LineInfoList& vOut ) const
{
	// Get the total size of the text
	unsigned int count = (unsigned int)vText.size( );

	// Stores pixel width of line and word
	float lineWidth = 0.0f;
	float wordWidth = 0.0f;

	// Stores current word
	Mocha::String word;

	// Stores the current line
	Mocha::String line;

	unsigned int x;
	for ( x = 0; x < count; x++ )
	{
		char c = vText[x];

		// Add the new character to the current word
		wordWidth += getGlyph( c ).mSpace;
		word += c;

		if ( isDelim( c ) || ( x == ( count-1 ) ) )
		{
			// Is this line too long to fit?
			if ( vWrap && ( lineWidth + wordWidth > vWidth ) )
			{
				// Save current line
				vOut.push_back( LineInfo( line, lineWidth ) );

				// Reset line width
				lineWidth = 0.0f;
				line = "";
			}
			if ( c == '\n' )
			{
				// Save current line
				vOut.push_back( LineInfo( line + word, lineWidth + wordWidth ) );

				// Reset line width
				lineWidth = 0.0f;
				wordWidth = 0.0f;

				line = "";
				word = "";
			}
			else
			{
				lineWidth += wordWidth;
				line += word;

				wordWidth = 0.0f;
				word = "";
			}
		}
	}

	// Push any remaining text onto list
	vOut.push_back( LineInfo( line + word, lineWidth + wordWidth ) );
}

//--------------------------------
void Font::renderAligned( Brush& vBrush, const Mocha::String& vText, const Mocha::Color& vColor, const Mocha::Rectangle& vRect, bool vUseTex, TextAlignmentMode vHorzAlign, TextAlignmentMode vVertAlign, bool vWrap ) const
{
	// Process the text block into lines

	mLineList.resize( 0 );
	processText( vText, vWrap, vRect.getWidth( ), mLineList );
	
	renderAligned( vBrush, mLineList, vColor, vRect, vUseTex, vHorzAlign, vVertAlign );
}

//--------------------------------
void Font::renderAligned( Brush& vBrush, const LineInfoList& vLineList, const Mocha::Color& vColor, const Mocha::Rectangle& vRect, bool vUseTex, TextAlignmentMode vHorzAlign, TextAlignmentMode vVertAlign, bool vSelection, int vSelectionStart, int vSelectionEnd ) const
{
	// Get the total height of the text (If we need it)

	float textHeight = 0.0f;
	if ( vVertAlign != TEXTALIGN_TOP )
		textHeight = (float)(mLineList.size( ) * getMaxGlyphHeight( ));

	float currentY = 0.0f;
	size_t charIndex = 0;

	// Get screen space clip region and Brush position

	Mocha::Rectangle clip = vBrush.getClipRegion( );
	Mocha::Vector2 pos;

	// Go through each character

	LineInfoList::const_iterator it;
	for ( it = vLineList.begin( ); it != vLineList.end( ); it++ )
	{
		const LineInfo& line = (*it);

		// Get the rendering position

		Mocha::Vector2 npos = calculatePos( vRect, line.width, textHeight, vHorzAlign, vVertAlign );
		npos.y += currentY;

		// See if this line actually needs to be rendered

		if ( !clip.isZero( ) )
		{
			if ( ( npos.y + getMaxGlyphHeight( ) + pos.y ) < clip.top )
			{
				currentY += getMaxGlyphHeight( );
				charIndex += line.text.size( );

				continue;
			}
			else if ( (npos.y + pos.y) > clip.bottom )
				return;
		}

		int start = vSelectionStart - charIndex;
		int end = vSelectionEnd - charIndex;

		// Render the line of text

		render( vBrush, line.text, vColor, npos, vSelection, start, end ); 

		// Reset the current line

		currentY += getMaxGlyphHeight( );
		charIndex += line.text.size( );
	}
}

//--------------------------------
void Font::setTexture( Texture* vTexture )
{
	mTexture = vTexture;
}

//--------------------------------
Texture* Font::getTexture( ) const
{
	return mTexture;
}

}
