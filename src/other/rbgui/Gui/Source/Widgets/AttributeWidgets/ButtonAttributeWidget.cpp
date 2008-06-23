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

#include "RBGui/Widgets/ButtonWidget.h"

#include "RBGui/Widgets/AttributeWidgets/ButtonAttributeWidget.h"

namespace RBGui
{

//--------------------------------
ButtonAttributeWidget::ButtonAttributeWidget( GuiManager* vManager )
: AttributeWidget( vManager )
{
	mButton = new ButtonWidget( vManager );
	mButton->setCallback( &ButtonAttributeWidget::buttonPressed, this );

	attach( mButton );
}

//--------------------------------
ButtonAttributeWidget::~ButtonAttributeWidget( )
{
	// ...
}

//--------------------------------
void ButtonAttributeWidget::buttonPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	valueChanged( Mocha::Value( ) );
}

//--------------------------------
void ButtonAttributeWidget::onRectangleChanged( )
{
	mButton->setSize( getClientRectangle( ).getSize( ) );
}

//--------------------------------
void ButtonAttributeWidget::setAttribute( const Mocha::Value& vValue )
{
	// ...
}

//--------------------------------
void ButtonAttributeWidget::setOptions( const Mocha::StringList& vOptions )
{
	// ...
}

//--------------------------------
void ButtonAttributeWidget::setTitle( const Mocha::String& vTitle ) const
{
	mButton->setText( vTitle );
}

//--------------------------------
bool ButtonAttributeWidget::showTitle( ) const
{
	return false;
}

//--------------------------------
AttributeWidget* ButtonAttributeWidget::factory( GuiManager* vManager )
{
	return new ButtonAttributeWidget( vManager );
}

}