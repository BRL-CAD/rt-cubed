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

#ifndef OLIVIA_MENUGUIWIDGET_H
#define OLIVIA_MENUGUIWIDGET_H

#include "RBGui/Widget.h"

#include "MenuEntry.h"

namespace RBGui
{

//--------------------------------
/// A widget that displays a list of menu entries
class GUI_EXPORT MenuWidget : public Widget
{

friend class MenuEntryWidget;

private:
	MenuEntry mRoot;

	void adjustSize( );

	void updateMenus( );

	MenuEntry* getEntry( const Mocha::String& vName, Mocha::String& vRootName );

	void entrySelected( const Mocha::String& vName );

	void deselectAll( );

protected:
	virtual void onRectangleChanged( );

	virtual void onDraw( Brush& vBrush ) const;

public:
	MenuWidget( GuiManager* vManager );

	virtual ~MenuWidget( );

	virtual Mocha::String getClassName( ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	/// Adds a menu entry
	/*! \param vName The full hierarchy path of the entry, separated by periods. For example: "File.Save As" / "File.New.Project" / "Help.About"
		\param vID A string ID to associate with this menu entry */
	void addEntry( const Mocha::String& vName, const Mocha::String& vID );

	/// Clears all entries from the menu
	void clear( );

	static Widget* factory( GuiManager* vManager );
};

}

#endif
