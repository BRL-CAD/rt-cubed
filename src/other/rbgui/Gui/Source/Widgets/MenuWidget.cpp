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

#include "Mocha/StringTools.h"
#include "RBGui/Widgets/MenuWidget.h"
#include "RBGui/Widgets/MenuEntryWidget.h"

namespace RBGui
{

//--------------------------------------------
MenuWidget::MenuWidget( GuiManager* vManager )
: Widget( vManager )
{
	// ...
}

//--------------------------------------------
MenuWidget::~MenuWidget( )
{
	// ...
}

//--------------------------------------------
void MenuWidget::deselectAll( )
{
	const WidgetList& children = getChildren( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{
		MenuEntryWidget* menu = dynamic_cast<MenuEntryWidget*>( (*it).get( ) );
		if ( menu )
			menu->setSelected( false );
	}
}

//--------------------------------------------
void MenuWidget::adjustSize( )
{
	// ...
}

//--------------------------------------------
void MenuWidget::onRectangleChanged( )
{
	adjustSize( );
	updateMenus( );
}

//--------------------------------------------
void MenuWidget::updateMenus( )
{
	const float xpadding = 2.0f;
	float xpos = 0.0f;

	const WidgetList& children = getChildren( );
	const Mocha::Rectangle& rect = getClientRectangle( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{
		// Try to get the child as a menu widget

		MenuEntryWidget* w = dynamic_cast<MenuEntryWidget*>( (*it).get( ) );
		if ( w == 0 )
			continue;

		// Tile menu widgets across the bar

		Mocha::Rectangle r = w->getRectangle( );
		r.setHeight( rect.getHeight( ) );
		r.setPosition( xpos, 0.0f );

		w->setRectangle( r );

		float wi = r.getWidth( );
		xpos += r.getWidth( ) + xpadding;
	}
}

//--------------------------------------------
MenuEntry* MenuWidget::getEntry( const Mocha::String& vName, Mocha::String& vRootName )
{
	// Make sure we have a valid string

	if ( vName == "" )
		return 0;

	// Split string into tokens

	const Mocha::StringList tokens = Mocha::SplitString( vName, "." );
	if ( tokens.size( ) > 0 )
		vRootName = tokens[0];

	// Find entry, adding entries along the way

	Mocha::String fullname;
	MenuEntry* res = &mRoot;

	Mocha::StringList::const_iterator it;
	for ( it = tokens.begin( ); it != tokens.end( ); it++ )
	{
		fullname += (*it);

		res = &res->getEntry( (*it) );
		res->setName( fullname );
		res->setText( (*it) );

		fullname += ".";
	}

	return res;
}

//--------------------------------------------
void MenuWidget::addEntry( const Mocha::String& vName, const Mocha::String& vID )
{
	// Get entry in map

	Mocha::String rootName;
	MenuEntry* entry = getEntry( vName, rootName );

	if ( entry == 0 )
		return;

	// Store ID of entry

	entry->setID( vID );

	// Make sure we create a root widget

	if ( findChild( rootName ) != 0 )
		return;

	// Add widget

	MenuEntryWidget* menu = new MenuEntryWidget( getGuiManager( ), this );
	attach( menu );

	// Set text and name

	menu->setText( rootName );
	menu->setName( rootName );

	// Re-organize the menus

	updateMenus( );
	flagDirty( );
}

//--------------------------------------------
void MenuWidget::entrySelected( const Mocha::String& vName )
{
	Mocha::ValueList v;
	v.push_back( vName );

	doCallback( v );
}

//--------------------------------------------
void MenuWidget::onDraw( Brush& vBrush ) const
{
	// ...
}

//--------------------------------------------
Mocha::CommandResult MenuWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "addEntry" )
	{
		if ( vIn.size( ) <= 0 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		Mocha::ValueList::const_iterator it;
		for ( it = vIn.begin( ); it != vIn.end( ); it++ )
		{
			Mocha::StringList parts = Mocha::SplitString( (*it).getAsString( ), ";" );
			if ( parts.size( ) > 1 )
				addEntry( parts[0], parts[1] );
			else
				return Mocha::CMDRESULT_BADARGUMENTS;
		}

		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------------------
void MenuWidget::clear( )
{
	clearChildren( );
	mRoot.clear( );
}

//--------------------------------------------
Mocha::String MenuWidget::getClassName( ) const
{
	return "Menu";
}

//--------------------------------------------
Widget* MenuWidget::factory( GuiManager* vManager )
{
	return new MenuWidget( vManager );
}

}
