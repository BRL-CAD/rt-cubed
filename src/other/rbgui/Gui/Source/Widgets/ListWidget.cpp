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
#include "RBGui/InputDefines.h"
#include "RBGui/GuiManager.h"
#include "Mocha/DataSection.h"

#include "RBGui/Widgets/ListWidget.h"
#include "RBGui/Widgets/ScrollWidget.h"

#define ICON_SIZE 16

namespace RBGui
{

//--------------------------------
ListWidget::ListWidget( GuiManager* vManager )
: Widget( vManager ), mMultiSelect( false ), mDrawIcons( false ), mSelected( -1 )
{
	// Setup the scroll bar

	mScrollBar = new ScrollWidget( vManager );
	//mScrollBar->setGenerated( true );

	attach( mScrollBar );
}

//--------------------------------
ListWidget::~ListWidget( )
{
	// ...
}

//--------------------------------
void ListWidget::setDrawIcons( bool vWhich )
{
	mDrawIcons = vWhich;
	flagDirty( );
}

//--------------------------------
int ListWidget::getSelected( ) const
{
	return mSelected;
}

//--------------------------------
bool ListWidget::getDrawIcons( ) const
{
	return mDrawIcons;
}

//--------------------------------
void ListWidget::clearEntries( )
{
	mEntries.clear( );
	mSelected = -1;
}

//--------------------------------------------
void ListWidget::onSelected( int vIndex )
{
	Mocha::ValueList v;
	v.push_back( vIndex );

	doCallback( v );
}

//--------------------------------
void ListWidget::onUnselected( int vIndex )
{
	Mocha::ValueList v;
	v.push_back( vIndex );

	doCallback( v );
}

//--------------------------------
void ListWidget::setScrollVisible( bool vWhich )
{
	// ...
}

//--------------------------------
bool ListWidget::getScrollVisible( ) const
{
	return false;
}

//--------------------------------
void ListWidget::onRectangleChanged( )
{
	// Get new client rectangle

	const Mocha::Rectangle& rect = getClientRectangle( );

	// Adjust size and position of scrollbar

	float w = getRenderTheme( )->getFloat( "ScrollWidth", 14.0f );

	Mocha::Rectangle r;
	r.setPosition( rect.getWidth( ) - w, 0.0f );
	r.setSize( w, rect.getHeight( ) );

	mScrollBar->setRectangle( r );
	adjustScrollBarSteps( );
}

//--------------------------------
void ListWidget::setMultiSelect( bool vWhich )
{
	mMultiSelect = vWhich;
}

//--------------------------------
bool ListWidget::getMultiSelect( ) const
{
	return mMultiSelect;
}

//--------------------------------
void ListWidget::removeEntry( size_t vIndex )
{
	if ( vIndex >= getEntryCount( ) )
		return;

	mEntries.erase( mEntries.begin( ) + vIndex );
	adjustScrollBarSteps();
    flagDirty( );
}

//--------------------------------
void ListWidget::swapEntryOrder( size_t vIndex1, size_t vIndex2 )
{
	if ( vIndex1 >= getEntryCount( ) )
		return;

	if ( vIndex2 >= getEntryCount( ) )
		return;

    ListWidgetEntry temp = mEntries[vIndex1];
	mEntries[vIndex1] = mEntries[vIndex2];
	mEntries[vIndex2] = temp;

	if( vIndex1 == mSelected )
	{
		mSelected = vIndex2;
	}
	else if( vIndex2 == mSelected )
	{
		mSelected = vIndex2;
	}


	flagDirty();
}

//--------------------------------
void ListWidget::addEntry( const Mocha::String& vText, void* vData, const Mocha::String& vTextData, const Mocha::String& vIcon )
{
	mEntries.push_back( ListWidgetEntry( vText, vData, vTextData, vIcon ) );
	adjustScrollBarSteps( );
	flagDirty( );
}

//--------------------------------
void ListWidget::setEntry( size_t vIndex, const Mocha::String& vText, void* vData, const Mocha::String& vTextData, const Mocha::String& vIcon )
{
	if ( vIndex >= getEntryCount( ) )
		return;

	mEntries[vIndex] = ListWidgetEntry( vText, vData, vTextData, vIcon );
	flagDirty( );
}

//--------------------------------
const Mocha::String& ListWidget::getEntryText( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex].text;
}

//--------------------------------
const Mocha::String& ListWidget::getEntryTextData( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex].textData;
}

//--------------------------------
void* ListWidget::getEntryData( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex].data;
}

//--------------------------------
bool ListWidget::getEntrySelected( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex].selected;
}

//--------------------------------
void ListWidget::setEntrySelected( size_t vIndex, bool vWhich )
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	mEntries[vIndex].selected = vWhich;
	if ( mSelected == -1 )
		mSelected = vIndex;

	flagDirty( );
}

//--------------------------------
size_t ListWidget::getEntryCount( ) const
{
	return mEntries.size( );
}

//--------------------------------
int ListWidget::pickEntry( const Mocha::Vector2& vPoint )
{
	// Get the font to use

	Font* f = getRenderFont( );
	if ( f == 0 )
		return -1;

	// Adjust for icon height if necessary

	float spaceY = f->getMaxGlyphHeight( );
	if ( mDrawIcons && (spaceY < ICON_SIZE) )
		spaceY = ICON_SIZE;

	// Calculate which entry is selected

	int s = (vPoint.y+getOffsetY( f )) / spaceY;

	if ( (s >= 0) && (s < getEntryCount( )) )
	{
		bool shiftDown = (getGuiManager( )->getKeyModifiers( ) & KM_SHIFT);
		if ( (mMultiSelect == false) || (shiftDown == false) )
			deselectAll( );

		bool status = !mEntries[s].selected;
		mEntries[s].selected = status;

		if ( status )
		{
			mSelected = s;
			onSelected( s );
		}
		else
			onUnselected( s );	

		flagDirty( );
		return s;
	}

	return -1;
}

//--------------------------------
void ListWidget::onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	// Simply pick a new entry to use

	pickEntry( vPoint );
}

//--------------------------------
void ListWidget::deselectAll( )
{
	EntryList::iterator it;
	for ( it = mEntries.begin( ); it != mEntries.end( ); it++ )
		(*it).selected = false;

	flagDirty( );
}

//--------------------------------
const ListWidgetEntry& ListWidget::getEntry( size_t vIndex ) const
{
	if ( vIndex >= getEntryCount( ) )
		throw Exception( "List entry index out of range" );

	return mEntries[vIndex];
}

//--------------------------------
float ListWidget::getOffsetY( Font* vFont ) const
{
	float clientHeight = getClientRectangle( ).getHeight( );

	// Adjust for icon height if necessary

	float spaceY = vFont->getMaxGlyphHeight( );
	if ( mDrawIcons && (spaceY < ICON_SIZE) )
		spaceY = ICON_SIZE;

	// Calculate total height of entries

	float totalHeight = spaceY * getEntryCount( );
	mScrollBar->setSliderSize( (totalHeight > 0.0f) ? clientHeight / totalHeight : 1.0f );

	// Calculate scroll offset

	float value = mScrollBar->getValue( );

	float tmp = totalHeight - clientHeight;
	if ( tmp < 0 )
		tmp = 0.0f;

	return tmp * value;
}

//--------------------------------
void ListWidget::onDraw( Brush& vBrush ) const
{
	// Get theme

	Theme* theme = getRenderTheme( );
	if ( theme == 0 )
		return;

	// Get the font and color to use

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	Mocha::Color textColor = getDerivedColor( theme->getColor( "ListWidgetTextColor" ) );
	Mocha::Color textSelectedColor = theme->getColor( "ListWidgetTextSelectedColor" );
	Mocha::Color color = getRenderColor( );

	// Calculate scroll offset

	float offsetY = getOffsetY( f );
	
	// Adjust for icon height if necessary

	float spaceY = f->getMaxGlyphHeight( );
	if ( mDrawIcons && (spaceY < ICON_SIZE) )
		spaceY = ICON_SIZE;

	// Adjust clipping region to take the scrollbar into account
	// (Not necessary, but looks a little bit more 'correct')

	const Mocha::Rectangle& client = getClientRectangle( );
	Mocha::Rectangle clip = vBrush.getClipRegion( );

	Mocha::Rectangle tmp = client;
	tmp.setWidth( client.getWidth( ) - mScrollBar->getRectangle( ).getWidth( ) - 1 );
	vBrush.setClipRegion( clip.intersect( tmp ) );

	// Draw all the entries in the list

	vBrush.setBlendMode( BRUSHBLEND_ALPHA );

	bool enabled = getEnabled( );

	size_t x;
	for ( x = 0; x < getEntryCount( ); x++ )
	{
		Mocha::Rectangle r = client;
		r.translate( 0.0f, (x * spaceY) - offsetY );
		r.setHeight( f->getMaxGlyphHeight( ) );

		if ( r.bottom < client.top )
			continue;

		if ( r.top > client.bottom )
			break;

		bool selected = getEntrySelected( x );
		if ( selected && (enabled == true) )
		{
			// Draw rectangle over selected item

			vBrush.setTexture( 0 );
			vBrush.setColor( color );
			vBrush.drawRectangle( r );
		}

		// Draw icon if necessary

		const Mocha::String& iconName = mEntries[x].icon;
		if ( mDrawIcons && (iconName != "") )
		{
			Texture* icon = theme->getTexture( iconName );
			vBrush.setColor( Mocha::Color::White );

			Mocha::Rectangle tmp;
			tmp.setPosition( r.left + 1, r.top - 1 );
			tmp.setSize( ICON_SIZE, ICON_SIZE );

			vBrush.setTexture( icon );
			vBrush.drawRectangle( tmp );				
		}

		// Draw entry text

		if ( mDrawIcons )
			r.translate( 18.0f, 0.0f );

		if ( selected && enabled )
			vBrush.setColor( textSelectedColor );
		else
			vBrush.setColor( textColor );

		vBrush.drawText( f, getEntryText( x ), r, false );
	}

	// Reset the clipping region

	vBrush.setClipRegion( clip );
}

//--------------------------------
void ListWidget::setScroll( float vAmount )
{
	mScrollBar->setValue( vAmount );
	flagDirty( );
}

//--------------------------------
void ListWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "MultiSelect", "bool", "Multi-Select Enabled" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "ScrollVisible", "bool", "Scrollbar Visible" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "DrawIcons", "bool", "Draw Icons" ) );
}

//--------------------------------
Mocha::CommandResult ListWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setMultiSelect" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setMultiSelect( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getMultiSelect" )
	{
		vOut.push_back( getMultiSelect( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setDrawIcons" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setDrawIcons( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getDrawIcons" )
	{
		vOut.push_back( getDrawIcons( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setScrollVisible" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setScrollVisible( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getScrollVisible" )
	{
		vOut.push_back( getScrollVisible( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
Mocha::String ListWidget::getClassName( ) const
{
	return "List";
}

//--------------------------------
void ListWidget::adjustScrollBarSteps( )
{
	if ( mEntries.size( ) == 0 )
		return;

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	float spaceY = f->getMaxGlyphHeight( );
	float viewableentries = (getClientRectangle().getHeight() / spaceY);

	float minstep = 1 / (float)(mEntries.size() - viewableentries);
	if( minstep > 0 )
	{
		mScrollBar->setStep( minstep );
	}
}

//--------------------------------
Widget* ListWidget::factory( GuiManager* vManager )
{
	return new ListWidget( vManager );
}

}
