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

#ifndef GUI_COLORSELECTWIDGET_H
#define GUI_COLORSELECTWIDGET_H

#include "Mocha/Color.h"
#include "RBGui/Widget.h"
#include "Mocha/WeakRefPointer.h"
#include "RBGui/Window.h"

namespace RBGui
{

//--------------------------------
class ButtonWidget;
class RectangleWidget;
class ColorRangeWidget;
class HSVWidget;

//--------------------------------
/// A widget for selecting a color visually
class GUI_EXPORT ColorSelectWidget : public Widget
{

friend class ColorSelectDropButtonSignal;

private:
	ButtonWidget* mDropButton;

	RectangleWidget* mColorRect;

	RectangleWidget* mDropRect;

	ColorRangeWidget* mHueRange;

	ColorRangeWidget* mAlphaRange;

	Mocha::WeakRefPointer<Window> mDropWindow;

	HSVWidget* mDropHSV;

	// Event handlers

	virtual void onRectangleChanged( );

	virtual void onColorChanged( );

	virtual void onDraw( Brush& vBrush ) const;

	void dropButtonPressed( GuiElement& vElement, const Mocha::ValueList& vValues );

	void hsvPicked( GuiElement& vElement, const Mocha::ValueList& vValues );

	void hueChanged( GuiElement& vElement, const Mocha::ValueList& vValues );

	void alphaChanged( GuiElement& vElement, const Mocha::ValueList& vValues );

	void dropFocusLost( GuiElement& vElement, const Mocha::ValueList& vValues );

	void updateDropWidgets( );

public:
	ColorSelectWidget( GuiManager* vManager );

	virtual ~ColorSelectWidget( );

	virtual Mocha::String getClassName( ) const;

	static Widget* factory( GuiManager* vManager );
};

}

#endif
