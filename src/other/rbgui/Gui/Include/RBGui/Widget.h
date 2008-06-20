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

#ifndef GUI_GUIWIDGET_H
#define GUI_GUIWIDGET_H

#include "Mocha/Object.h"
#include "Mocha/Vector2.h"
#include "Mocha/Rectangle.h"
#include "Mocha/RefPointer.h"
#include "Mocha/DataSection.h"

#include "RBGui/InputDefines.h"
#include "RBGui/GuiElement.h"
#include "RBGui/Border.h"
#include "RBGui/Theme.h"

namespace RBGui
{

//--------------------------------
class GuiManager;
class Window;
class Brush;
class Font;

//--------------------------------
class Widget;
typedef std::vector< Mocha::RefPointer<Widget> > WidgetList;

//--------------------------------
/// A single element in a GUI layout
class GUI_EXPORT Widget : public GuiElement
{

friend class Window;

private:
	Mocha::RefPointer<Font> mFont;

	WidgetList mChildren;

	Window* mWindow;

	Widget* mParent;

	GuiManager* mManager;

	Mocha::Rectangle mRectangle;

	Mocha::Rectangle mScreenRect;

	Mocha::Rectangle mClientRect;

	Mocha::Color mColor;

	Mocha::Vector2 mScroll;

	Mocha::String mBorderName;

	Mocha::String mFontName;

	Mocha::String mBorderState;

	Mocha::String mText;

	Mocha::String mName;

	bool mScrollable;

	bool mVisible;

	bool mGenerated;

	bool mBorderVisible;

	bool mEnabled;

	void setParent( Widget* vWidget );

protected:
	void updateScreenRect( );

	void setBorderState( const Mocha::String& vName );

	const Mocha::String& getBorderState( );

	bool getLocalPointInside( const Mocha::Vector2& vPoint ) const;

	void attach( Widget* vWidget );

	void detach( Widget* vWidget );

	virtual void onDraw( Brush& vBrush ) const;

	virtual void onTextChanged( );

	virtual void onRectangleChanged( );

	virtual void onColorChanged( );

	virtual void onMouseEnter( const Mocha::Vector2& vPoint );

	virtual void onMouseLeave( );

	virtual void onDoubleClick( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint );

	virtual void onMouseScrolled( float vAmount );

	virtual void onKeyPressed( KeyID vKeyID );

	virtual void onKeyReleased( KeyID vKeyID );

	virtual void onFocusRecieved( );

	virtual void onFocusLost( );

	/// Gets a version of the color that is half transparent if the widget is disabled
	Mocha::Color getDerivedColor( const Mocha::Color& vColor ) const;

public:
	Widget( GuiManager* vManager );

	virtual ~Widget( );

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	/// Gets the theme that will be used to render the widget
	Theme* getRenderTheme( ) const;

	/// Gets the border that will be used to render the widget
	Border* getRenderBorder( ) const;

	/// Gets the font that will be used to render the widget
	Font* getRenderFont( ) const;

	/// Gets the color that will be used to render the widget
	Mocha::Color getRenderColor( ) const;

	/// Gets the name of the class of this widget
	virtual Mocha::String getClassName( ) const;

	/// Returns whether or not the widget implements the ContainerWidget interface
	virtual bool getContainer( ) const;

	/// Gets the cursor that should be used when the mouse moves over this widget. See CursorType
	virtual CursorType getCursor( ) const;

	/// Sets whether or not the widget is enabled
	void setEnabled( bool vWhich );

	/// Gets whether or not the widget is enabled
	bool getEnabled( ) const;

	/// Sets the scroll amount. This is the offset that all child widgets will be drawn with
	void setScroll( const Mocha::Vector2& vScroll );

	/// Gets the scroll amount. This is the offset that all child widgets will be drawn with
	const Mocha::Vector2& getScroll( ) const;

	/// Handles a mouse enter event
	void handleMouseEnter( const Mocha::Vector2& vPoint );

	/// Handles a mouse leave event
	void handleMouseLeave( );

	/// Handles a double click event
	void handleDoubleClick( MouseButtonID vID, const Mocha::Vector2& vPoint );

	/// Handles a mouse pressed event
	void handleMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint );

	/// Handles a mouse released event
	void handleMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint );

	/// Handles a mouse motion event
	void handleMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint );

	/// Handles a mouse wheel scroll event
	void handleMouseScrolled( float vAmount );

	/// Handles a key pressed event
	void handleKeyPressed( KeyID vKeyID );

	/// Handles a key released event
	void handleKeyReleased( KeyID vKeyID );

	/// Handles a focus received event
	void handleFocusRecieved( );

	/// Handles a focus lost event
	void handleFocusLost( );

	/// Gets the list of child widgets
	const WidgetList& getChildren( ) const;

	/// Sets whether or not the widget should be drawn with the parent's offset
	void setScrollable( bool vWhich );

	/// Gets whether or not the widget should be drawn with the parent's offset
	bool getScrollable( ) const;

	/// Sets whether or not this widget was automatically generated by it's parent
	void setGenerated( bool vWhich );

	/// Gets whether or not this widget was automatically generated by it's parent
	bool getGenerated( ) const;

	/// Sets whether or not the border will be drawn
	void setBorderVisible( bool vWhich );

	/// Gets whether or not the border will be drawn
	bool getBorderVisible( ) const;

	/// Sets the font to use by name (From the theme)
	void setFont( const Mocha::String& vFont );

	/// Gets the theme font
	const Mocha::String& getFont( ) const;

	/// Sets the name of the border to use
	/*! \param vName The name of the border in the theme to use */
	void setBorder( const Mocha::String& vName );

	/// Gets the name of the border to use
	/*! \return The name of the border in the theme to use */
	const Mocha::String& getBorder( ) const;

	/// Find a widget under a point that is relative to the parent window
	/*! \param vPoint A point, relative to the top left corner of the window
		\return The first widget found under the point, or 0 if no widget was found */
	Widget* findWidgetAtPoint( const Mocha::Vector2& vPoint ) const;

	/// Recursively finds a widget with the given name
	/*! \return A pointer to the first widget found with the given name, or 0 if no widget was found */
	Widget* findWidget( const Mocha::String& vName ) const;

	/// Finds a child with the given name
	/*! \return A pointer to the child widget with the given name, or 0 if no child was found */
	Widget* findChild( const Mocha::String& vName ) const;

	/// Gets the GuiManager that owns the widget
	GuiManager* getGuiManager( ) const;

	/// Signals the widget to redraw
	void flagDirty( );

	/// Sets the name of the widget
	void setName( const Mocha::String& vName );

	/// Gets the name of the widget
	const Mocha::String& getName( ) const;

	/// Sets the color to use for the widget. How this color is used depends on the widget
	void setColor( const Mocha::Color& vColor );

	/// Gets the color to use for the widget. How this color is used depends on the widget
	const Mocha::Color& getColor( ) const;

	/// Sets the text of the widget. How this text is used depends on the widget
	void setText( const Mocha::String& vText );

	/// Gets the text of the widget. How this text is used depends on the widget
	const Mocha::String& getText( ) const;

	/// Sets the position of the widget, in pixels
	/*! \param vPosition The position of the widget to use, relative to the parent */
	void setPosition( const Mocha::Vector2& vPosition );

	/// Gets the position of the widget, in pixels
	/*! \return vPosition The position of the widget, relative to the parent */
	Mocha::Vector2 getPosition( ) const;

	/// Sets the size of the widget, in pixels
	void setSize( const Mocha::Vector2& vSize );

	/// Gets the size of the widget, in pixels
	Mocha::Vector2 getSize( ) const;

	/// Sets the rectangle of the widget
	void setRectangle( float vX, float vY, float vWidth, float vHeight );

	/// Sets the rectangle of the widget
	/*! \param vRectangle The rectangle of the widget, relative to the parent */
	void setRectangle( const Mocha::Rectangle& vRectangle );

	/// Gets the rectangle of the widget
	/*! \return The rectangle of the widget, relative to the parent */
	const Mocha::Rectangle& getRectangle( ) const;

	/// Gets the screen rectangle (The rectangle relative to the parent window)
	/*! \return The screen rectangle (The rectangle relative to the parent window) */
	const Mocha::Rectangle& getScreenRectangle( ) const;

	/// Gets the client rectangle, used for drawing
	/*! \return The client rectangle. This is the region inside the border of the screen rectangle */
	const Mocha::Rectangle& getClientRectangle( ) const;

	/// Gets the window that owns this widget
	/*! \return The owning window, or 0 if there is no window that owns the widget */
	Window* getWindow( ) const;

	/// Gets the parent of the widget
	/*! \return The parent widget, or 0 if there is no parent */
	Widget* getParent( ) const;

	/// Sets whether or not the widget is visible
	void setVisible( bool vWhich );

	/// Gets whether or not the widget is visible
	bool getVisible( ) const;

	/// Removes all children of the widget
	void clearChildren( );

	/// Draws the widget
	void draw( Brush& vBrush ) const;

	/// Saves the widget and all children to a data section
	void save( Mocha::DataSection& vSection ) const;

	/// Reads the widget and any children from a data section
	void load( const Mocha::DataSection& vSection );
};

}

#endif
