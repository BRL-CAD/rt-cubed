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

#ifndef GUI_EVALUATORWIDGET_H
#define GUI_EVALUATORWIDGET_H

#include "RBGui/Widget.h"

namespace RBGui
{

//--------------------------------
enum EvaluatorWidgetMode
{
	EVALUATORMODE_FLOAT = 0,
	EVALUATORMODE_INTEGER
};

//--------------------------------
class ButtonWidget;
class TextEntryWidget;

//--------------------------------
/// A widget for editing a numeric value
class GUI_EXPORT EvaluatorWidget : public Widget
{
private:
	Mocha::Vector2 mRange;

	float mStep;

	ButtonWidget* mPlusButton;

	ButtonWidget* mMinusButton;

	TextEntryWidget* mTextEntry;

	EvaluatorWidgetMode mMode;

	void raiseEvents( );

	void plusPressed( GuiElement& vElement, const Mocha::ValueList& vValues );

	void minusPressed( GuiElement& vElement, const Mocha::ValueList& vValues );

	void returnPressed( GuiElement& vElement, const Mocha::ValueList& vValues );

protected:
	virtual void onRectangleChanged( );

	virtual void onDraw( Brush& vBrush ) const;

public:
	EvaluatorWidget( GuiManager* vManager );

	virtual ~EvaluatorWidget( );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual Mocha::String getClassName( ) const;

	/// Sets the value mode of the evaluator. See EvaluatorWidgetMode
	void setMode( EvaluatorWidgetMode vMode );

	/// Gets the value mode of the evaluator. See EvaluatorWidgetMode
	EvaluatorWidgetMode getMode( ) const;

	/// Sets the amount of change to be used when the plus/minus button is pressed
	void setStep( float vValue );

	/// Gets the amount of change to be used when the plus/minus button is pressed
	float getStep( ) const;

	/// Sets the value of the evaluator
	void setValue( float vValue );

	/// Gets the value of the evaluator
	float getValue( ) const;

	/// Sets the allowable range of values (min,max)
	void setRange( const Mocha::Vector2& vValue );

	/// Gets the maximum allowed value (min,max)
	const Mocha::Vector2& getRange( ) const;

	/// Increments the value by the step amount
	void increment( );

	/// Decrements the value by the step amount
	void decrement( );

	static Widget* factory( GuiManager* vManager );
};

}

#endif
