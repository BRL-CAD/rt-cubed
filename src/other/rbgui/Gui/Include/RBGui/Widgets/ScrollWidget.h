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

#ifndef OLIVIA_SCROLLGUIWIDGET_H
#define OLIVIA_SCROLLGUIWIDGET_H

#include "RBGui/Widget.h"

namespace RBGui
{

//--------------------------------
class ButtonWidget;

//--------------------------------
/// A vertical/horizontal scrollbar widget
class GUI_EXPORT ScrollWidget : public Widget
{

friend class ScrollPlusCallback;
friend class ScrollMinusCallback;

private:
	enum Orientation
	{
		SCROLL_VERTICAL = 0,
		SCROLL_HORIZONTAL
	};

	ButtonWidget* mMinusButton;

	ButtonWidget* mPlusButton;

	Mocha::Rectangle mSliderRect;

	Mocha::Rectangle mMinusRect;

	Mocha::Rectangle mPlusRect;

	Mocha::Rectangle mBackRect;

	Mocha::Rectangle mLargeMinusRect;
	
	Mocha::Rectangle mLargePlusRect;

	Orientation mOrientation;

	bool mScrolling;

	float mStep;

	Mocha::Vector2 mRange;

	float mSliderSize;

	float mValue;

	int mDragX;

	int mDragY;

	void updateRects( );

	void plusPressed( GuiElement& vElement, const Mocha::ValueList& vValues );

	void minusPressed( GuiElement& vElement, const Mocha::ValueList& vValues );

protected:
	virtual void onScroll( );

	virtual void onRectangleChanged( );

	virtual void onMousePressed( MouseButtonID vButtonID, const Mocha::Vector2& vPoint );

	virtual void onMouseReleased( MouseButtonID vButtonID, const Mocha::Vector2& vPoint );

	virtual void onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint );

	virtual void onDraw( Brush& vBrush ) const;

public:
	ScrollWidget( GuiManager* vManager );

	virtual ~ScrollWidget( );

	virtual Mocha::String getClassName( ) const;

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	/// Sets the relative size of the slider rectangle
	/*! \param vSize The size of the slider rectangle as a value from 0.0 to 1.0 */
	void setSliderSize( float vSize );

	/// Gets the relative size of the slider rectangle
	/*! \return A value from 0.0 to 1.0, representing the size of the slider rectangle */
	float getSliderSize( ) const;

	/// Change the value by the min step amount
	void stepMinus( );

	/// Change the value by the max step amount
	void stepPlus( );

	/// Sets the amount to change the value when the plus/minus button is pressed
	void setStep( float vValue );

	/// Gets the amount to change the value when the plus/minus button is pressed
	float getStep( ) const;

	/// Sets the range to scale the value by (min,max)
	void setRange( const Mocha::Vector2& vValue );

	/// Gets the range to scale the value by (min,max)
	const Mocha::Vector2& getRange( ) const;

	/// Sets the value of the scroll
	void setValue( float vValue );

	/// Gets the value of the scroll
	float getValue( ) const;

	static Widget* factory( GuiManager* vManager );
};

}

#endif
