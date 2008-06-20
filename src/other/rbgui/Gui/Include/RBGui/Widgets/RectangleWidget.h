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

#ifndef GUI_RECTANGLEWIDGET_H
#define GUI_RECTANGLEWIDGET_H

#include "RBGui/Widget.h"

namespace RBGui
{

//--------------------------------
enum RectangleStyle
{
	RECTANGLE_OUTLINE = 0,
	RECTANGLE_FILLED
};

//--------------------------------
/// A widget that draws a rectangle with an optional checkered background
class GUI_EXPORT RectangleWidget : public Widget
{
private:
	bool mCheckered;

	RectangleStyle mStyle;

protected:
	virtual void onDraw( Brush& vBrush ) const;

public:
	RectangleWidget( GuiManager* vManager );

	virtual ~RectangleWidget( );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual Mocha::String getClassName( ) const;

	/// Sets whether or not the rectangle should be drawn with a checkered background
	void setCheckered( bool vWhich );

	/// Gets whether or not the rectangle will be drawn with a checkered background
	bool getCheckered( ) const;

	/// Sets the style of the rectangle. See RectangleStyle
	void setStyle( RectangleStyle vStyle );

	/// Gets the style of the rectangle. See RectangleStyle
	RectangleStyle getStyle( ) const;

	static Widget* factory( GuiManager* vManager );
};

}

#endif
