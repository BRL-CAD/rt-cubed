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

#include "RBGui/Widgets/TextWidget.h"

namespace RBGui
{

//--------------------------------
TextWidget::TextWidget( GuiManager* vManager )
: Widget( vManager ), mWrap( false ), mHorizontalAlignment( TEXTALIGN_LEFT ), mVerticalAlignment( TEXTALIGN_TOP )
{
	// ...
}

//--------------------------------
TextWidget::~TextWidget( )
{
	// ...
}

//--------------------------------
Mocha::String TextWidget::getClassName( ) const
{
	return "Text";
}

//--------------------------------
void TextWidget::setVerticalTextAlignment( TextAlignmentMode vMode )
{
	mVerticalAlignment = vMode;
	flagDirty( );
}

//--------------------------------
TextAlignmentMode TextWidget::getVerticalTextAlignment( ) const
{
	return mVerticalAlignment;
}

//--------------------------------
void TextWidget::setHorizontalTextAlignment( TextAlignmentMode vMode )
{
	mHorizontalAlignment = vMode;
	flagDirty( );
}

//--------------------------------
TextAlignmentMode TextWidget::getHorizontalTextAlignment( ) const
{
	return mHorizontalAlignment;
}

//--------------------------------
void TextWidget::setWrap( bool vWhich )
{
	mWrap = vWhich;
	flagDirty( );
}

//--------------------------------
bool TextWidget::getWrap( ) const
{
	return mWrap;
}

//--------------------------------
void TextWidget::onDraw( Brush& vBrush ) const
{
	// Get the theme and font

	Theme* theme = getRenderTheme( );
	Font* f = getRenderFont( );

	if ( (theme == 0) || (f == 0) )
		return;

	// Set blend mode, color and render text

	vBrush.setColor( getRenderColor( ) );
	vBrush.setBlendMode( BRUSHBLEND_ALPHA );

	vBrush.drawText( f, getText( ), getClientRectangle( ),
					mWrap, mHorizontalAlignment, mVerticalAlignment );
}

//--------------------------------
void TextWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Wrap", "bool", "Word Wrap" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "VerticalTextAlignment", "list|top|center|bottom", "Vertical Text Alignment" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "HorizontalTextAlignment", "list|left|center|right", "Horizontal Text Alignment" ) );
}

//--------------------------------
Mocha::CommandResult TextWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setWrap" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setWrap( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getWrap" )
	{
		vOut.push_back( getWrap( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setVerticalTextAlignment" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setVerticalTextAlignment( StringToTextAlignmentMode( vIn[0].getAsString( ) ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getVerticalTextAlignment" )
	{
		vOut.push_back( TextAlignmentModeToString( getVerticalTextAlignment( ) ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setHorizontalTextAlignment" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setHorizontalTextAlignment( StringToTextAlignmentMode( vIn[0].getAsString( ) ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getHorizontalTextAlignment" )
	{
		vOut.push_back( TextAlignmentModeToString( getHorizontalTextAlignment( ) ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
Widget* TextWidget::factory( GuiManager* vManager )
{
	return new TextWidget( vManager );
}

}
