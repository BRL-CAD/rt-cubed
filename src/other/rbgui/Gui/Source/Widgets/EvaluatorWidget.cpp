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
#include "Mocha/Math.h"

#include "Mocha/DataSection.h"

#include "RBGui/Widgets/EvaluatorWidget.h"
#include "RBGui/Widgets/TextEntryWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"

namespace RBGui
{

//--------------------------------------------
EvaluatorWidget::EvaluatorWidget( GuiManager* vManager )
: Widget( vManager ), mMode( EVALUATORMODE_FLOAT ), mRange( -10000.0f, 10000.0f ), mStep( 0.1f )
{
	// Create text entry field

	mTextEntry = new TextEntryWidget( vManager );
	mTextEntry->setCallback( &EvaluatorWidget::returnPressed, this, "onReturnPressed" );
	mTextEntry->setCallback( &EvaluatorWidget::returnPressed, this, "onFocusLost" );
	mTextEntry->setNumericOnly( true );
	mTextEntry->setGenerated( true );

	mPlusButton = new ButtonWidget( vManager );
	mPlusButton->setCallback( &EvaluatorWidget::plusPressed, this );
	mPlusButton->setAnimatedImage( true );
	mPlusButton->setSink( false );
	//mPlusButton->setBorderName( "DropButton" );
	mPlusButton->setGenerated( true );
	//mPlusButton->setSignalRepeat( true );

	mMinusButton = new ButtonWidget( vManager );
	mMinusButton->setCallback( &EvaluatorWidget::minusPressed, this );
	mMinusButton->setAnimatedImage( true );
	mMinusButton->setSink( false );
	//mMinusButton->setBorderName( "DropButton" );
	mMinusButton->setGenerated( true );
	//mMinusButton->setSignalRepeat( true );

	attach( mTextEntry );
	attach( mPlusButton );
	attach( mMinusButton );

	// Set initial value

	setValue( 0.0f );
}

//--------------------------------------------
EvaluatorWidget::~EvaluatorWidget( )
{
	// ...
}

//--------------------------------------------
void EvaluatorWidget::plusPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	increment( );
	raiseEvents( );
}

//--------------------------------------------
void EvaluatorWidget::minusPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	decrement( );
	raiseEvents( );
}

//--------------------------------------------
void EvaluatorWidget::returnPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	float val = Mocha::StringToFloat( mTextEntry->getText( ) );

	setValue( val );
	raiseEvents( );
}

//--------------------------------------------
void EvaluatorWidget::setMode( EvaluatorWidgetMode vMode )
{
	mMode = vMode;
	//setValue( getValue( ) );
}

//--------------------------------------------
EvaluatorWidgetMode EvaluatorWidget::getMode( ) const
{
	return mMode;
}

//--------------------------------------------
void EvaluatorWidget::onRectangleChanged( )
{
	// Get new client rectangle

	const Mocha::Rectangle& client = getClientRectangle( );

	// Reposition the buttons

	float size = client.getHeight( ) / 2;

	Mocha::Rectangle plusRect;
	plusRect.setPosition( client.getWidth( ) - size, 0.0f );
	plusRect.setSize( size, size );

	mPlusButton->setRectangle( plusRect );

	Mocha::Rectangle minusRect;
	minusRect.setPosition( client.getWidth( ) - size, size );
	minusRect.setSize( size, size );

	mMinusButton->setRectangle( minusRect );

	// Resize text entry field

	Mocha::Rectangle r;
	r.setSize( client.getWidth( ) - (size + 1), client.getHeight( ) );
	r.setPosition( 0.0f, 0.0f );

	mTextEntry->setRectangle( r );
}

//--------------------------------------------
void EvaluatorWidget::setStep( float vValue )
{
	mStep = vValue;
}

//--------------------------------------------
float EvaluatorWidget::getStep( ) const
{
	return mStep;
}

//--------------------------------------------
void EvaluatorWidget::increment( )
{
	setValue( getValue( ) + mStep );
}

//--------------------------------------------
void EvaluatorWidget::decrement( )
{
	setValue( getValue( ) - mStep );
}

//--------------------------------------------
void EvaluatorWidget::raiseEvents( )
{
	Mocha::ValueList values;
	values.push_back( getValue( ) );

	doCallback( values );
}

//--------------------------------------------
void EvaluatorWidget::setValue( float vValue )
{
	float v = Mocha::clamp( vValue, mRange.x, mRange.y );

	if ( mMode == EVALUATORMODE_FLOAT )
		mTextEntry->setText( Mocha::FloatToString( v ) );
	else
		mTextEntry->setText( Mocha::IntToString( (int)v ) );

	flagDirty( );
}

//--------------------------------------------
float EvaluatorWidget::getValue( ) const
{
	Mocha::String v = mTextEntry->getText( );
	return Mocha::StringToFloat( v );
}

//--------------------------------------------
void EvaluatorWidget::setRange( const Mocha::Vector2& vRange )
{
	mRange = vRange;
}

//--------------------------------------------
const Mocha::Vector2& EvaluatorWidget::getRange( ) const
{
	return mRange;
}

//--------------------------------------------
void EvaluatorWidget::onDraw( Brush& vBrush ) const
{
	Theme* theme = getRenderTheme( );
	if ( theme == 0 )
		return;

	// Set the drop button image

	mPlusButton->setImage( theme->getTexture( "EvaluatorPlus" ) );
	mMinusButton->setImage( theme->getTexture( "EvaluatorMinus" ) );
}

//--------------------------------------------
void EvaluatorWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Value", "float", "Value" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Step", "float", "Step Value" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Range", "vector2", "Range" ) );
}

//--------------------------------------------
Mocha::CommandResult EvaluatorWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setRange" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setRange( vIn[0].getAsVector2( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getRange" )
	{
		vOut.push_back( getRange( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setValue" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setValue( vIn[0].getAsNumber( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getValue" )
	{
		vOut.push_back( getValue( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setStep" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setStep( vIn[0].getAsNumber( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getStep" )
	{
		vOut.push_back( getStep( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------------------
Mocha::String EvaluatorWidget::getClassName( ) const
{
	return "Evaluator";
}

//--------------------------------------------
Widget* EvaluatorWidget::factory( GuiManager* vManager )
{
	return new EvaluatorWidget( vManager );
}

}
