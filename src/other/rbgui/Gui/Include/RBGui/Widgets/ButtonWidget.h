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

#ifndef OLIVIA_BUTTONGUIWIDGET_H
#define OLIVIA_BUTTONGUIWIDGET_H

#include "RBGui/Widget.h"

namespace RBGui
{

//--------------------------------
enum ButtonImageAlign
{
	BUTTONIMAGEALIGN_LEFT = 0,
	BUTTONIMAGEALIGN_CENTER
};

//--------------------------------
/// A simple button widget that can display text and an optional image
class GUI_EXPORT ButtonWidget : public Widget
{
private:
	Mocha::RefPointer<Texture> mImage;

	ButtonImageAlign mImageAlign;

	bool mAnimatedImage;

	bool mPressed;

	bool mSink;

	bool mDown;

protected:
	virtual void onDraw( Brush& vBrush ) const;

public:
	ButtonWidget( GuiManager* vManager );

	virtual ~ButtonWidget( );

	virtual Mocha::String getClassName( ) const;

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual void onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint );

	/// Sets the image alignment (See ButtonImageAlign)
	void setImageAlignment( ButtonImageAlign vMode );

	/// Gets the image alignment (See ButtonImageAlign)
	ButtonImageAlign getImageAlignment( ) const;

	/// Sets whether or not this image is animated (Changes when button is pushed)
	/*! \param vWhich True if the image should be animated, false if not */
	void setAnimatedImage( bool vWhich );

	/// Gets whether or not the image is animated
	/*! \return True if the image is animated, false if not */
	bool getAnimatedImage( ) const;

	/// Sets whether or not the contents of the button should 'sink' by an offset when pushed
	void setSink( bool vWhich );

	/// Gets whether or not the contents of the button should 'sink' by an offset when pushed
	bool getSink( ) const;

	/// Sets the image to draw in the button by name
	/*! \param vName The name of the texture to use */
	void setImage( const Mocha::String& vName );

	/// Sets the texture to draw in the button
	void setImage( Texture* vTexture );

	/// Gets the texture that will be drawn in the button
	Texture* getImage( ) const;

	static Widget* factory( GuiManager* vManager );
};

}

#endif
