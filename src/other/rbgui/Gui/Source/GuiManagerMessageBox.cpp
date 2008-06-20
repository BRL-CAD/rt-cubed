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

#include "RBGui/GuiManager.h"

#include "RBGui/Widgets/TextWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"

namespace RBGui
{

//--------------------------------
class MessageBoxCallback : public GuiCallback
{
private:
	GuiCallback* mMainCallback;

public:
	MessageBoxCallback( GuiCallback* vMainCallback )
		: mMainCallback( vMainCallback )
	{
		// ...
	}

	virtual void onGuiEvent( GuiElement& vElement, const Mocha::ValueList& vData )
	{
		// Close the window

		static_cast<Widget&>( vElement ).getWindow( )->close( );

		// Do main callback

		if ( mMainCallback )
			mMainCallback->onGuiEvent( vElement, vData );
	}
};

//--------------------------------
Window* GuiManager::createMessageBox( const Mocha::String& vTitle, const Mocha::String& vText, GuiCallback* vCallback, const Mocha::Vector2& vMinSize )
{
	const float buttonwidth = 100.0f;
	const float buttonheight = 30.0f;

	// Create the window

	Window* window = createWindow( );
	window->setResizeable( false );
	window->setCloseable( false );
	window->setModal( true );
	window->setText( vTitle );

	// Setup text label

	TextWidget* text = static_cast<TextWidget*>( window->createWidget( "Text" ) );
	text->setHorizontalTextAlignment( TEXTALIGN_CENTER );
	text->setVerticalTextAlignment( TEXTALIGN_CENTER );
	text->setName( "Text" );
	text->setText( vText );
	text->setWrap( true );

	// Get size of text region

	Font* f = text->getRenderFont( );
	if ( f )
	{
		Mocha::Vector2 size;
		f->getTextSize( vText, size );

		size = Mocha::Vector2( Mocha::max( vMinSize.x, size.x ), Mocha::max( vMinSize.y, size.y ) );
		window->setSize( size );
	}
	else
		window->setSize( vMinSize );

	const Mocha::Rectangle& r = window->getClientRectangle( );
	const float ypadding = 5.0f;

	// Set text rectangle

	text->setRectangle( 0.0f, 0.0f, r.getWidth( ), r.getHeight( ) - buttonheight );

	// Setup the button

	ButtonWidget* button = static_cast<ButtonWidget*>( window->createWidget( "Button" ) );
	button->setRectangle( (r.getWidth( )/2) - (buttonwidth/2), r.getHeight( )-(buttonheight+ypadding), buttonwidth, buttonheight );
	button->setName( "Button" );
	button->setText( "Okay" );
	button->setCallback( new MessageBoxCallback( vCallback ) );

	// Center window

	window->centerX( );
	window->centerY( );

	// All done!

	return window;
}

}
