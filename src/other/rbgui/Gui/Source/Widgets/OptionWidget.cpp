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

#include "RBGui/Widgets/OptionWidget.h"

namespace RBGui
{

//--------------------------------
OptionWidget::OptionWidget( GuiManager* vManager )
: Widget( vManager ), mSelected( false ), mColor( Mocha::Color::White )
{
	// ...
}

//--------------------------------
OptionWidget::~OptionWidget( )
{
	// ...
}

//--------------------------------
void OptionWidget::onChanged( )
{
	Mocha::ValueList v;
	v.push_back( mSelected );

	doCallback( v );
}

//--------------------------------
void OptionWidget::onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	// Deselect all other widgets in parent

	mColor = Mocha::Color::White;
	setSelected( true );

	onChanged( );
}

//--------------------------------
void OptionWidget::onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	// Change color a bit

	mColor = Mocha::Color::Gray;
	flagDirty( );
}

//--------------------------------
void OptionWidget::setSelected( bool vWhich )
{
	if ( vWhich == true )
	{
		Widget* p = getParent( );
		if ( p )
		{
			const WidgetList& siblings = p->getChildren( );

			WidgetList::const_iterator it;
			for ( it = siblings.begin( ); it != siblings.end( ); it++ )
			{
				OptionWidget* w = dynamic_cast<OptionWidget*>( (*it).get( ) );
				if ( w && w != this )
					w->mSelected = false;
			}
		}
	}

	mSelected = vWhich;
	flagDirty( );
}

//--------------------------------
bool OptionWidget::getSelected( ) const
{
	return mSelected;
}

//--------------------------------
void OptionWidget::onDraw( Brush& vBrush ) const
{
	// Get the image to draw

	Texture* t = getRenderTheme( )->getTexture( "OptionButton" );
	if ( t == 0 )
		return;

	const Mocha::Vector2 texSize = t->getSize( );

	// Draw the image in the upper-left corner

	vBrush.setBlendMode( BRUSHBLEND_ALPHA );
	vBrush.setFilterMode( BRUSHFILTER_NEAREST );
	vBrush.setColor( getDerivedColor( mColor ) );

	Mocha::Rectangle r = getClientRectangle( );
	r.setSize( texSize * Mocha::Vector2( 1.0f, 0.5f ) );

	Mocha::Rectangle uv;
	uv.left = 0.0f;
	uv.right = 1.0f;
	uv.top = ( mSelected ? 1.0f : 0.0f ) * 0.5f;
	uv.bottom = ( ( mSelected ? 1.0f : 0.0f ) * 0.5f) + 0.5f;

	vBrush.setTexture( t );
	vBrush.drawRectangle( r, uv );

	// Draw the text next to it

	Mocha::Color c = getDerivedColor( getRenderColor( ) );

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	r = getClientRectangle( );
	r.left += texSize.x + 3;

	vBrush.setColor( c );
	vBrush.drawText( f, getText( ), r, true );
}

//--------------------------------
void OptionWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Selected", "bool", "Selected" ) );
}

//--------------------------------
Mocha::CommandResult OptionWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setSelected" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setSelected( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getSelected" )
	{
		vOut.push_back( getSelected( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
Mocha::String OptionWidget::getClassName( ) const
{
	return "Option";
}

//--------------------------------
Widget* OptionWidget::factory( GuiManager* vManager )
{
	return new OptionWidget( vManager );
}

}
