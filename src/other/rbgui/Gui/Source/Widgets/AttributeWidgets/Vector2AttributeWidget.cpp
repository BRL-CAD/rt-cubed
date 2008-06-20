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

#include "RBGui/Widgets/AttributeWidgets/Vector2AttributeWidget.h"

namespace RBGui
{

//--------------------------------
Vector2AttributeWidget::Vector2AttributeWidget( GuiManager* vManager )
: EvaluatorAttributeWidget( vManager )
{
	mEvaluatorX = new EvaluatorWidget( vManager );
	mEvaluatorX->setCallback( &Vector2AttributeWidget::evaluatorChanged, this );

	mEvaluatorY = new EvaluatorWidget( vManager );
	mEvaluatorY->setCallback( &Vector2AttributeWidget::evaluatorChanged, this );

	attach( mEvaluatorX );
	attach( mEvaluatorY );
}

//--------------------------------
Vector2AttributeWidget::~Vector2AttributeWidget( )
{
	// ...
}

//--------------------------------
void Vector2AttributeWidget::evaluatorChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	valueChanged( Mocha::Vector2( mEvaluatorX->getValue( ), mEvaluatorY->getValue( ) ) );
}

//--------------------------------
void Vector2AttributeWidget::onRectangleChanged( )
{
	const Mocha::Rectangle& r = getClientRectangle( );

	float w = (r.getWidth( )-2) / 2;
	float h = r.getHeight( );

	mEvaluatorX->setRectangle( 0.0f, 0.0f, w, h );
	mEvaluatorY->setRectangle( w+1, 0.0f, w, h );
}

//--------------------------------
void Vector2AttributeWidget::setAttribute( const Mocha::Value& vValue )
{
	const Mocha::Vector2& v = vValue.getAsVector2( );

	mEvaluatorX->setValue( v.x );
	mEvaluatorY->setValue( v.y );
}

//--------------------------------
void Vector2AttributeWidget::getAttribute( Mocha::Value& vValue ) const
{
	vValue.setVector2( Mocha::Vector2( mEvaluatorX->getValue( ), mEvaluatorY->getValue( ) ) );
}

//--------------------------------
void Vector2AttributeWidget::setParams( float vStep, float vMin, float vMax, EvaluatorWidgetMode vMode )
{
	mEvaluatorX->setStep( vStep );
	mEvaluatorX->setRange( Mocha::Vector2( vMin, vMax ) );
	mEvaluatorX->setMode( vMode );

	mEvaluatorY->setStep( vStep );
	mEvaluatorY->setRange( Mocha::Vector2( vMin, vMax ) );
	mEvaluatorY->setMode( vMode );
}

//--------------------------------
AttributeWidget* Vector2AttributeWidget::factory( GuiManager* vManager )
{
	return new Vector2AttributeWidget( vManager );
}

}
