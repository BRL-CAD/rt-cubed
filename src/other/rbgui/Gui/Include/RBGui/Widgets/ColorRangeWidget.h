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

#ifndef GUI_COLORRANGEWIDGET_H
#define GUI_COLORRANGEWIDGET_H

#include "RBGui/Widget.h"

namespace RBGui
{

//--------------------------------
class ColorRange
{
public:
	inline ColorRange( const Mocha::Color& vColor1, const Mocha::Color& vColor2 )
		: color1( vColor1 ), color2( vColor2 )
	{
		// ...
	}

	inline ColorRange( )
	{
		// ...
	}

	Mocha::Color color1;

	Mocha::Color color2;
};

//--------------------------------
class GUI_EXPORT ColorRangeWidget : public Widget
{
private:
	typedef std::vector<ColorRange> RangeList;
	RangeList mRanges;

	GradientType mGradientType;

	bool mDragging;

	float mValue;

	void updateValue( const Mocha::Vector2& vPoint );

	void drawGradients( Brush& vBrush ) const;

protected:
	virtual void onDraw( Brush& vBrush ) const;

	virtual void onRectangleChanged( );

public:
	ColorRangeWidget( GuiManager* vManager );

	virtual ~ColorRangeWidget( );

	virtual void onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint ); 

	virtual void onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint );

	virtual void onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint );

	virtual Mocha::String getClassName( ) const;

	void onChanged( );

	void addRange( const Mocha::Color& vColor1, const Mocha::Color& vColor2 );

	void addRange( const ColorRange& vRange );

	const ColorRange& getRange( size_t vIndex ) const;

	size_t getRangeCount( ) const;

	void clear( );

	void setValue( float vValue );

	float getValue( ) const;

	static Widget* factory( GuiManager* vManager );
};

}

#endif
