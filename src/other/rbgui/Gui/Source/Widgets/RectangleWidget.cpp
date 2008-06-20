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

#include "RBGui/Widgets/RectangleWidget.h"

namespace RBGui
{

//--------------------------------------------
RectangleWidget::RectangleWidget( GuiManager* vManager )
: Widget( vManager ), mStyle( RECTANGLE_FILLED ), mCheckered( false )
{
	// ...
}

//--------------------------------------------
RectangleWidget::~RectangleWidget( )
{
	// ...
}

//--------------------------------------------
void RectangleWidget::setCheckered( bool vWhich )
{
	mCheckered = vWhich;
	flagDirty( );
}

//--------------------------------------------
bool RectangleWidget::getCheckered( ) const
{
	return mCheckered;
}

//--------------------------------------------
void RectangleWidget::setStyle( RectangleStyle vStyle )
{
	mStyle = vStyle;
	flagDirty( );
}

//--------------------------------------------
RectangleStyle RectangleWidget::getStyle( ) const
{
	return mStyle;
}

//--------------------------------------------
void RectangleWidget::onDraw( Brush& vBrush ) const
{
	// Draw the checkered background

	vBrush.setBlendMode( BRUSHBLEND_ALPHA );

	if ( mCheckered )
	{
		Theme* theme = getRenderTheme( );
		if ( theme == 0 )
			return;

		Texture* checker = theme->getTexture( "Checker" );
		if ( checker )
		{
			vBrush.setColor( Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ) );
			vBrush.setTexture( checker );
			vBrush.drawTiledRectangle( getClientRectangle( ) );
		}
	}

	// Draw the rectangle

	vBrush.setColor( getColor( ) );

	switch ( mStyle )
	{
	case RECTANGLE_FILLED:
		vBrush.setTexture( 0 );
		vBrush.drawRectangle( getClientRectangle( ) );
		break;

	case RECTANGLE_OUTLINE:
		vBrush.setTexture( 0 );
		vBrush.drawLineRectangle( getClientRectangle( ) );
		break;
	}
}

//--------------------------------
void RectangleWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Checkered", "bool", "Checkered" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Style", "list|filled|outline", "Style" ) );
}

//--------------------------------------------
Mocha::CommandResult RectangleWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setCheckered" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setCheckered( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getCheckered" )
	{
		vOut.push_back( getCheckered( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setStyle" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setStyle( (vIn[0].getAsString( ) == "outline") ? RECTANGLE_OUTLINE : RECTANGLE_FILLED );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getStyle" )
	{
		vOut.push_back( (getStyle( ) == RECTANGLE_OUTLINE) ? "outline" : "filled" );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------------------
Mocha::String RectangleWidget::getClassName( ) const
{
	return "Mocha::Rectangle";
}

//--------------------------------------------
Widget* RectangleWidget::factory( GuiManager* vManager )
{
	return new RectangleWidget( vManager );
}

}
