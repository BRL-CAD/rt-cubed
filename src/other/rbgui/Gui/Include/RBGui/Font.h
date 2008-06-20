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

#ifndef GUI_GUIFONT_H
#define GUI_GUIFONT_H

#include <vector>
#include <map>

#include "Mocha/Platform.h"
#include "Mocha/Object.h"
#include "Mocha/Vector2.h"
#include "Mocha/RefPointer.h"
#include "Mocha/Rectangle.h"

#include "RBGui/GuiDefines.h"
#include "RBGui/Texture.h"

namespace RBGui
{

//--------------------------------
/// Stores the rectangle of a single glyph within a font texture
class Glyph
{
public:
	inline Glyph( const Mocha::Rectangle& vRect, float vSpace, float vOffsetX, float vOffsetY )
		: mRect( vRect ), mSpace( vSpace ), mOffsetX( vOffsetX ), mOffsetY( vOffsetY )
	{
		// ...
	}

	inline Glyph( const Glyph& vOther )
		: mRect( vOther.mRect ), mSpace( vOther.mSpace ), mOffsetX( vOther.mOffsetX ), mOffsetY( vOther.mOffsetY )
	{
		// ...
	}

	inline Glyph( )
		: mSpace( 0.0f ), mOffsetX( 0.0f ), mOffsetY( 0.0f )
	{
		// ...
	}

	Mocha::Rectangle mRect;

	float mOffsetX;

	float mOffsetY;

	float mSpace;
};

typedef std::map<size_t, Glyph> GlyphMap;

//--------------------------------
/// Stores the contents and width of a single line of text. Used for optimized caching of pre-processed GUI text
struct LineInfo
{
public:
	inline LineInfo( const Mocha::String& vText, float vWidth )
		: text( vText ), width( vWidth )
	{
		// ...
	}

	inline LineInfo( )
		: width( 0.0f )
	{
		// ...
	}

	Mocha::String text;

	float width;
};

typedef std::vector<LineInfo> LineInfoList;

//--------------------------------
class Brush;

//--------------------------------
/// Manages font rendering
class GUI_EXPORT Font : public Mocha::Object
{
protected:
	GlyphMap mGlyphs;

	Mocha::RefPointer<Texture> mTexture;

	mutable LineInfoList mLineList;

	int mMaxBearingY;

	size_t mMaxGlyphHeight;

	size_t mFontSize;

public:
	Font( );

	virtual ~Font( );

	/// Sets the character to use the provided Glyph
	/*! \param vChar The character that represents the Glyph
		\param vGlyph The font Glyph to use for the character */
	void setGlyph( size_t vChar, const Glyph& vGlyph );
	
	/// Gets the font Glyph that represents the provided character
	/*! \param vChar The character you want to find the Glyph for
		\return The Glyph that represents the character. If the character is not found, a 'null glyph' is returned. */
	inline const Glyph& getGlyph( size_t vChar ) const
	{
		GlyphMap::const_iterator it = mGlyphs.find( vChar );
		if ( it == mGlyphs.end( ) )
			return (*mGlyphs.find( 0 )).second;

		return (*it).second;
	}

	/// Gets the glyph map
	/*! \return A reference to the map of glyphs */
	inline GlyphMap& getGlyphMap( )
	{
		return mGlyphs;
	}

	/// Sets the size of the font
	/*! \param vSize The size of the font to use */
	void setFontSize( size_t vSize );

	/// Gets the size of the font
	/*! \return The size of the font */
	size_t getFontSize( ) const;

	/// Sets the texture that contains the rendered font glyphs
	/*! \param vTexture A pointer to the texture containing the glyphs */
	void setTexture( Texture* vTexture );

	/// Gets the texture that contains the rendered font glyphs, used for rendering
	/*! \return The texture that contains the rendered font glyphs */
	Texture* getTexture( ) const;

	/// Gets the number of Glyphs in the font
	/*! \return The number of Glypgs in the font */
	size_t getNumGlyphs( ) const;

	/// Clears all Glyphs from the font
	void clearGlyphs( );

	/// Sets the maximum height of the glyphs (The tallest Glyph height)
	/*! \param vSize The maximum height */
	void setMaxGlyphHeight( size_t vValue );

	/// Gets the maximum height of the glyphs (The tallest Glyph height)
	/*! \return The maximum height of the glyphs */
	size_t getMaxGlyphHeight( ) const;

	/// Sets the maximum Y bearing of the font
	/*! \vParam vSize The maximum Y bearing of the font. I don't exactly remember what this is used for. :P */
	void setMaxBearingY( int vValue );

	/// Gets the maximum Y bearing of the font
	/*! \return The maximum Y bearing of the font. I don't exactly remember what this is used for. :P */
	int getMaxBearingY( ) const;

	int getCharacterIndexAt( const Mocha::String& vText, const Mocha::Rectangle& vRect, bool vWrap, const Mocha::Vector2& vCursorLoc ) const;

	int getCharacterIndexAt( const LineInfoList& vLines, const Mocha::Vector2& vLoc, const Mocha::Vector2& vPos ) const;

	Mocha::Vector2 getCharacterPosition( const Mocha::String& vText, const Mocha::Rectangle& vRect, bool vWrap, int vIndex ) const;

	Mocha::Vector2 getCharacterPosition( const LineInfoList& vLines, int vIndex, const Mocha::Vector2& vPos ) const;

	float getTextWidth( const Mocha::String& vText ) const;
	
	float getTextHeight( const Mocha::String& vText ) const;

	float getTextHeight( const Mocha::String& vText, float vWidth ) const;

	void getTextSize( const Mocha::String& vText, Mocha::Vector2& vSize ) const;

	void processText( const Mocha::String& vText, bool vWrap, float vWidth, LineInfoList& vOut ) const;

	void render( Brush& vBrush, const Mocha::String& vText, const Mocha::Color& vColor, const Mocha::Vector2& vPos, bool vSelection = false, int vSelectionStart = -1, int vSelectionEnd = -1 ) const;

	void renderAligned( Brush& vBrush, const Mocha::String& vText, const Mocha::Color& vColor, const Mocha::Rectangle& vRect, bool vUseTex = true, TextAlignmentMode vHorzAlign = TEXTALIGN_LEFT, TextAlignmentMode vVertAlign = TEXTALIGN_TOP, bool vWrap = false ) const;

	void renderAligned( Brush& vBrush, const LineInfoList& vLineList, const Mocha::Color& vColor, const Mocha::Rectangle& vRect, bool vUseTex = true, TextAlignmentMode vHorzAlign = TEXTALIGN_LEFT, TextAlignmentMode vVertAlign = TEXTALIGN_TOP, bool vSelection = false, int vSelectionStart = -1, int vSelectionEnd = -1 ) const;
};

}

#endif
