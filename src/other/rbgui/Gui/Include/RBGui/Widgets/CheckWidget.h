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

#ifndef GUI_CHECKWIDGET_H
#define GUI_CHECKWIDGET_H

#include "RBGui/Widget.h"

namespace RBGui
{

/// A checkbox widget
class GUI_EXPORT CheckWidget : public Widget
{
protected:
	Mocha::Color mColor;

	bool mChecked;

	// Event handlers

	virtual void onChanged( );

	virtual void onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint ); 

	virtual void onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint ); 

	virtual void onDraw( Brush& vBrush ) const;

public:
	CheckWidget( GuiManager* vManager );

	virtual ~CheckWidget( );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual Mocha::String getClassName( ) const;

	/// Sets whether or not the box is checked
	void setChecked( bool vWhich );

	/// Gets whether or not the box is checked
	bool getChecked( ) const;

	static Widget* factory( GuiManager* vManager );
};

}

#endif
