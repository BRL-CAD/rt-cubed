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

#ifndef OLIVIA_MENUENTRYGUIWIDGET_H
#define OLIVIA_MENUENTRYGUIWIDGET_H

#include "Mocha/WeakRefPointer.h"

#include "RBGui/Widget.h"
#include "RBGui/Window.h"

#include "RBGui/Widgets/MenuWidget.h"

namespace RBGui
{

class MenuEntryWidget : public Widget
{
private:
	Mocha::WeakRefPointer<MenuWidget> mMenu;

	Mocha::WeakRefPointer<Window> mDropWindow;

	TextAlignmentMode mTextAlignMode;

	Mocha::StringList mEntries;

	bool mSubMenu;

	bool mSelected;

	void createSubMenu( MenuEntry* vEntry );

	void fillSubMenu( MenuEntry* vEntry );

	MenuEntry* getEntry( ) const;

	// Event handlers

	virtual void onTextChanged( );

	virtual void onMouseEnter( const Mocha::Vector2& vPoint );

	virtual void onMouseLeave( );

	virtual void onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint );

	virtual void onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint );

	virtual void onDraw( Brush& vBrush ) const;

public:
	MenuEntryWidget( GuiManager* vManager, MenuWidget* vMenu );

	virtual ~MenuEntryWidget( );

	void deselectSiblings( );

	void setSelected( bool vWhich );

	bool getSelected( ) const;

	void onMenuClosed( );

	void setSubMenu( bool vWhich );

	bool getSubMenu( ) const;

	void setTextAlignment( TextAlignmentMode vAlign );
};

}

#endif
