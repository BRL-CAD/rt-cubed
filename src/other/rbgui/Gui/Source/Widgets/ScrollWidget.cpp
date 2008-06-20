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

#include "RBGui/Widgets/ScrollWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"

namespace RBGui
{

//--------------------------------
ScrollWidget::ScrollWidget( GuiManager* vManager )
: Widget( vManager ), mOrientation( SCROLL_HORIZONTAL ), mScrolling( false ), mRange( 0.0f, 1.0f ), mStep( 0.1f ),
  mDragX( 0 ), mDragY( 0 ), mValue( 0.0f ), mSliderSize( 0.0f )
{
	// Setup the minus button

	mMinusButton = new ButtonWidget( vManager );
	mMinusButton->setCallback( &ScrollWidget::minusPressed, this );
	mMinusButton->setAnimatedImage( true );
	mMinusButton->setSink( false );
	//mMinusButton->setBorderName( "ScrollButton" );
	mMinusButton->setGenerated( true );
	//mMinusButton->setSignalRepeat( true );
	attach( mMinusButton );

	// Setup the plus button

	mPlusButton = new ButtonWidget( vManager );
	mPlusButton->setCallback( &ScrollWidget::plusPressed, this );
	mPlusButton->setAnimatedImage( true );
	mPlusButton->setSink( false );
	//mPlusButton->setBorderName( "ScrollButton" );
	mPlusButton->setGenerated( true );
	//mPlusButton->setSignalRepeat( true );
	attach( mPlusButton );
}

//--------------------------------
ScrollWidget::~ScrollWidget( )
{
	// ...
}

//--------------------------------
void ScrollWidget::setSliderSize( float vSize )
{
	mSliderSize = Mocha::clamp( vSize, 0.0f, 1.0f );
	updateRects( );
}

//--------------------------------
float ScrollWidget::getSliderSize( ) const
{
	return mSliderSize;
}

//--------------------------------
void ScrollWidget::plusPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	stepPlus( );
	onScroll( );
}

//--------------------------------
void ScrollWidget::minusPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	stepMinus( );
	onScroll( );
}

//--------------------------------
void ScrollWidget::setRange( const Mocha::Vector2& vValue )
{
	mRange = vValue;
	flagDirty( );
}

//--------------------------------
const Mocha::Vector2& ScrollWidget::getRange( ) const
{
	return mRange;
}

//--------------------------------
void ScrollWidget::setStep( float vValue )
{
	mStep = vValue;
}

//--------------------------------
float ScrollWidget::getStep( ) const
{
	return mStep;
}

//--------------------------------
void ScrollWidget::setValue( float vValue )
{
	float val = Mocha::clamp( vValue, mRange.x, mRange.y );
	
	if ( mRange.y != 0.0f )
		mValue = (val - mRange.x) / (mRange.y-mRange.x);
	else
		mValue = val;

	updateRects( );
}

//--------------------------------
float ScrollWidget::getValue( ) const
{
	// Interpolate value through range

	float val;
	Mocha::lerp( val, mRange.x, mRange.y, mValue );

	return val;
}

//--------------------------------
void ScrollWidget::stepMinus( )
{
	mValue -= mStep;
	if( mValue < 0 )
		mValue = 0;

	updateRects( );
}

//--------------------------------
void ScrollWidget::stepPlus( )
{
	mValue += mStep;
	if( mValue > 1 )
		mValue = 1;

	updateRects( );
}

//--------------------------------
void ScrollWidget::updateRects( )
{
	float width = getRectangle( ).getWidth( );
	float height = getRectangle( ).getHeight( );

	const Mocha::Rectangle& screen = getScreenRectangle( );

	if ( width > height )
	{
		mOrientation = SCROLL_HORIZONTAL;

		mMinusRect.setSize( height, height );
		mPlusRect.setSize( height, height );

		if ( mSliderSize <= 0.0f )
			mSliderRect.setSize( height, height );
		else
		{
			Mocha::Vector2 tmp = screen.getSize( ) - Mocha::Vector2( height * 2, 0.0f );
			mSliderRect.setSize( tmp * Mocha::Vector2( mSliderSize, 1.0f ) );

			if ( mSliderRect.getWidth( ) < 10.0f )
				mSliderRect.setWidth( 10.0f );
		}

		float reduce = mSliderRect.getWidth( ) + (height * 2);
		mSliderRect.setPosition( (screen.getWidth( ) - reduce) * mValue + screen.left + height, screen.top );

		mMinusRect.setPosition( 0.0f, 0.0f );
		mPlusRect.setPosition( getRectangle( ).getWidth( ) - height, 0.0f );

		// set up two never-rendered quads that track the 'large' click regions.. just for convienience.

		mLargeMinusRect.setPosition( screen.left + height, screen.top );
		mLargeMinusRect.setSize( mSliderRect.left - (screen.left + mMinusRect.right), height );
		
		mLargePlusRect.setPosition( mSliderRect.right, screen.top );
		mLargePlusRect.setSize( (screen.left + mPlusRect.left) - mSliderRect.right, height );

		// Calculate background rectangle

		mBackRect.left = screen.left + mMinusRect.getWidth( );
		mBackRect.right = screen.right - mPlusRect.getWidth( );
		mBackRect.top = screen.top;
		mBackRect.bottom = screen.bottom;

		Texture* left = getRenderTheme( )->getTexture( "ScrollLeft" );
		mMinusButton->setImage( left );

		Texture* right = getRenderTheme( )->getTexture( "ScrollRight" );
		mPlusButton->setImage( right );
	}
	else
	{
		mOrientation = SCROLL_VERTICAL;

		mMinusRect.setSize( width, width );
		mPlusRect.setSize( width, width );

		mMinusRect.setPosition( 0.0f, 0.0f );
		mPlusRect.setPosition( 0.0f, getRectangle( ).getHeight( ) - width );

		if ( mSliderSize <= 0.0f )
			mSliderRect.setSize( width, width );
		else
		{
			Mocha::Vector2 tmp = screen.getSize( ) - Mocha::Vector2( 0.0f, width * 2 );
			mSliderRect.setSize( tmp * Mocha::Vector2( 1.0f, mSliderSize ) );

			if ( mSliderRect.getHeight( ) < 10.0f )
				mSliderRect.setHeight( 10.0f );
		}

		float reduce = mSliderRect.getHeight( ) + (width * 2);
		mSliderRect.setPosition( screen.left, (screen.getHeight( ) - reduce) * mValue + screen.top + width );

		// set up two never-rendered quads that track the 'large' click regions.. just for convienience.
		
		mLargeMinusRect.setPosition( screen.left, screen.top + width );
		mLargeMinusRect.setSize( width, mSliderRect.top - (screen.top + mMinusRect.bottom) );
		
		mLargePlusRect.setPosition( screen.left, mSliderRect.bottom );
		mLargePlusRect.setSize( width, (screen.top + mPlusRect.top) - mSliderRect.bottom );

		// Calculate background rectangle

		mBackRect.left = screen.left;
		mBackRect.top = screen.top + mMinusRect.getHeight( );
		mBackRect.bottom = screen.bottom - mPlusRect.getHeight( );
		mBackRect.right = screen.right;

		Texture* up = getRenderTheme( )->getTexture( "ScrollUp" );
		mMinusButton->setImage( up );

		Texture* down = getRenderTheme( )->getTexture( "ScrollDown" );
		mPlusButton->setImage( down );
	}

	// Update button widgets

	mMinusButton->setRectangle( mMinusRect );
	mPlusButton->setRectangle( mPlusRect );

	flagDirty( );
}

//--------------------------------
void ScrollWidget::onRectangleChanged( )
{
	updateRects( );
}

//--------------------------------
void ScrollWidget::onMousePressed( MouseButtonID vButtonID, const Mocha::Vector2& vPoint )
{
	const Mocha::Rectangle& screen = getScreenRectangle( );
	Mocha::Vector2 pt = vPoint + screen.getPosition( );

	if( (mSliderSize < 1.0f) && mSliderRect.pointInside( pt ) )
	{
		mScrolling = true;

		mDragX = pt.x - mSliderRect.left;
		mDragY = pt.y - mSliderRect.top;
	}
}

//--------------------------------
void ScrollWidget::onMouseReleased( MouseButtonID vButtonID, const Mocha::Vector2& vPoint )
{
	const Mocha::Rectangle& screen = getScreenRectangle( );
	Mocha::Vector2 pt = vPoint + screen.getPosition( );

	if( mScrolling )
	{
		mScrolling = false;
	}
	else
	{
		if( mLargeMinusRect.pointInside( pt ) )
		{
			mValue -= mStep;
			if( mValue < 0 ) mValue = 0;	
			onScroll( );
		}
		else if( mLargePlusRect.pointInside( pt ) )
		{
			mValue += mStep;
			if( mValue > 1 ) mValue = 1;	
			onScroll( );
		}
	}

	updateRects( );
}

//--------------------------------
void ScrollWidget::onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	const Mocha::Rectangle& screen = getScreenRectangle( );
	Mocha::Vector2 pt = vPoint + screen.getPosition( );

	if( mScrolling )
	{
		if( mOrientation == SCROLL_VERTICAL )
		{
			float range = screen.getHeight( ) - (mSliderRect.getHeight( ) + mPlusRect.getHeight( ) + mMinusRect.getHeight( ));
            mValue = (vPoint.y - mDragY - mMinusRect.getHeight( )) / range;
		}
		else
		{
			float range = screen.getWidth( ) - (mSliderRect.getWidth( ) + mPlusRect.getWidth( ) + mMinusRect.getWidth( ));
            mValue = (vPoint.x - mDragX - mMinusRect.getWidth( )) / range;
		}

		mValue = Mocha::clamp( mValue, 0.0f, 1.0f );

		updateRects( );
		onScroll( );
	}
}

//--------------------------------
void ScrollWidget::onScroll( )
{
	// Issue callback

	Mocha::ValueList v;
	v.push_back( getValue( ) );

	doCallback( v );
}

//--------------------------------
void ScrollWidget::onDraw( Brush& vBrush ) const
{
	// Draw background

	vBrush.setColor( Mocha::Color( 1.0f, 1.0f, 1.0f, 1.0f ) );
	vBrush.setBlendMode( BRUSHBLEND_ALPHA );

	if ( mOrientation == SCROLL_VERTICAL )
	{
		Border* border = getRenderTheme( )->getBorder( "ScrollBackgroundVertical" );
		if ( border )
			border->draw( vBrush, mBackRect );
	}
	else if ( mOrientation == SCROLL_HORIZONTAL )
	{
		Border* border = getRenderTheme( )->getBorder( "ScrollBackgroundHorizontal" );
		if ( border )
			border->draw( vBrush, mBackRect );
	}

	// Draw slider

	if ( (getEnabled( ) == true) && (mSliderSize < 1.0f) )
	{
		Border* border = getRenderTheme( )->getBorder( "ScrollSlider" );
		if ( border )
			border->draw( vBrush, mSliderRect );
	}
}

//--------------------------------
void ScrollWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Value", "float", "Value" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Range", "vector2", "Value" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Step", "float", "Value" ) );
}

//--------------------------------
Mocha::CommandResult ScrollWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setValue" )
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
	else if ( vName == "setRange" )
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

//--------------------------------
Mocha::String ScrollWidget::getClassName( ) const
{
	return "Scroll";
}

//--------------------------------
Widget* ScrollWidget::factory( GuiManager* vManager )
{
	return new ScrollWidget( vManager );
}

}
