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


#ifndef TOI_LISTWIDGET_H
#define TOI_LISTWIDGET_H

#include <vector>

#include "RBGui/Widget.h"

namespace RBGui
{

//--------------------------------
class ListWidgetEntry
{
public:
	inline ListWidgetEntry( const Mocha::String& vText, void* vData = 0, const Mocha::String& vTextData = "", const Mocha::String& vIcon = "" )
		: textData( vTextData ), selected( false ), text( vText ), icon( vIcon ), data( vData )
	{
		// ...
	}

	inline ListWidgetEntry( )
		: selected( false ), data( 0 )
	{
		// ...
	}

	Mocha::String textData;

	Mocha::String text;

	Mocha::String icon;

	bool selected;

	void* data;
};

//--------------------------------
class ScrollWidget;

//--------------------------------
/// A widget that displays a list of entries that can be selected
class GUI_EXPORT ListWidget : public Widget
{
private:
	typedef std::vector<ListWidgetEntry> EntryList;
	EntryList mEntries;

	ScrollWidget* mScrollBar;

	int mSelected;

	bool mMultiSelect;

	bool mDrawIcons;

	float getOffsetY( Font* vFont ) const;

	void adjustScrollBarSteps( );

	void onSelected( int vIndex );

	void onUnselected( int vIndex );

protected:
	int pickEntry( const Mocha::Vector2& vPoint );

	virtual void onRectangleChanged( );

	virtual void onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint );

	virtual void onDraw( Brush& vBrush ) const;

public:
	ListWidget( GuiManager* vManager );

	virtual ~ListWidget( );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual Mocha::String getClassName( ) const;

	/// Sets the scroll value of the scrollbar
	void setScroll( float vAmount );

	/// Sets whether or not the list should draw the entry icons
	void setDrawIcons( bool vWhich );

	/// Gets whether or not the entry icons will be drawn
	bool getDrawIcons( ) const;

	/// Sets whether or not the scroll bar is visible
	void setScrollVisible( bool vWhich );

	/// Gets whether or not the scroll bar is visible
	bool getScrollVisible( ) const;

	/// Sets whether or not multiple entries can be selected at the same time
	void setMultiSelect( bool vWhich );

	/// Gets whether or not multiple entries can be selected at the same time
	bool getMultiSelect( ) const;

	/// Clears all entries from the list
	void clearEntries( );

	/// Adds a new entry to the list
	/*! \param vText The entry text
		\param vData The user data to associate with the entry
		\param vTextData A string of text to assicate with the entry
		\param vIcon The theme image name to use for the icon of this entry */
	void addEntry( const Mocha::String& vText, void* vData = 0, const Mocha::String& vTextData = "", const Mocha::String& vIcon = "" );

	/// Sets an entry of the list
	/*! \param vIndex The index of the entry to set
		\param vText The entry text
		\param vData The user data to associate with the entry
		\param vTextData A string of text to assicate with the entry
		\param vIcon The theme image name to use for the icon of this entry */
	void setEntry( size_t vIndex, const Mocha::String& vText, void* vData = 0, const Mocha::String& vTextData = "", const Mocha::String& vIcon = "" );

	/// Removes an entry from the list
	void removeEntry( size_t vIndex );

	/// Swaps the position of two entries in the list
	void swapEntryOrder( size_t vIndex1, size_t vIndex2 );

	/// Gets the text of an entry
	const Mocha::String& getEntryText( size_t vIndex ) const;

	/// Gets the text data of an entry
	const Mocha::String& getEntryTextData( size_t vIndex ) const;

	/// Gets a reference to an entry in the list
	const ListWidgetEntry& getEntry( size_t vIndex ) const;

	/// Gets whether or not an entry is selected
	bool getEntrySelected( size_t vIndex ) const;

	/// Sets whether or not an entry is selected
	/*! \param vIndex The index of the entry
		\param vWhich Whether or not the entry should be selected */
	void setEntrySelected( size_t vIndex, bool vWhich );

	/// Gets the user data of an entry
	void* getEntryData( size_t vIndex ) const;

	/// Gets the index of the most recently selected entry
	/*! \return The index of the most recently selected entry, or -1 if no entry is selected */
	int getSelected( ) const;

	/// Gets the number of entries in the list
	size_t getEntryCount( ) const;

	/// De-selects all entries in the list
	void deselectAll( );

	static Widget* factory( GuiManager* vManager );
};

}

#endif

