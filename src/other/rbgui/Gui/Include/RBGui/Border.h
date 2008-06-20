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

#ifndef GUI_GUIBORDER_H
#define GUI_GUIBORDER_H

#include "Mocha/Object.h"
#include "Mocha/RefPointer.h"
#include "Mocha/Rectangle.h"
#include "Mocha/DataSection.h"
#include "Mocha/Vector2.h"
#include "Mocha/Color.h"

#include "RBGui/Brush.h"

namespace RBGui
{

//--------------------------------
enum BorderPart
{
	BORDER_TOP = 0,
	BORDER_BOTTOM,
	BORDER_LEFT,
	BORDER_RIGHT,
	BORDER_TOPLEFT,
	BORDER_BOTTOMLEFT,
	BORDER_TOPRIGHT,
	BORDER_BOTTOMRIGHT,
	BORDER_CENTER
};

//--------------------------------
class GuiManager;

//--------------------------------
/// A border defines how the edges of a gui element should be drawn
class GUI_EXPORT Border : public Mocha::Object
{
private:
	class GuiBorderState
	{
	public:
		Mocha::RefPointer<Texture> texture;

		Mocha::RefPointer<Texture> closeButton;

		Mocha::Color bgColor1;

		Mocha::Color bgColor2;
	};

	typedef std::map<Mocha::String, GuiBorderState> StateMap;
	mutable StateMap mStates;

	Mocha::Vector2 mCloseButtonPos;

	Mocha::Rectangle mClientAdjust;

	Mocha::Rectangle mParts[9];

	Mocha::Vector2 mMinSize;

	Mocha::Vector2 mTextPos;

	GradientType mGradientType;

	bool mRenderCenter;

	bool mTileCenter;

	bool mTileEdges;

	GuiBorderState& getState( const Mocha::String& vName );

	const GuiBorderState& getState( const Mocha::String& vName ) const;

public:
	Border( );

	virtual ~Border( );

	/// Returns whether or not the given state name exists
	/*! \param vName The name of the state to test */
	bool hasState( const Mocha::String& vName ) const;

	/// Sets the type of the gradient to use for the background. See GradientType
	void setGradientType( GradientType vType );

	/// Gets the type of the gradient that will be used for the background
	GradientType getGradientType( ) const;

	/// Sets the first background color to use for the gradient
	/*! \param vColor The color to use
		\param vState The state to assign the color to */
	void setBackgroundColor1( const Mocha::Color& vColor, const Mocha::String& vState = "default" );

	/// Gets the first background color for the gradient
	/*! \param vState The state to get the color from */
	const Mocha::Color& getBackgroundColor1( const Mocha::String& vState = "default" ) const;

	/// Sets the second background color to use for the gradient
	/*! \param vColor The color to use
		\param vState The state to assign the color to */
	void setBackgroundColor2( const Mocha::Color& vColor, const Mocha::String& vState = "default" );

	/// Gets the second background color for the gradient
	/*! \param vState The state to get the color from */
	const Mocha::Color& getBackgroundColor2( const Mocha::String& vState = "default" ) const;

	/// Sets a rectangle that defines the amount to adjust a given rectangle to calculate the client region
	/*! \param The rectangle that defines the relative amount to adjust a rectangle to get the client region */
	void setClientAdjust( const Mocha::Rectangle& vAdjust );

	/// Gets the client adjust rectangle (See setClientAdjust)
	const Mocha::Rectangle& getClientAdjust( ) const;

	/// Sets the background texture to use for the border
	/*! \param vTexture The texture to use
		\param vState The border state to assign the texture to */
	void setTexture( Texture* vTexture, const Mocha::String& vState = "default" );

	/// Sets the texture to use for the close button
	/*! \param vTexture The texture to use
		\param vState The border state to assign the texture to */
	void setCloseButton( Texture* vTexture, const Mocha::String& vState = "default" );

	/// Gets the offset of the close button, relative to the upper right corner of a rectangle
	/*! \param vOffset The offset, in pixels, relative to the upper right corner of a rectangle */
	void setCloseButtonOffset( const Mocha::Vector2& vPosition );

	/// Gets the offset of the close button
	/*! \return The offset of the close button, relative to the upper right corner of a rectangle */
	const Mocha::Vector2& getCloseButtonOffset( );

	/// Sets a rectangle part of the border. This is a rectangle inside the border texture to use
	/*! \param vID The ID of the part. (See BorderPart)
		\param vRect The rectangle to use for this part, in pixels */
	void setPart( BorderPart vID, const Mocha::Rectangle& vRect );

	/// Gets the rectangle of a border part. (See BorderPart)
	const Mocha::Rectangle& getPart( BorderPart vID ) const;

	/// Draws a border
	/*! \param vBrush The brush to use for drawing
		\param vRect The rectangle to draw with the border
		\param vBackground Whether or not to draw the background of the border
		\param vCloseButton Whether or not to draw the close button of the border
		\param vClosePressed Whether or not the close button should be pressed
		\param vState The state of the border to use */
	void draw( Brush& vBrush, const Mocha::Rectangle& vRect, bool vBackground = true, bool vCloseButton = false, bool vClosePressed = false, const Mocha::String& vState = "default" );

	/// Draws only the background of the border
	/*! \param vBrush The brush to use for drawing
		\param vRect The rectangle to draw the background in
		\param vState The border state to use */
	void drawBackground( Brush& vBrush, const Mocha::Rectangle& vRect, const Mocha::String& vState = "default" );

	/// Returns whether or not the given point will be inside the close button of the border
	/*! \param vPoint The point to test
		\param vBorderRect The rectangle of the border to test with
		\param vState The border state to use
		\return True if the point is inside the close button, false if not */
	bool pointInButton( const Mocha::Vector2& vPoint, const Mocha::Rectangle& vBorderRect, const Mocha::String& vState = "default" ) const;

	/// Sets the offset of the border text
	/*! \param vPos The offset to use for rendering the border text, in pixels relative to the top left corner */
	void setTextOffset( const Mocha::Vector2& vPos );

	/// Gets the offset of the border text
	/*! \return The offset, in pixels from the top left corner of the border */
	const Mocha::Vector2& getTextOffset( ) const;

	/// Sets the minimum allowable size of a rectangle drawn with the border
	void setMinSize( const Mocha::Vector2& vSize );

	/// Gets the minimum allowable size of a rectangle drawn with the border
	const Mocha::Vector2& getMinSize( ) const;

	/// Reads the border from a data file
	/*! \param vSection The data file section to read from
		\param vManager The GuiManager to load resources into */
	void open( const Mocha::DataSection& vSection );
};

}

#endif
