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

#ifndef OLIVIA_TEXTENTRYGUIWIDGET_H
#define OLIVIA_TEXTENTRYGUIWIDGET_H

#include "RBGui/GuiDefines.h"
#include "RBGui/Widget.h"

namespace RBGui
{

//--------------------------------
class ScrollWidget;

//--------------------------------
/// A widget that provides an optionally scrollable text entry field
class GUI_EXPORT TextEntryWidget : public Widget
{
private:
	int mCursorPos;

	int mSelectStart;

	int mSelectEnd;

	int mSelectOrigin;

	bool mWrap;

	bool mLocked;

	bool mPassword;

	bool mDrawCursor;

	bool mMultiLine;

	bool mNumericOnly;

	bool mEnableReturn;

	bool mDragging;

	ScrollWidget* mScrollBar;

	Mocha::Rectangle mTextRect;

	Mocha::String mPasswordText;

	LineInfoList mLines;

	int mWrapWidth;

	int mTextHeight;

	int mOffsetX;

	int mOffsetY;

	Mocha::Vector2 mCursorLocation;

	void insertText( const Mocha::String& vText );

	void removeText( int vStart, int vLength );

	void updateTextHeight( );

	void updateTextRect( );

	void updateCursorLocation( );

	void processText( );

	void moveCursorY( float vDir, bool vSelect );

	int getCharacterIndexAtPixel( int vX, int vY );

	void copy( ) const;

	void paste( );

	void findLineStart( bool vShift );

	void findLineEnd( bool vShift );

	void setSelectionEnd( int vPos );

	void setSelectionStart( int vPos );

	void resetSelection( );

	void textScrolled( GuiElement& vElement, const Mocha::ValueList& vData );

	void adjustScrollY( );

	void onReturnPressed( );

	void updatePasswordText( );

	void scrollTextX( int vAmount );

	void scrollTextY( int vAmount );

	const Mocha::String& getRealText( ) const;

protected:
	virtual void onTextChanged( );

	virtual void onRectangleChanged( );

	virtual void onDraw( Brush& vBrush ) const;

	virtual void onFocusRecieved( );

	virtual void onFocusLost( );

	virtual void onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint ); 

	virtual void onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint );

	virtual void onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint );

	virtual void onKeyPressed( KeyID vKey );

public:
	TextEntryWidget( GuiManager* vManager );

	virtual ~TextEntryWidget( );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual CursorType getCursor( ) const;

	virtual Mocha::String getClassName( ) const;

	/// Sets the Y scroll value
	void setScrollY( float vValue );

	/// Gets the Y scroll value
	float getScrollY( ) const;

	/// Sets whether or not the return button can be pressed
	void setEnableReturn( bool vWhich );

	/// Gets whether or not the return button can be pressed
	bool getEnableReturn( ) const;

	/// Sets whether or not the the text can be changed
	void setLocked( bool vWhich );

	/// Gets whether or not the the text can be changed
	bool getLocked( ) const;

	/// Sets whether or not the text is restricted to numeric values
	void setNumericOnly( bool vWhich );

	/// Gets whether or not the text is restricted to numeric values
	bool getNumericOnly( ) const;

	/// Sets whether or not the text can be edited across multiple lines
	void setMultiLine( bool vWhich );

	/// Gets whether or not the text can be edited across multiple lines
	bool getMultiLine( ) const;

	/// Sets whether or not the text is rendered as a password field
	void setPassword( bool vWhich );

	/// Sets whether or not the text is rendered as a password field
	bool getPassword( ) const;

	/// Sets whether or not the text should word-wrap
	void setWrap( bool vWhich );

	/// Gets whether or not the text should word-wrap
	bool getWrap( ) const;

	/// Sets the position of the cursor
	/*! \param vPos The index of the character to insert the cursor after
		\param vSelect Whether or not to select text from the current cursor position to the new position */
	void setCursorPos( int vPos, bool vSelect = false );

	/// Gets the index of the character that the cursor is at
	int getCursorPos( ) const;

	static Widget* factory( GuiManager* vManager );
};

}

#endif
