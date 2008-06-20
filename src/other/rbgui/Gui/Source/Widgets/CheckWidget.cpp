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

#include "Mocha/DataSection.h"

#include "RBGui/Widgets/CheckWidget.h"

namespace RBGui
{

//--------------------------------
CheckWidget::CheckWidget( GuiManager* vManager )
: Widget( vManager ), mChecked( false ), mColor( Mocha::Color::White )
{
	// ...
}

//--------------------------------
CheckWidget::~CheckWidget( )
{
	// ...
}

//--------------------------------
void CheckWidget::onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	mColor = Mocha::Color( 0.7f, 0.7f, 0.7f, 1.0f );
	flagDirty( );
}

//--------------------------------
void CheckWidget::onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	mColor = Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f );
	setChecked( !getChecked( ) );

	onChanged( );
}

//--------------------------------
void CheckWidget::setChecked( bool vWhich )
{
	mChecked = vWhich;
	flagDirty( );
}

//--------------------------------
bool CheckWidget::getChecked( ) const
{
	return mChecked;
}

//--------------------------------
void CheckWidget::onChanged( )
{
	Mocha::ValueList v;
	v.push_back( mChecked );

	doCallback( v );
}

//--------------------------------
void CheckWidget::onDraw( Brush& vBrush ) const
{
	// Get the image to draw

	Texture* t = getRenderTheme( )->getTexture( "CheckBox" );
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
	uv.top = ( mChecked ? 1.0f : 0.0f ) * 0.5f;
	uv.bottom = ( ( mChecked ? 1.0f : 0.0f ) * 0.5f) + 0.5f;

	vBrush.setTexture( t );
	vBrush.drawRectangle( r, uv );

	// Draw the text next to it

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	r = getClientRectangle( );
	r.left += texSize.x + 3;

	vBrush.setColor( getDerivedColor( getRenderColor( ) ) );
	vBrush.drawText( f, getText( ), r, true );
}

//--------------------------------
Mocha::CommandResult CheckWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setChecked" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setChecked( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getChecked" )
	{
		vOut.push_back( getChecked( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}


//--------------------------------
void CheckWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Checked", "bool", "Checked" ) );
}

//--------------------------------
Mocha::String CheckWidget::getClassName( ) const
{
	return "Check";
}

//--------------------------------
Widget* CheckWidget::factory( GuiManager* vManager )
{
	return new CheckWidget( vManager );
}

}
