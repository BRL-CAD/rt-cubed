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

#include "RBGui/Widgets/GroupWidget.h"
#include "RBGui/Widgets/ScrollWidget.h"

namespace RBGui
{

//--------------------------------
GroupWidget::GroupWidget( GuiManager* vManager )
: Widget( vManager )
{
	// Create the scroll bar

	mScrollBar = new ScrollWidget( vManager );
	mScrollBar->setCallback( &GroupWidget::scrolled, this );
	mScrollBar->setScrollable( false );
	mScrollBar->setGenerated( true );

	attach( mScrollBar );
}

//--------------------------------
GroupWidget::~GroupWidget( )
{
	// ...
}

//--------------------------------
void GroupWidget::scrolled( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	float scroll = mScrollBar->getValue( );
	setScroll( Mocha::Vector2( 0.0f, (int)-getOffsetY( scroll ) ) );
}

//--------------------------------
void GroupWidget::onMouseScrolled( float vValue )
{
	/*float val = mScrollBar->getValue( ) - ( vValue * 0.10f );
	val = clamp( val, 0.0f, 1.0f );

	mScrollBar->setValue( val );

	setScroll( Mocha::Vector2( 0.0f, (int)-getOffsetY( val ) ) );*/
}

//--------------------------------
void GroupWidget::onRectangleChanged( )
{
	// Get new client rectangle

	const Mocha::Rectangle& rect = getClientRectangle( );

	// Adjust size and position of scrollbar

	Theme* theme = getRenderTheme( );
	if ( theme )
	{
		float width = theme->getFloat( "ScrollWidth", 14.0f );

		Mocha::Rectangle r;
		r.setPosition( rect.getWidth( ) - width, 0.0f );
		r.setSize( width, rect.getHeight( ) );

		mScrollBar->setRectangle( r );
	}

	// Update scroll bar slider size

	mScrollBar->setSliderSize( ( mRegionSize.y > 0.0f ) ? rect.getHeight( ) / mRegionSize.y : 1.0f );
}

//--------------------------------
float GroupWidget::getOffsetY( float vScroll ) const
{
	// Calculate scroll offset

	float tmp = mRegionSize.y - getClientRectangle( ).getHeight( );
	if ( tmp < 0 )
		tmp = 0.0f;

	return tmp * vScroll;
}

//--------------------------------
void GroupWidget::updateRegionSize( ) const
{
	// Get the highest bottom value

	mRegionSize = Mocha::Vector2( );

	const WidgetList& children = getChildren( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{
		Widget* w = (*it);

		const Mocha::Rectangle& r = w->getRectangle( );
		if ( r.bottom > mRegionSize.y )
			mRegionSize.y = r.bottom;
		if ( r.right > mRegionSize.x )
			mRegionSize.x = r.right;
	}

	// Update scroll bar

	mScrollBar->setSliderSize( getClientRectangle( ).getHeight( ) / mRegionSize.y );
}

//--------------------------------
Mocha::Vector2 GroupWidget::getRegionSize( ) const
{
	return mRegionSize;
}

//--------------------------------
Mocha::String GroupWidget::getClassName( ) const
{
	return "Group";
}

//--------------------------------
Widget* GroupWidget::factory( GuiManager* vManager )
{
	return new GroupWidget( vManager );
}

}

