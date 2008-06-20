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

#ifndef TOI_DROPLISTWIDGET_H
#define TOI_DROPLISTWIDGET_H

#include <vector>

#include "Mocha/WeakRefPointer.h"

#include "RBGui/Widget.h"
#include "RBGui/Window.h"

#include "RBGui/Widgets/ListWidget.h"

namespace RBGui
{

//--------------------------------
class TextEntryWidget;
class ButtonWidget;

//--------------------------------
/// A drop-list/combo box widget
class GUI_EXPORT DropListWidget : public Widget
{
private:
	typedef std::vector<ListWidgetEntry> EntryList;
	EntryList mEntries;

	TextEntryWidget* mTextEntry;

	ButtonWidget* mDropButton;

	Mocha::WeakRefPointer<Window> mDropWindow;

	int mSelected;

	void onSelectionMade( size_t vIndex );

	void dropButtonPushed( GuiElement& vElement, const Mocha::ValueList& vData );

	void textEntryPushed( GuiElement& vElement, const Mocha::ValueList& vData );

	void entrySelected( GuiElement& vElement, const Mocha::ValueList& vData );

	void textChanged( GuiElement& vElement, const Mocha::ValueList& vData );

	void dropWindowFocusLost( GuiElement& vElement, const Mocha::ValueList& vData );

protected:
	virtual void onDraw( Brush& vBrush ) const;

	virtual void onRectangleChanged( );

	virtual void onTextChanged( );

public:
	DropListWidget( GuiManager* vManager );

	virtual ~DropListWidget( );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual Mocha::String getClassName( ) const;

	/// Sets whether or not the text area of the widget can be edited as a combo-box
	void setEditable( bool vWhich );

	/// Gets whether or not the text area of the widget can be edited as a combo-box
	bool getEditable( ) const;

	/// Adds an entry to the list
	/*! \param vText The text of the entry
		\param vData A pointer to user data to be associated with the entry
		\param vTextData A string of text data to be associated with the entry */
	void addEntry( const Mocha::String& vText, void* vData = 0, const Mocha::String& vTextData = "" );

	/// Sets an entry in the list
	/*! \param vIndex The index of the entry to set
		\param vText The value to set the entry text to
		\param vData A pointer to some user data to associated with the entry
		\param vTextData A string to text data to associate with the entry */
	void setEntry( size_t vIndex, const Mocha::String& vText, void* vData = 0, const Mocha::String& vTextData = "" );

	/// Gets the text of an entry
	const Mocha::String& getEntryText( size_t vIndex ) const;

	/// Gets the text data of an entry
	const Mocha::String& getEntryTextData( size_t vIndex ) const;

	/// Gets a reference to an entry
	const ListWidgetEntry& getEntry( size_t vIndex ) const;

	/// Gets the user data of an entry
	void* getEntryData( size_t vIndex ) const;

	/// Gets the number of entries in the list
	size_t getEntryCount( ) const;

	/// Selects the entry with the given text
	/*! \param vText The text of the entry to select */
	void setSelected( const Mocha::String& vText );

	/// Sets the selected entry
	void setSelected( size_t vIndex );

	/// Gets the currently selected entry
	/*! \return The selected entry index, or -1 if no entry is selected */
	int getSelected( ) const;

	/// Removes all entries from the list
	void clearEntries( );

	static Widget* factory( GuiManager* vManager );
};

}

#endif
