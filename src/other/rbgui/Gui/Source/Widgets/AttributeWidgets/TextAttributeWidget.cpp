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

#include "RBGui/Widgets/TextEntryWidget.h"

#include "RBGui/Widgets/AttributeWidgets/TextAttributeWidget.h"

namespace RBGui
{

//--------------------------------
TextAttributeWidget::TextAttributeWidget( GuiManager* vManager )
: AttributeWidget( vManager ), mMultiLine( false )
{
	mEntry = new TextEntryWidget( vManager );
	mEntry->setCallback( &TextAttributeWidget::entryChanged, this, "onFocusLost" );
	mEntry->setCallback( &TextAttributeWidget::entryChanged, this, "onReturnPressed" );

	attach( mEntry );
}

//--------------------------------
TextAttributeWidget::~TextAttributeWidget( )
{
	// ...
}

//--------------------------------
void TextAttributeWidget::entryChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	valueChanged( mEntry->getText( ) );
}

//--------------------------------
void TextAttributeWidget::setAttribute( const Mocha::Value& vValue )
{
	mEntry->setText( vValue.getAsString( ) );
}

//--------------------------------
void TextAttributeWidget::getAttribute( Mocha::Value& vValue ) const
{
	vValue.setString( mEntry->getText( ) );
}

//--------------------------------
void TextAttributeWidget::onRectangleChanged( )
{
	mEntry->setSize( getClientRectangle( ).getSize( ) );
}

//--------------------------------
void TextAttributeWidget::setOptions( const Mocha::StringList& vOptions )
{
	if ( vOptions.empty( ) == false )
	{
		if ( vOptions[0] == "multiline" )
		{
			mEntry->setMultiLine( true );
			mMultiLine = true;
		}
	}
}

//--------------------------------
float TextAttributeWidget::getAttributeHeight( ) const
{
	if ( mMultiLine == true )
		return 80.0f;

	return AttributeWidget::getAttributeHeight( );
}

//--------------------------------
AttributeWidget* TextAttributeWidget::factory( GuiManager* vManager )
{
	return new TextAttributeWidget( vManager );
}

}
