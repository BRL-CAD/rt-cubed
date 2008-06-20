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

#include "RBGui/Widgets/AttributeWidgets/SplineAttributeWidget.h"

#include "RBGui/Widgets/SplineWidget.h"

namespace RBGui
{

//--------------------------------
SplineAttributeWidget::SplineAttributeWidget( GuiManager* vManager )
: AttributeWidget( vManager )
{
	mSpline = new SplineWidget( vManager );
	mSpline->setCallback( &SplineAttributeWidget::splineChanged, this );
	mSpline->setEditable( true );

	attach( mSpline );
}

//--------------------------------
SplineAttributeWidget::~SplineAttributeWidget( )
{
	// ...
}

//--------------------------------
void SplineAttributeWidget::splineChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	const Mocha::Vector2List& handles = mSpline->getHandles( );
	Mocha::ValueList l;

	Mocha::Vector2List::const_iterator it;
	for ( it = handles.begin( ); it != handles.end( ); it++ )
		l.push_back( (*it) );

	valueChanged( l );
}

//--------------------------------
void SplineAttributeWidget::onRectangleChanged( )
{
	mSpline->setSize( getClientRectangle( ).getSize( ) );
}

//--------------------------------
void SplineAttributeWidget::setAttribute( const Mocha::Value& vValue )
{
	mSpline->clearHandles( );

	if ( vValue.getType( ) == Mocha::VALUE_LIST )
	{
		const Mocha::ValueList& l = vValue.getList( );

		Mocha::ValueList::const_iterator it;
		for ( it = l.begin( ); it != l.end( ); it++ )
		{
			const Mocha::Value& v = (*it);
			if ( v.getType( ) == Mocha::VALUE_VECTOR2 )
				mSpline->addHandle( v.getVector2( ) );
		}
	}
}

//--------------------------------
void SplineAttributeWidget::getAttribute( Mocha::Value& vValue ) const
{
	const Mocha::Vector2List& handles = mSpline->getHandles( );
	Mocha::ValueList l;

	Mocha::Vector2List::const_iterator it;
	for ( it = handles.begin( ); it != handles.end( ); it++ )
		l.push_back( (*it) );

	vValue.setList( l );
}

//--------------------------------
void SplineAttributeWidget::setOptions( const Mocha::StringList& vOptions )
{
	// ...
}

//--------------------------------
float SplineAttributeWidget::getAttributeHeight( ) const
{
	return 60.0f;
}

//--------------------------------
AttributeWidget* SplineAttributeWidget::factory( GuiManager* vManager )
{
	return new SplineAttributeWidget( vManager );
}

}
