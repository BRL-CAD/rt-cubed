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

#ifndef GUI_GUIWINDOW_H
#define GUI_GUIWINDOW_H

#include <sstream>
#include <list>

#include "Mocha/Object.h"
#include "Mocha/Vector2.h"
#include "Mocha/Rectangle.h"
#include "Mocha/WeakRefPointer.h"

#include "RBGui/InputDefines.h"
#include "RBGui/WindowAnimator.h"
#include "RBGui/WindowFader.h"
#include "RBGui/Texture.h"

#include "RBGui/Widgets/ContainerWidget.h"

namespace RBGui
{

//--------------------------------
class GuiManager;
class Brush;
class Font;

//--------------------------------
enum WindowState
{
	WINDOWSTATE_CLOSED = 0,
	WINDOWSTATE_NORMAL,
	WINDOWSTATE_HIDDEN
};

//--------------------------------
/// A 2D window that contains a layout of widgets and can be faded or animated
class GUI_EXPORT Window : public GuiElement
{
private:
	enum MouseMode
	{
		MOUSEMODE_NONE = 0,
		MOUSEMODE_MOVING,
		MOUSEMODE_RESIZING
	};

	Mocha::RefPointer<Texture> mTarget;
	
	Mocha::RefPointer<ContainerWidget> mRoot;

	Mocha::RefPointer<WindowAnimator> mAnimator;

	Mocha::RefPointer<WindowFader> mFader;

	Mocha::WeakRefPointer<Widget> mFocused;

	GuiManager* mManager;

	MouseMode mMouseMode;

	bool mTargetDirty;

	bool mHideOnClose;

	Mocha::Vector2 mMinSize;

	Mocha::Vector2 mMaxSize;

	Mocha::Rectangle mRectangle;

	Mocha::Rectangle mClientRect;

	Mocha::String mTag;

	Mocha::String mBorder;

	Mocha::String mTheme;

	Mocha::String mText;

	Mocha::String mName;

	WindowState mState;

	bool mDirty;

	bool mBorderVisible;

	bool mClosePressed;

	bool mCloseDown;

	bool mCloseable;

	bool mMovable;

	bool mModal;

	bool mResizeable;

	float mOpacity;

	void prepareTarget( );

	Border* getRenderBorder( ) const;

	Font* getRenderFont( ) const;

	Theme* getRenderTheme( ) const;

	void drawBorder( Brush& vBrush ) const;

	bool pointInTitle( const Border& vBorder, const Mocha::Vector2& vPoint ) const;

	bool pointInResizeCorner( const Border& vBorder, const Mocha::Vector2& vPoint ) const;

	void checkRectSize( );

	void destroyTarget( );

public:
	Window( GuiManager* vManager );

	virtual ~Window( );

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	/// Sets the currently focused widget
	void setFocused( Widget* vWidget );

	/// Sets whether or not the window should hide instead of close when the close button is pressed
	void setHideOnClose( bool vWhich );

	/// Gets whether or not the window should hide instead of close when the close button is pressed
	bool getHideOnClose( ) const;

	/// Sets the name of the theme to use
	void setTheme( const Mocha::String& vName );

	/// Gets the name of the theme to use
	const Mocha::String& getTheme( ) const;

	/// Sets the tag of the window, which is just a string of text that can be used to identify it as part of some group
	void setTag( const Mocha::String& vTag );

	/// Gets the tag of the window
	const Mocha::String& getTag( ) const;

	/// Called by the GuiManager to update the cursor icon
	void updateCursor( const Mocha::Vector2& vPoint );

	/// Sets whether or not the window is modal
	void setModal( bool vWhich );

	/// Gets whether or not the window is modal
	bool getModal( ) const;

	/// Sets the window fader to use for the window
	void setFader( WindowFader* vFader );

	/// Gets the window fader assigned to the window
	WindowFader* getFader( ) const;

	/// Sets the window animator to use for the window
	void setAnimator( WindowAnimator* vAnimator );

	/// Gets the window animator assigned to the window
	WindowAnimator* getAnimator( ) const;

	/// Sets the minimum size of the window
	void setMinSize( const Mocha::Vector2& vValue );

	/// Gets the minimum size of the window
	const Mocha::Vector2& getMinSize( ) const;

	/// Sets the maximum size of the window
	void setMaxSize( const Mocha::Vector2& vValue );

	/// Gets the maximum size of the window
	const Mocha::Vector2& getMaxSize( ) const;

	/// Gets the screen-space position of a point inside the window
	/*! \param vWindowPos A point, relative from the top left corner of the window
		\return The point translated into screen space */
	Mocha::Vector2 getScreenPosition( const Mocha::Vector2& vWindowPos );

	/// Handles a mouse pressed event
	void onMousePressed( MouseButtonID vButtonID, const Mocha::Vector2& vPoint, bool vDoubleClick = false );

	/// Handles a mouse released event
	void onMouseReleased( MouseButtonID vButtonID, const Mocha::Vector2& vPoint );

	/// Handles a mouse motion event
	void onMouseMotion( const Mocha::Vector2& vRel, const Mocha::Vector2& vPoint );

	/// Handles a mouse wheel scroll event
	void onMouseScrolled( float vAmount, const Mocha::Vector2& vPoint );

	/// Handles a key pressed event
	void onKeyPressed( KeyID vKey );

	/// Handles a key released event
	void onKeyReleased( KeyID vKey );

	/// Handles a focus lost event
	void onFocusLost( );

	/// Handles a focus received event
	void onFocusRecieved( );

	/// Sets the opacity of the window
	void setOpacity( float vValue );

	/// Gets the opacity of the window
	float getOpacity( ) const;

	/// Gets whether or not the window is currently fading
	bool getFading( ) const;

	/// Sets whether or not the window can be moved by the user
	void setMovable( bool vWhich );

	/// Gets whether or not the window can be moved by the user
	bool getMovable( ) const;

	/// Sets whether or not the window can be resized by the user
	void setResizeable( bool vWhich );

	/// Gets whether or not the window can be resized by the user
	bool getResizeable( ) const;

	/// Sets whether or not the window can be closed by the user
	void setCloseable( bool vWhich );

	/// Gets whether or not the window can be closed by the user
	bool getCloseable( ) const;

	/// Sets whether or not the border will be drawn
	void setBorderVisible( bool vWhich );

	/// Gets whether or not the border will be drawn
	bool getBorderVisible( ) const;

	/// Updates the window
	void tick( float vDelta );
	
	/// Gets whether or not the window is currently being resized by the user
	bool getResizing( ) const;

	/// Gets whether or not the window is currently being moved by the user
	bool getMoving( ) const;

	/// Gets whether or not the window will be drawn to the screen
	bool getVisible( ) const;

	/// Centers the window on the screen along the X axis
	void centerX( );

	/// Centers the window on the screen along the Y axis
	void centerY( );

	/// Finds a widget under a point in the window
	/*! \param vPoint The point, relative to the window, to search with
		\return The first widget found under the point, or 0 if no widget was found */
	Widget* findWidgetAtPoint( const Mocha::Vector2& vPoint ) const;

	/// Finds a widget with a given name
	/*! \return The first widget found with the given name, or 0 if no widget was found */
	Widget* findWidget( const Mocha::String& vName ) const;

	/// Signals the window to redraw
	void flagDirty( );

	/// Gets whether or not the window needs to be redrawn
	bool getDirty( );

	/// Resets whether or not the window needs to be redrawn
	void clearDirty( );

	/// Sets the name of the window
	void setName( const Mocha::String& vName );

	/// Gets the name of the window
	const Mocha::String& getName( ) const;

	/// Sets the window text (The text that is drawn in the title bar)
	void setText( const Mocha::String& vText );

	/// Gets the window text (The text that is drawn in the title bar)
	const Mocha::String& getText( ) const;

	/// Sets the screen-space position of the window
	void setPosition( const Mocha::Vector2& vPosition );

	/// Gets the screen-space position of the window
	Mocha::Vector2 getPosition( ) const;

	/// Sets the size of the window in pixels
	void setSize( const Mocha::Vector2& vSize );

	/// Gets the size of the window in pixels
	Mocha::Vector2 getSize( ) const;

	/// Sets the screen-space rectangle of the window
	void setRectangle( const Mocha::Rectangle& vRectangle );

	/// Gets the screen-space rectangle of the window
	const Mocha::Rectangle& getRectangle( ) const;

	/// Gets the client rectangle (The region inside of the border) This rectangle is in window-space (Not screen-space)
	const Mocha::Rectangle& getClientRectangle( ) const;

	/// Draws the window
	void draw( Brush& vBrush );

	/// Sets the name of the border to use for the window
	void setBorder( const Mocha::String& vName );

	/// Gets the name of the boder to use for the window
	const Mocha::String& getBorder( ) const;

	/// Creates a widget and adds it to the window
	/*! \param vName The class name of the widget to create
		\return A pointer to the new widget */
	Widget* createWidget( const Mocha::String& vName );

	/// Shows the window
	void show( );

	/// Closes the window
	void close( );

	/// Hides the window
	void hide( );

	/// Gets the state of the window (See WindowState)
	WindowState getState( ) const;

	/// Gets whether or not the window has been closed
	bool getClosed( ) const;

	/// Updates the client region and forces a redraw of the window contents
	void updateClientRect( );

	/// Gets the root container
	ContainerWidget* getRoot( ) const;

	/// Gets the texture that the window will be drawn to
	Texture* getTarget( ) const;

	/// Gets the GuiManager that owns the window
	GuiManager* getGuiManager( ) const;
};

//--------------------------------
typedef std::list< Mocha::RefPointer<Window> > WindowList;

}

#endif
