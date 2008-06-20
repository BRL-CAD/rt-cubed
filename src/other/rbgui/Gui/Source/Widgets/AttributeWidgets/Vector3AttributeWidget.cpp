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

#include "Mocha/Vector3.h"

#include "RBGui/Widgets/AttributeWidgets/Vector3AttributeWidget.h"

namespace RBGui
{

//--------------------------------
Vector3AttributeWidget::Vector3AttributeWidget( GuiManager* vManager )
: EvaluatorAttributeWidget( vManager )
{
	mEvaluatorX = new EvaluatorWidget( vManager );
	mEvaluatorX->setCallback( &Vector3AttributeWidget::evaluatorChanged, this );

	mEvaluatorY = new EvaluatorWidget( vManager );
	mEvaluatorY->setCallback( &Vector3AttributeWidget::evaluatorChanged, this );

	mEvaluatorZ = new EvaluatorWidget( vManager );
	mEvaluatorZ->setCallback( &Vector3AttributeWidget::evaluatorChanged, this );

	attach( mEvaluatorX );
	attach( mEvaluatorY );
	attach( mEvaluatorZ );
}

//--------------------------------
Vector3AttributeWidget::~Vector3AttributeWidget( )
{
	// ...
}

//--------------------------------
void Vector3AttributeWidget::evaluatorChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	valueChanged( Mocha::Vector3( mEvaluatorX->getValue( ), mEvaluatorY->getValue( ), mEvaluatorZ->getValue( ) ) );
}

//--------------------------------
void Vector3AttributeWidget::onRectangleChanged( )
{
	const Mocha::Rectangle& r = getClientRectangle( );

	float w = (r.getWidth( )-2) / 3;
	float h = r.getHeight( );

	mEvaluatorX->setRectangle( 0.0f, 0.0f, w, h );
	mEvaluatorY->setRectangle( w+1, 0.0f, w, h );
	mEvaluatorZ->setRectangle( ((w+1)*2), 0.0f, w, h );
}

//--------------------------------
void Vector3AttributeWidget::setAttribute( const Mocha::Value& vValue )
{
	const Mocha::Vector3& v = vValue.getAsVector3( );

	mEvaluatorX->setValue( v.x );
	mEvaluatorY->setValue( v.y );
	mEvaluatorZ->setValue( v.z );
}

//--------------------------------
void Vector3AttributeWidget::getAttribute( Mocha::Value& vValue ) const
{
	vValue.setVector3( Mocha::Vector3( mEvaluatorX->getValue( ), mEvaluatorY->getValue( ), mEvaluatorY->getValue( ) ) );
}

//--------------------------------
void Vector3AttributeWidget::setParams( float vStep, float vMin, float vMax, EvaluatorWidgetMode vMode )
{
	mEvaluatorX->setStep( vStep );
	mEvaluatorX->setRange( Mocha::Vector2( vMin, vMax ) );
	mEvaluatorX->setMode( vMode );

	mEvaluatorY->setStep( vStep );
	mEvaluatorY->setRange( Mocha::Vector2( vMin, vMax ) );
	mEvaluatorY->setMode( vMode );

	mEvaluatorZ->setStep( vStep );
	mEvaluatorZ->setRange( Mocha::Vector2( vMin, vMax ) );
	mEvaluatorZ->setMode( vMode );
}

//--------------------------------
AttributeWidget* Vector3AttributeWidget::factory( GuiManager* vManager )
{
	return new Vector3AttributeWidget( vManager );
}


}
