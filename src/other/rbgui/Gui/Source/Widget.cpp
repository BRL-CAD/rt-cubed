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

#include "RBGui/Exception.h"
#include "RBGui/Widget.h"
#include "RBGui/Window.h"
#include "RBGui/Brush.h"
#include "RBGui/Core.h"

namespace RBGui
{

//--------------------------------
Widget::Widget( GuiManager* vManager )
: mWindow( 0 ), mEnabled( true ), mColor( Mocha::Color::Transparent ), mParent( 0 ), mVisible( true ), mScrollable( true ), mBorderVisible( true ), mBorderState( "default" ), mManager( vManager ), mGenerated( false )
{
	// ...
}

//--------------------------------
Widget::~Widget( )
{
	// ...
}

//--------------------------------
void Widget::setEnabled( bool vWhich )
{
	mEnabled = vWhich;
	flagDirty( );
}

//--------------------------------
bool Widget::getEnabled( ) const
{
	// A child is always disabled if the parent is disabled

	if ( mParent && (mParent->getEnabled( ) == false) )
		return false;

	// Return own enabled flag

	return mEnabled;
}

//--------------------------------
bool Widget::getContainer( ) const
{
	return false;
}

//--------------------------------
void Widget::setScrollable( bool vWhich )
{
	mScrollable = vWhich;
}

//--------------------------------
bool Widget::getScrollable( ) const
{
	return mScrollable;
}

//--------------------------------
void Widget::setGenerated( bool vWhich )
{
	mGenerated = vWhich;
}

//--------------------------------
bool Widget::getGenerated( ) const
{
	return mGenerated;
}

//--------------------------------
CursorType Widget::getCursor( ) const
{
	return CURSOR_DEFAULT;
}

//--------------------------------
bool Widget::getLocalPointInside( const Mocha::Vector2& vPoint ) const
{
	const Mocha::Rectangle& screen = getScreenRectangle( );
	const Mocha::Rectangle& client = getClientRectangle( );

	return screen.pointInside( vPoint + client.getPosition( ) );
}

//--------------------------------
void Widget::setBorderVisible( bool vWhich )
{
	mBorderVisible = vWhich;
	updateScreenRect( );
}

//--------------------------------
Mocha::Color Widget::getDerivedColor( const Mocha::Color& vColor ) const
{
	return ( getEnabled( ) ? vColor : vColor * Mocha::Color( 1.0f, 1.0f, 1.0f, 0.5f ) );
}

//--------------------------------
void Widget::clearChildren( )
{
	WidgetList::iterator it = mChildren.begin( );
	while ( it != mChildren.end( ) )
	{
		Widget* w = (*it);
		if ( w->getGenerated( ) == false )
		{
			w->setParent( 0 );
			it = mChildren.erase( it );
		}
		else
			it++;
	}
}

//--------------------------------
bool Widget::getBorderVisible( ) const
{
	return mBorderVisible;
}

//--------------------------------
const Mocha::String& Widget::getBorderState( )
{
	return mBorderState;
}

//--------------------------------
void Widget::setBorder( const Mocha::String& vName )
{
	mBorderName = vName;
	updateScreenRect( );
}

//--------------------------------
const Mocha::String& Widget::getBorder( ) const
{
	return mBorderName;
}

//--------------------------------
Border* Widget::getRenderBorder( ) const
{
	// Get theme

	Theme* theme = getRenderTheme( );
	if ( theme == 0 )
		return 0;

	// First try custom border

	if ( mBorderName != "" )
		return theme->getBorder( mBorderName );

	// Try default theme border

	return theme->getBorder( getClassName( ) );
}

//--------------------------------
Font* Widget::getRenderFont( ) const
{
	// Try custom font

	//if ( mFont )
	//	return mFont;

	// Try default theme font

	Theme* tmp = getRenderTheme( );
	if ( tmp )
	{
		// Try font name

		if ( mFontName != "" )
		{
			Font* f = tmp->getFont( mFontName );
			if ( f )
				return f;
		}

		// Try default font

		return tmp->getFont( getClassName( ) );
	}

	// No font!

	return 0;
}

//--------------------------------
Mocha::Color Widget::getRenderColor( ) const
{
	// First try custom color

	if ( mColor.a > 0.0f )
		return mColor;

	// Try default theme color

	Theme* tmp = getRenderTheme( );
	if ( tmp )
		return tmp->getColor( getClassName( ), Mocha::Color::Black );

	// No color, just use black

	return Mocha::Color::Black;
}

//--------------------------------
Theme* Widget::getRenderTheme( ) const
{
	// For now just return default theme

	return Core::Get( ).getThemeManager( ).getDefaultTheme( );
}

//--------------------------------
void Widget::setFont( const Mocha::String& vFont )
{
	mFontName = vFont;
}

//--------------------------------
const Mocha::String& Widget::getFont( ) const
{
	return mFontName;
}

//--------------------------------
Widget* Widget::findWidgetAtPoint( const Mocha::Vector2& vPoint ) const
{
	if ( mVisible && mScreenRect.pointInside( vPoint ) )
	{
		// Search children

		WidgetList::const_reverse_iterator it;
		for ( it = mChildren.rbegin( ); it != mChildren.rend( ); it++ )
		{
			Widget* w = (*it)->findWidgetAtPoint( vPoint );
			if ( w )
				return w;
		}

		// Return self

		return (Widget*)this;
	}

	// No match!

	return 0;
}

//--------------------------------
Widget* Widget::findWidget( const Mocha::String& vName ) const
{
	WidgetList::const_iterator it;
	for ( it = mChildren.begin( ); it != mChildren.end( ); it++ )
	{
		Widget* w = (*it)->findWidget( vName );
		if ( w )
			return w;
	}

	return (Widget*)(( mName == vName ) ? this : 0);
}

//--------------------------------
Widget* Widget::findChild( const Mocha::String& vName ) const
{
	WidgetList::const_iterator it;
	for ( it = mChildren.begin( ); it != mChildren.end( ); it++ )
	{
		Widget* w = (*it);
		if ( w->getName( ) == vName )
			return w;
	}

	return 0;
}

//--------------------------------
void Widget::flagDirty( )
{
	if ( mWindow )
		mWindow->flagDirty( );
}

//--------------------------------
void Widget::setParent( Widget* vWidget )
{
	// Set new parent and window

	mParent = vWidget;
	if ( mParent )
		mWindow = mParent->mWindow;
	else
		mWindow = 0;

	// Update children (To make sure window pointers are updated)

	WidgetList::const_iterator it;
	for ( it = mChildren.begin( ); it != mChildren.end( ); it++ )
		(*it)->setParent( this );

	// Update screen rectangle

	updateScreenRect( );
}

//--------------------------------
void Widget::attach( Widget* vWidget )
{
	// Make sure widget is not already attached to something

	if ( vWidget->mParent )
		return;

	// Add widget as child

	mChildren.push_back( vWidget );
	vWidget->setParent( this );

	// Redraw

	flagDirty( );
}

//--------------------------------
void Widget::detach( Widget* vWidget )
{
	// Find widget

	WidgetList::iterator it = std::find( mChildren.begin( ), mChildren.end( ), vWidget );
	if ( it == mChildren.end( ) )
		return;

	// Remove from list

	vWidget->setParent( 0 );
	mChildren.erase( it );

	// Redraw

	flagDirty( );
}

//--------------------------------
void Widget::setName( const Mocha::String& vName )
{
	mName = vName;
}

//--------------------------------
const Mocha::String& Widget::getName( ) const
{
	return mName;
}

//--------------------------------
void Widget::setText( const Mocha::String& vText )
{
	mText = vText;
	onTextChanged( );
	flagDirty( );
}

//--------------------------------
const Mocha::String& Widget::getText( ) const
{
	return mText;
}

//--------------------------------
void Widget::setScroll( const Mocha::Vector2& vScroll )
{
	mScroll = vScroll;
	updateScreenRect( );
}

//--------------------------------
const Mocha::Vector2& Widget::getScroll( ) const
{
	return mScroll;
}

//--------------------------------
void Widget::setColor( const Mocha::Color& vColor )
{
	mColor = vColor;
	onColorChanged( );

	flagDirty( );
}

//--------------------------------
const Mocha::Color& Widget::getColor( ) const
{
	return mColor;
}

//--------------------------------
void Widget::updateScreenRect( )
{
	// Update screen rectangle by offsetting from parent

	if ( mParent )
	{
		mScreenRect = mRectangle;
		mScreenRect.translate( mParent->getClientRectangle( ).getPosition( ) );

		if ( mScrollable )
			mScreenRect.translate( mParent->getScroll( ) );
	}
	else
		mScreenRect = mRectangle;

	// Calculate client rect

	mClientRect = mScreenRect;

	if ( mBorderVisible )
	{
		Border* border = getRenderBorder( );
		if ( border )
			mClientRect += border->getClientAdjust( );
	}

	// Update children

	WidgetList::const_iterator it;
	for ( it = mChildren.begin( ); it != mChildren.end( ); it++ )
		(*it)->updateScreenRect( );

	// Force redraw

	flagDirty( );

	// Notify widget that rectangle changed

	onRectangleChanged( );
}

//--------------------------------
void Widget::setPosition( const Mocha::Vector2& vPosition )
{
	mRectangle.setPosition( vPosition );
	updateScreenRect( );
}

//--------------------------------
Mocha::Vector2 Widget::getPosition( ) const
{
	return mRectangle.getPosition( );
}

//--------------------------------
void Widget::setSize( const Mocha::Vector2& vSize )
{
	mRectangle.setSize( vSize );
	updateScreenRect( );
}

//--------------------------------
Mocha::Vector2 Widget::getSize( ) const
{
	return mRectangle.getSize( );
}

//--------------------------------
void Widget::setRectangle( float vX, float vY, float vWidth, float vHeight )
{
	Mocha::Rectangle r;
	r.setPosition( vX, vY );
	r.setSize( vWidth, vHeight );

	setRectangle( r );
}

//--------------------------------
void Widget::setRectangle( const Mocha::Rectangle& vRectangle )
{
	mRectangle = vRectangle;
	updateScreenRect( );
}

//--------------------------------
const Mocha::Rectangle& Widget::getRectangle( ) const
{
	return mRectangle;
}

//--------------------------------
const Mocha::Rectangle& Widget::getScreenRectangle( ) const
{
	return mScreenRect;
}

//--------------------------------
const Mocha::Rectangle& Widget::getClientRectangle( ) const
{
	return mClientRect;
}

//--------------------------------
Window* Widget::getWindow( ) const
{
	return mWindow;
}

//--------------------------------
Widget* Widget::getParent( ) const
{
	return mParent;
}

//--------------------------------
void Widget::setVisible( bool vWhich )
{
	mVisible = vWhich;
	flagDirty( );
}

//--------------------------------
bool Widget::getVisible( ) const
{
	return mVisible;
}

//--------------------------------
void Widget::setBorderState( const Mocha::String& vName )
{
	mBorderState = vName;
	flagDirty( );
}

//--------------------------------
void Widget::onDraw( Brush& vBrush ) const
{
	// ...
}

//--------------------------------
void Widget::onRectangleChanged( )
{
	// ...
}

//--------------------------------
void Widget::onTextChanged( )
{
	// ...
}

//--------------------------------
void Widget::onColorChanged( )
{
	// ...
}

//--------------------------------
void Widget::onDoubleClick( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	// ...
}

//--------------------------------
void Widget::onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	// ...
}

//--------------------------------
void Widget::onMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	// ...
}

//--------------------------------
void Widget::onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	// ...
}

//--------------------------------
void Widget::onMouseScrolled( float vAmount )
{
	// ...
}

//--------------------------------
void Widget::onKeyPressed( KeyID vKeyID )
{
	// ...
}

//--------------------------------
void Widget::onKeyReleased( KeyID vKeyID )
{
	// ...
}

//--------------------------------
void Widget::onFocusRecieved( )
{
	// ...
}

//--------------------------------
void Widget::onFocusLost( )
{
	// ...
}

//--------------------------------
void Widget::onMouseEnter( const Mocha::Vector2& vPoint )
{
	// ...
}

//--------------------------------
void Widget::onMouseLeave( )
{
	// ...
}

//--------------------------------
void Widget::handleDoubleClick( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	Mocha::ValueList v;
	v.push_back( (int)vID );
	v.push_back( vPoint );

	doCallback( v, "onDoubleClick" );
	onDoubleClick( vID, vPoint );
}

//--------------------------------
void Widget::handleMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	Mocha::ValueList v;
	v.push_back( (int)vID );
	v.push_back( vPoint );

	doCallback( v, "onMousePressed" );
	onMousePressed( vID, vPoint );
}

//--------------------------------
void Widget::handleMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	Mocha::ValueList v;
	v.push_back( (int)vID );
	v.push_back( vPoint );

	doCallback( v, "onMouseReleased" );
	onMouseReleased( vID, vPoint );
}

//--------------------------------
void Widget::handleMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	Mocha::ValueList v;
	v.push_back( vRelative );
	v.push_back( vPoint );

	doCallback( v, "onMouseMotion" );
	onMouseMotion( vRelative, vPoint );
}

//--------------------------------
void Widget::handleMouseScrolled( float vAmount )
{
	Mocha::ValueList v;
	v.push_back( vAmount );

	doCallback( v, "onMouseScrolled" );
	onMouseScrolled( vAmount );
}

//--------------------------------
void Widget::handleKeyPressed( KeyID vKeyID )
{
	Mocha::ValueList v;
	v.push_back( (int)vKeyID );

	doCallback( v, "onKeyPressed" );
	onKeyPressed( vKeyID );
}

//--------------------------------
void Widget::handleKeyReleased( KeyID vKeyID )
{
	Mocha::ValueList v;
	v.push_back( (int)vKeyID );

	doCallback( v, "onKeyReleased" );
	onKeyReleased( vKeyID );
}

//--------------------------------
void Widget::handleFocusRecieved( )
{
	doCallback( "onFocusRecieved" );
	onFocusRecieved( );
}

//--------------------------------
void Widget::handleFocusLost( )
{
	doCallback( "onFocusLost" );
	onFocusLost( );
}

//--------------------------------
void Widget::handleMouseEnter( const Mocha::Vector2& vPoint )
{
	Mocha::ValueList v;
	v.push_back( vPoint );

	doCallback( v, "onMouseEnter" );
	onMouseEnter( vPoint );
}

//--------------------------------
void Widget::handleMouseLeave( )
{
	doCallback( "onMouseLeave" );
	onMouseLeave( );
}

//--------------------------------
void Widget::draw( Brush& vBrush ) const
{
	// Are we even visible?

	if ( mVisible == false )
		return;

	// Get current clipping region

	Mocha::Rectangle region = vBrush.getClipRegion( );

	// See if this widget is visible within current clip region

	if ( region.intersect( mScreenRect ).isZero( ) )
		return;

	// Get border

	Border* border = getRenderBorder( );

	// Draw border if necessary

	if ( border && mBorderVisible )
	{
		vBrush.setBlendMode( BRUSHBLEND_ALPHA );
		border->draw( vBrush, mScreenRect, true, false, false, mBorderState );
	}

	// Set new clip region

	vBrush.setClipRegion( region.intersect( mClientRect ) );

	// Draw widget contents

	onDraw( vBrush );

	// Draw children

	WidgetList::const_iterator it;
	for ( it = mChildren.begin( ); it != mChildren.end( ); it++ )
		(*it)->draw( vBrush );

	// Return old clip region

	vBrush.setClipRegion( region );
}

//--------------------------------
const WidgetList& Widget::getChildren( ) const
{
	return mChildren;
}

//--------------------------------
GuiManager* Widget::getGuiManager( ) const
{
	return mManager;
}

//--------------------------------
Mocha::CommandResult Widget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setText" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setText( vIn[0].getAsString( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getText" )
	{
		vOut.push_back( getText( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setColor" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setColor( vIn[0].getAsColor( ) );
		return Mocha::CMDRESULT_SUCCESS;		
	}
	else if ( vName == "getColor" )
	{
		vOut.push_back( getColor( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setBorderVisible" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setBorderVisible( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;	
	}
	else if ( vName == "getBorderVisible" )
	{
		vOut.push_back( getBorderVisible( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setRectangle" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setRectangle( vIn[0].getAsRectangle( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getRectangle" )
	{
		vOut.push_back( getRectangle( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setPosition" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setPosition( vIn[0].getAsVector2( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getPosition" )
	{
		vOut.push_back( getPosition( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setSize" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setPosition( vIn[0].getAsVector2( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getSize" )
	{
		vOut.push_back( getSize( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Mocha::CMDRESULT_INVALIDCOMMAND;
}

//--------------------------------
void Widget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	vOut.push_back( Mocha::ObjectValueEntry( "Size", "vector2", "Size" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Position", "vector2", "Position" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "BorderVisible", "bool", "Border Visible" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Border", "text", "Border Name" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Mocha::Color", "color", "Mocha::Color" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Text", "text", "Text" ) );
}

//--------------------------------
void Widget::save( Mocha::DataSection& vSection ) const
{
	Mocha::ObjectValueEntryList vals;
	getValueList( vals );

	Mocha::ObjectValueEntryList::const_iterator it;
	for ( it = vals.begin( ); it != vals.end( ); it++ )
	{
		const Mocha::ObjectValueEntry& entry = (*it);
		if ( entry.persistant )
		{
			// Get the value and save it to the data section as a string

			Mocha::Value out;
			if ( getValue( entry.name, out ) == Mocha::CMDRESULT_SUCCESS )
				vSection.addComponent( entry.name, out.getAsString( ) );
		}
	}

	// Save children if this is a container

	if ( getContainer( ) )
	{
		WidgetList::const_iterator it;
		for ( it = mChildren.begin( ); it != mChildren.end( ); it++ )
		{
			Widget* w = (*it);
			if ( w->getGenerated( ) == false )
			{
				// Setup new section

				Mocha::DataSection section;
				section.setType( "widget" );
				section.addParam( "\"" + w->getClassName( ) + "\"" );

				// Save widget to section

				w->save( section );
				
				// Add to own section

				vSection.addSection( section );
			}
		}
	}
}

//--------------------------------
void Widget::load( const Mocha::DataSection& vSection )
{
	size_t x;

	// Read any values

	for ( x = 0; x < vSection.getComponentCount( ); x++ )
	{
		const Mocha::DataComponent& comp = vSection.getComponent( x );
		if ( comp.getParamCount( ) > 0 )
		{
			const Mocha::String& name = comp.getName( );
			setValue( name, comp.getParam( 0 ) );
		}
	}

	// Read any widgets

	if ( getContainer( ) )
	{
		for ( x = 0; x < vSection.getSectionCount( ); x++ )
		{
			const Mocha::DataSection& section = vSection.getSection( x );
			if ( section.getParamCount( ) > 0 )
			{
				const Mocha::String& name = section.getParam( 0 );
				if ( name == "widget" )
				{
					if ( section.getParamCount( ) != 2 )
						throw Exception( "Invalid parent count in 'widget' tag (usage: begin widget type)" );

					Mocha::RefPointer<Widget> w = getGuiManager( )->createWidget( section.getParam( 1 ) );
					w->load( section );

					attach( w );
				}
				else
					throw Exception( "Invalid section type: '" + name + "'" );
			}
		}
	}
}

//--------------------------------
Mocha::String Widget::getClassName( ) const
{
	return "Widget";
}

}
