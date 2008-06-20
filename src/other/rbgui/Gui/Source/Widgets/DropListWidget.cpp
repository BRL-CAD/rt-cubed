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
#include "RBGui/Exception.h"

#include "RBGui/Widgets/TextEntryWidget.h"
#include "RBGui/Widgets/DropListWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"

#define BUTTON_SIZE 14

namespace RBGui
{

//--------------------------------
DropListWidget::DropListWidget( GuiManager* vManager )
: Widget( vManager ), mSelected( -1 )
{
	// Create text entry widget and button

	mTextEntry = new TextEntryWidget( vManager );
	mTextEntry->setCallback( &DropListWidget::textEntryPushed, this, "onMousePressed" );
	mTextEntry->setCallback( &DropListWidget::textChanged, this, "onReturnPressed" );
	mTextEntry->setCallback( &DropListWidget::textChanged, this, "onFocusLost" );
	mTextEntry->setGenerated( true );
	mTextEntry->setLocked( true );

	mDropButton = new ButtonWidget( vManager );
	mDropButton->setCallback( &DropListWidget::dropButtonPushed, this );
	mDropButton->setAnimatedImage( true );
	mDropButton->setGenerated( true );
	mDropButton->setSink( false );

	attach( mTextEntry );
	attach( mDropButton );
}

//--------------------------------
DropListWidget::~DropListWidget( )
{
	if ( mDropWindow )
		mDropWindow->close( );
}

//--------------------------------
void DropListWidget::clearEntries( )
{
	mEntries.clear( );
	mSelected = -1;

	if ( getEditable( ) == false )
		setText( "" );

	flagDirty( );
}

//--------------------------------
void DropListWidget::onTextChanged( )
{
	mTextEntry->setText( getText( ) );
}

//--------------------------------
void DropListWidget::setEditable( bool vWhich )
{
	mTextEntry->setLocked( !vWhich );
}

//--------------------------------
bool DropListWidget::getEditable( ) const
{
	return (mTextEntry->getLocked( ) == false);
}

//--------------------------------
void DropListWidget::onRectangleChanged( )
{
	// Get new client rectangle

	const Mocha::Rectangle& client = getClientRectangle( );

	// Adjust text entry

	Mocha::Rectangle r;
	r.setSize( client.getWidth( ) - BUTTON_SIZE - 1, client.getHeight( ) );
	r.setPosition( 0, 0 );

	mTextEntry->setRectangle( r );

	// Calculate position anf size of drop button

	Mocha::Rectangle rect;
	rect.setPosition( client.getWidth( ) - BUTTON_SIZE, 0.0f );
	rect.setSize( BUTTON_SIZE, client.getHeight( ) );

	mDropButton->setRectangle( rect );
}

//--------------------------------
void DropListWidget::addEntry( const Mocha::String& vText, void* vData, const Mocha::String& vTextData )
{
	mEntries.push_back( ListWidgetEntry( vText, vData, vTextData ) );
	flagDirty( );
}

//--------------------------------
void DropListWidget::setEntry( size_t vIndex, const Mocha::String& vText, void* vData, const Mocha::String& vTextData )
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	mEntries[vIndex] = ListWidgetEntry( vText, vData, vTextData );
	flagDirty( );
}

//--------------------------------
const Mocha::String& DropListWidget::getEntryText( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex].text;
}

//--------------------------------
const Mocha::String& DropListWidget::getEntryTextData( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex].textData;
}

//--------------------------------
const ListWidgetEntry& DropListWidget::getEntry( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex];
}

//--------------------------------
void DropListWidget::setSelected( const Mocha::String& vText )
{
	size_t x;
	for ( x = 0; x < mEntries.size( ); x++ )
	{
		if ( mEntries[x].text == vText )
		{
			setSelected( x );
			return;
		}
	}

	if ( getEditable( ) == false )
		setText( "" );

	mSelected = -1;
	flagDirty( );
}

//--------------------------------
void DropListWidget::setSelected( size_t vIndex )
{
	mTextEntry->setText( getEntryText( vIndex ) );
	mSelected = (int)vIndex;

	flagDirty( );
}

//--------------------------------
int DropListWidget::getSelected( ) const
{
	return mSelected;
}

//--------------------------------
void* DropListWidget::getEntryData( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex].data;
}

//--------------------------------
size_t DropListWidget::getEntryCount( ) const
{
	return mEntries.size( );
}

//--------------------------------
void DropListWidget::onSelectionMade( size_t vIndex )
{
	setSelected( vIndex );

	Mocha::ValueList v;
	v.push_back( (int)vIndex );

	doCallback( v );
}

//--------------------------------
void DropListWidget::textChanged( GuiElement& vElement, const Mocha::ValueList& vData )
{
	if ( getEditable( ) )
		setText( mTextEntry->getText( ) );
}

//--------------------------------
void DropListWidget::textEntryPushed( GuiElement& vElement, const Mocha::ValueList& vData )
{
	if ( getEditable( ) == false )
		dropButtonPushed( vElement, vData );
}

//--------------------------------
void DropListWidget::dropButtonPushed( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Calculate screen space position of window

	const Mocha::Rectangle& rect = getScreenRectangle( );
	Mocha::Vector2 pos = getWindow( )->getScreenPosition( Mocha::Vector2( rect.left, rect.top + rect.getHeight( )+1 ) );

	// Create window

	mDropWindow = getGuiManager( )->createWindow( );
	mDropWindow->setSize( Mocha::Vector2( getRectangle( ).getWidth( ), 100.0f ) );
	mDropWindow->setCallback( &DropListWidget::dropWindowFocusLost, this, "FocusLost" );
	mDropWindow->setBorderVisible( false );
	mDropWindow->setPosition( pos );
	mDropWindow->setResizeable( false );
	mDropWindow->setMovable( false );
	mDropWindow->show( );

	getGuiManager( )->setFocused( mDropWindow );

	//win->setTheme( mWindow->getTheme( ) );
	//win->setScaleX( mWindow->getScaleX( ) );
	//win->setScaleY( mWindow->getScaleY( ) );
	//win->setOrderMode( WINDOWORDER_ALWAYSONTOP );
	//win->setConstrained( true );

	// Setup the menu list

	ListWidget* list = new ListWidget( getGuiManager( ) );
	list->setCallback( &DropListWidget::entrySelected, this );
	
	Mocha::Rectangle r = mDropWindow->getClientRectangle( );
	r.setPosition( 0, 0 );

	list->setRectangle( r );

	mDropWindow->getRoot( )->addChild( list );
	
	// Add entries to the list

	size_t x;
	for ( x = 0; x < getEntryCount( ); x++ )
		list->addEntry( getEntryText( x ) );
}

//--------------------------------
void DropListWidget::entrySelected( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Update selection

	setSelected( (size_t)vData[0].getAsNumber( ) );

	// Close the window

	static_cast<Widget&>( vElement ).getWindow( )->close( );

	// Do callback

	doCallback( vData );
}

//--------------------------------
void DropListWidget::dropWindowFocusLost( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Close the drop window

	static_cast<Window&>( vElement ).close( );
}

//--------------------------------
void DropListWidget::onDraw( Brush& vBrush ) const
{
	Theme* theme = getRenderTheme( );
	if ( theme )
		mDropButton->setImage( theme->getTexture( "DropArrow" ) );
}

//--------------------------------
void DropListWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Editable", "bool", "Editable" ) );
}

//--------------------------------
Mocha::CommandResult DropListWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setEditable" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setEditable( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getEditable" )
	{
		vOut.push_back( getEditable( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
Mocha::String DropListWidget::getClassName( ) const
{
	return "DropList";
}

//--------------------------------
Widget* DropListWidget::factory( GuiManager* vManager )
{
	return new DropListWidget( vManager );
}

}
