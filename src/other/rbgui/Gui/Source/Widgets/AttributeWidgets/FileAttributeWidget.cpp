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

#include "RBGui/Widgets/AttributeWidgets/FileAttributeWidget.h"
#include "RBGui/Widgets/TextEntryWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"

namespace RBGui
{

//--------------------------------
FileAttributeWidget::FileAttributeWidget( GuiManager* vManager )
: AttributeWidget( vManager )
{
	// Create text entry field

	mEntry = new TextEntryWidget( vManager );
	mEntry->setCallback( &FileAttributeWidget::entryChanged, this, "onFocusLost" );
	mEntry->setCallback( &FileAttributeWidget::entryChanged, this, "onReturnPressed" );

	// Create file open button

	mButton = new ButtonWidget( vManager );
	mButton->setCallback( &FileAttributeWidget::buttonPressed, this );
	mButton->setText( "..." );

	attach( mButton );
	attach( mEntry );
}

//--------------------------------
FileAttributeWidget::~FileAttributeWidget( )
{
	// ...
}

//--------------------------------
void FileAttributeWidget::onRectangleChanged( )
{
	const Mocha::Rectangle& r = getClientRectangle( );

	mEntry->setRectangle( 0.0f, 0.0f, r.getWidth( ) - 21, r.getHeight( ) );
	mButton->setRectangle( r.getWidth( ) - 20, 0.0f, 20, r.getHeight( ) );
}

//--------------------------------
void FileAttributeWidget::buttonPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	// Open the file select window

	getGuiManager( )->createFileSelectWindow( "Select File", "", mFilter, new MemberGuiCallback<FileAttributeWidget>( &FileAttributeWidget::fileSelected, this ), FILESELECTWINDOW_OPEN )->show( );
}

//--------------------------------
void FileAttributeWidget::entryChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	valueChanged( mEntry->getText( ) );
}

//--------------------------------
void FileAttributeWidget::fileSelected( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	mEntry->setText( vValues[0].getString( ) );
	valueChanged( mEntry->getText( ) );
}

//--------------------------------
void FileAttributeWidget::setAttribute( const Mocha::Value& vValue )
{
	mEntry->setText( vValue.getAsString( ) );
}

//--------------------------------
void FileAttributeWidget::getAttribute( Mocha::Value& vValue ) const
{
	vValue.setString( mEntry->getText( ) );
}

//--------------------------------
void FileAttributeWidget::setOptions( const Mocha::StringList& vOptions )
{
	if ( vOptions.size( ) > 0 )
		mFilter = vOptions[0];
}

//--------------------------------
float FileAttributeWidget::getAttributeHeight( ) const
{
	return 20.0f;
}

//--------------------------------
AttributeWidget* FileAttributeWidget::factory( GuiManager* vManager )
{
	return new FileAttributeWidget( vManager );
}

}
