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

#include "RBGui/Widgets/AttributeWidgets/IntAttributeWidget.h"

namespace RBGui
{

//--------------------------------
IntAttributeWidget::IntAttributeWidget( GuiManager* vManager )
: EvaluatorAttributeWidget( vManager, 1 )
{
	mEvaluator = new EvaluatorWidget( vManager );
	mEvaluator->setCallback( &IntAttributeWidget::evaluatorChanged, this );
	mEvaluator->setMode( EVALUATORMODE_INTEGER );

	attach( mEvaluator );
}

//--------------------------------
IntAttributeWidget::~IntAttributeWidget( )
{
	// ...
}

//--------------------------------
void IntAttributeWidget::evaluatorChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	valueChanged( vValues[0].getNumber( ) );
}

//--------------------------------
void IntAttributeWidget::onRectangleChanged( )
{
	mEvaluator->setSize( getClientRectangle( ).getSize( ) );
}

//--------------------------------
void IntAttributeWidget::setAttribute( const Mocha::Value& vValue )
{
	mEvaluator->setValue( (int)vValue.getAsNumber( ) );
}

//--------------------------------
void IntAttributeWidget::getAttribute( Mocha::Value& vValue ) const
{
	vValue.setNumber( mEvaluator->getValue( ) );
}

//--------------------------------
void IntAttributeWidget::setParams( float vStep, float vMin, float vMax, EvaluatorWidgetMode vMode )
{
	mEvaluator->setStep( (int)vStep );
	mEvaluator->setRange( Mocha::Vector2( (int)vMin, (int)vMax ) );
}

//--------------------------------
AttributeWidget* IntAttributeWidget::factory( GuiManager* vManager )
{
	return new IntAttributeWidget( vManager );
}

}
