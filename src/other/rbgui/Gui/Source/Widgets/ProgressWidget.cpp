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

#include "RBGui/Widgets/ProgressWidget.h"

namespace RBGui
{

//--------------------------------
ProgressWidget::ProgressWidget( GuiManager* vManager )
: Widget( vManager ), mValue( 0.0f )
{
	// ...
}

//--------------------------------
ProgressWidget::~ProgressWidget( )
{
	// ...
}

//--------------------------------
void ProgressWidget::setValue( float vValue )
{
	mValue = Mocha::clamp( vValue );
	flagDirty( );
}

//--------------------------------
float ProgressWidget::getValue( ) const
{
	return mValue;
}

//--------------------------------
void ProgressWidget::onDraw( Brush& vBrush ) const
{
	// Draw the progress bar inside the client rectangle

	if ( mValue > 0.0f )
	{
		Theme* theme = getRenderTheme( );
		if ( theme == 0 )
			return;

		Border* border = theme->getBorder( "ProgressBar" );
		if ( border )
		{
			Mocha::Rectangle client = getClientRectangle( );
			client.setWidth( mValue * client.getWidth( ) );

			border->draw( vBrush, client );
		}
	}
}

//--------------------------------
void ProgressWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Value", "float|0.1|0.0|1.0", "Value" ) );
}

//--------------------------------
Mocha::CommandResult ProgressWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setValue" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setValue( vIn[0].getAsNumber( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getValue" )
	{
		vOut.push_back( getValue( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
Mocha::String ProgressWidget::getClassName( ) const
{
	return "Progress";
}

//--------------------------------
Widget* ProgressWidget::factory( GuiManager* vManager )
{
	return new ProgressWidget( vManager );
}

}
