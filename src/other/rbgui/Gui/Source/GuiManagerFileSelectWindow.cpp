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

#ifndef GUI_FILESELECTWINDOW_H
#define GUI_FILESELECTWINDOW_H

#include "Mocha/StringTools.h"

#include "RBGui/GuiManager.h"

#include "RBGui/Widgets/DirectoryListWidget.h"
#include "RBGui/Widgets/DropListWidget.h"
#include "RBGui/Widgets/TextEntryWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"
#include "RBGui/Widgets/TextWidget.h"

namespace RBGui
{

//--------------------------------
static Mocha::String lastPath = ".";

//--------------------------------
static void fileSelectCancelCallback( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Close the window

	static_cast<Widget&>( vElement ).getWindow( )->close( );
}

//--------------------------------
static void filterChangedCallback( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Get list

	DirectoryListWidget* fileList = static_cast<DirectoryListWidget*>( static_cast<Widget&>( vElement ).getWindow( )->findWidget( "FileList" ) );

	// Change filter

	fileList->setFilter( static_cast<DropListWidget&>( vElement ).getEntryTextData( static_cast<DropListWidget&>( vElement ).getSelected( ) ) );
}

//--------------------------------
static void fileSelectFileSelectedCallback( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Get window

	Window* win = static_cast<Widget&>( vElement ).getWindow( );

	// Get full path of file

	Mocha::String filename = Mocha::TrimString( win->findWidget( "FileEntry" )->getText( ) );
	if ( filename == "" )
		return;

	Mocha::String fullPath = static_cast<DirectoryListWidget*>( win->findWidget( "FileList" ) )->getFullPath( filename );

	// Append extension if necessary

	if ( win->getName( ) == "SAVE" )
	{
		Mocha::String ext = Mocha::GetStringFileExtension( fullPath );
		if ( ext == "" )
		{
			DropListWidget* filters = static_cast<DropListWidget*>( win->findWidget( "FilterList" ) );
			if ( filters->getSelected( ) != -1 )
			{
				ext = filters->getEntryTextData( filters->getSelected( ) );
				if ( ext != "" )
					fullPath += "." + ext;
			}
		}
	}

	// Do callback

	GuiCallback* cb = static_cast<GuiCallback*>( win->getObject( ) );
	if ( cb )
	{
		Mocha::ValueList v;
		v.push_back( fullPath );

		cb->onGuiEvent( *win, v );
	}

	// Save the last path

	lastPath = static_cast<DirectoryListWidget*>( win->findWidget( "FileList" ) )->getPath( );

	// Close the window

	win->close( );
}

//--------------------------------
static void fileSelectFileClickedCallback( GuiElement& vElement, const Mocha::ValueList& vData )
{
	static_cast<Widget&>( vElement ).getWindow( )->findWidget( "FileEntry" )->setText( vData[0].getString( ) );
}

//--------------------------------
Window* GuiManager::createFileSelectWindow( const Mocha::String& vTitle, const Mocha::String& vPath, const Mocha::String& vFilter, GuiCallback* vCallback, FileSelectWindowType vType )
{
	Mocha::RefPointer<Window> win = createWindow( );
	win->setSize( Mocha::Vector2( 480.0f, 320.0f ) );
	win->setResizeable( false );
	win->setObject( vCallback );
	win->setText( vTitle );
	win->setModal( true );
	win->centerX( );
	win->centerY( );

	const float padding = 3.0f;

	Mocha::Rectangle client = win->getClientRectangle( );
	client.shrink( padding );

	Mocha::RefPointer<TextEntryWidget> textEntry = static_cast<TextEntryWidget*>( win->createWidget( "TextEntry" ) );
	textEntry->setRectangle( 60.0f, padding + client.getHeight( ) - 42.0f, client.getWidth( ) - 122.0f, 20.0f );
	textEntry->setCallback( &fileSelectFileSelectedCallback, "onReturnPressed" );
	textEntry->setName( "FileEntry" );

	Mocha::RefPointer<DropListWidget> filterList = static_cast<DropListWidget*>( win->createWidget( "DropList" ) );
	filterList->setRectangle( 60.0f, padding + client.getHeight( ) - 20.0f, client.getWidth( ) - 122.0f, 20.0f );
	filterList->setCallback( &filterChangedCallback );
	filterList->setName( "FilterList" );

	Mocha::RefPointer<DirectoryListWidget> fileList = static_cast<DirectoryListWidget*>( win->createWidget( "DirectoryList" ) );
	fileList->setRectangle( padding, padding, client.getWidth( ), client.getHeight( ) - 44.0f - 1.0f );
	fileList->setCallback( &fileSelectFileClickedCallback, "onFileClicked" );
	fileList->setCallback( &fileSelectFileSelectedCallback, "onFileSelected" );
	fileList->setName( "FileList" );
	fileList->setPath( ( vPath != "" ) ? vPath : lastPath );

	Mocha::RefPointer<ButtonWidget> selectButton = static_cast<ButtonWidget*>( win->createWidget( "Button" ) );
	selectButton->setRectangle( client.getWidth( ) - 60.0f, padding + client.getHeight( ) - 42.0f, 63.0f, 20.0f );
	selectButton->setCallback( &fileSelectFileSelectedCallback );
	selectButton->setText( "Select" );

	Mocha::RefPointer<ButtonWidget> cancelButton = static_cast<ButtonWidget*>( win->createWidget( "Button" ) );
	cancelButton->setRectangle( client.getWidth( ) - 60.0f, padding + client.getHeight( ) - 20.0f, 63.0f, 20.0f );
	cancelButton->setCallback( &fileSelectCancelCallback );
	cancelButton->setText( "Cancel" );

	// Create text widgets

	Mocha::RefPointer<TextWidget> fileNameLabel = static_cast<TextWidget*>( win->createWidget( "Text" ) );
	fileNameLabel->setRectangle( padding, padding + client.getHeight( ) - 42.0f, 60.0f, 20.0f );
	fileNameLabel->setText( "Filename:" );

	Mocha::RefPointer<TextWidget> filterLabel = static_cast<TextWidget*>( win->createWidget( "Text" ) );
	filterLabel->setRectangle( padding, padding + client.getHeight( ) - 20.0f, 60.0f, 20.0f );
	filterLabel->setText( "Filter:" );

	// Populate filter list

	Mocha::StringList filters = Mocha::SplitString( vFilter, ";" );
	if ( filters.size( ) == 0 )
		filters.push_back( "*" );

	Mocha::StringList::iterator it;
	for ( it = filters.begin( ); it != filters.end( ); it++ )
		filterList->addEntry( "*." + (*it), 0, (*it) );

	fileList->setFilter( filters[0] );
	filterList->setSelected( 0 );

	// Set selection to file name entry

	win->setFocused( textEntry );

	// Return pointer to new window

	win->setName( ( vType == FILESELECTWINDOW_OPEN ) ? "OPEN" : "SAVE" );
	return win;
}

}

#endif
