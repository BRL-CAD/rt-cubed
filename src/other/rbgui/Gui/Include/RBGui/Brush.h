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

#ifndef GUI_GUIBRUSH_H
#define GUI_GUIBRUSH_H

#include "OgreHardwareVertexBuffer.h"
#include "OgreRenderOperation.h"
#include "OgreMaterial.h"

#include "Mocha/Object.h"
#include "Mocha/Color.h"
#include "Mocha/Rectangle.h"
#include "Mocha/RefPointer.h"
#include "Mocha/Vector2.h"

#include "RBGui/GuiDefines.h"
#include "RBGui/Font.h"

namespace RBGui
{

//--------------------------------
class Texture;

//--------------------------------
/// Main interface used for drawing 2D graphics
class Brush : public Mocha::Object
{
public:
	/// Converts a pixel rectangle into a final screen-space rectangle, suitable for rendering directly
	virtual Mocha::Rectangle getScreenRectangle( const Mocha::Rectangle& vRectangle ) = 0;

	/// Gets the size of the screen, in pixels
	virtual Mocha::Vector2 getScreenSize( ) = 0;

	/// Sets the current texture to draw into
	virtual void setTarget( Texture* vTexture ) = 0;

	/// Sets the current texture to draw with
	virtual void setTexture( Texture* vTexture ) = 0;

	/// Sets the current color to draw with
	virtual void setColor( const Mocha::Color& vColor ) = 0;

	/// Sets the current clip region rectangle, in pixels
	virtual void setClipRegion( const Mocha::Rectangle& vRectangle ) = 0;

	/// Gets the current clip region rectangle, in pixels
	virtual const Mocha::Rectangle& getClipRegion( ) const = 0;

	/// Sets the blend mode to use. (See BrushBlendMode)
	virtual void setBlendMode( BrushBlendMode vMode ) = 0;

	/// Sets the filtering mode to use (See BrushFilterMode)
	virtual void setFilterMode( BrushFilterMode vMode ) = 0;

	/// Draws a tiled image within the provided rectangle
	virtual void drawTiledRectangle( const Mocha::Rectangle& vRectangle ) = 0;

	/// Draws a tiled image within the provided rectangle
	/*! \param vRectangle The rectangle to draw to
		\param vSubRect The rectangle within the current texture to tile */
	virtual void drawTiledRectangle( const Mocha::Rectangle& vRectangle, const Mocha::Rectangle& vSubRect ) = 0;

	/// Draws a rectangle with a unique color at each corner
	virtual void drawColorRectangle( const Mocha::Rectangle& vRect, const Mocha::Color& vTopLeft, const Mocha::Color& vTopRight, const Mocha::Color& vLowerLeft, const Mocha::Color& vLowerRight ) = 0;

	/// Draws a gradient rectangle
	virtual void drawGradient( const Mocha::Rectangle& vRect, GradientType vType, const Mocha::Color& vColor1, const Mocha::Color& vColor2 ) = 0;

	/// Draws a rectangle with the current texture, color settings
	/*! \param vRectangle The rectangle to draw to
		\param vUV The UV coordinates to use
		\param vRelative True if the UV coordinates are relative, false if they are positive */
	virtual void drawRectangle( const Mocha::Rectangle& vRectangle, const Mocha::Rectangle& vUV = Mocha::Rectangle( 0.0f, 0.0f, 1.0f, 1.0f ), bool vUVRelative = true ) = 0;

	/// Draws a string of text into a rectangle using a given font
	virtual void drawText( Font* vFont, const Mocha::String& vText, const Mocha::Rectangle& vRect, bool vWrap = false, TextAlignmentMode vHorzAlign = TEXTALIGN_LEFT, TextAlignmentMode vVertAlign = TEXTALIGN_TOP ) = 0;

	/// Draws a set of pre-processed text lines using a given font
	virtual void drawText( Font* vFont, const LineInfoList& vText, const Mocha::Rectangle& vRect, TextAlignmentMode vHorzAlign = TEXTALIGN_LEFT, TextAlignmentMode vVertAlign = TEXTALIGN_TOP, bool vSelection = false, int vSelectionStart = -1, int vSelectionEnd = -1 ) = 0;

	/// Draws a line
	virtual void drawLine( const Mocha::Vector2& vPoint1, const Mocha::Vector2& vPoint2 ) = 0;

	/// Begin rendering a batch of lines
	virtual void beginLines( ) = 0;

	/// Adds a line to the batch. Do not call this outside of beginLines/endLines
	virtual void addLine( const Mocha::Vector2& vPoint1, const Mocha::Vector2& vPoint2 ) = 0;

	/// Ends a batch of lines and renders them
	virtual void endLines( ) = 0;

	/// Draws a rectangle made of lines
	virtual void drawLineRectangle( const Mocha::Rectangle& vRectangle ) = 0;

	/// Begins rendering a batch of triangles
	virtual void beginTriangles( ) = 0;

	/// Adds a triangle vertex to the batch
	virtual void addTriangleVertex( const Mocha::Vector2& vPoint, const Mocha::Vector2& vUV, bool vScreenSpace = false ) = 0;

	/// Ends a batch of triangles and renders them
	virtual void endTriangles( ) = 0;

	/// Begin rendering a rectangle glyph batch
	virtual void beginGlyphs( ) = 0;

	/// Adds a batched glyph rectangle. Do not call this outside of beginGlyphs/endGlyphs
	virtual void addGlyph( const Mocha::Rectangle& vRect, const Mocha::Rectangle& vUV, bool vUVRelative = true ) = 0;

	/// Ends a batch of glyphs and renders them
	virtual void endGlyphs( ) = 0;

	/// Clears the current target using the current color
	virtual void clear( ) = 0;

	/// Begins drawing operations
	virtual void begin( ) = 0;

	/// Ends drawing operations
	virtual void end( ) = 0;
};

}

#endif
