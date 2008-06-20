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

#include "RBGui/Window.h"
#include "RBGui/Core.h"

namespace RBGui
{

//--------------------------------
Window::Window( GuiManager* vManager )
: mDirty( true ), mTargetDirty( true ), mHideOnClose( false ), mClosePressed( false ), mMouseMode( MOUSEMODE_NONE ), mManager( vManager ), mModal( false ),
  mState( WINDOWSTATE_HIDDEN ), mBorderVisible( true ), mCloseable( true ), mOpacity( 0.0f ), mCloseDown( false ), mMovable( true ), mResizeable( true )
{
	// Create root widget

	mRoot = new ContainerWidget( vManager );
	mRoot->mManager = mManager;
	mRoot->mWindow = this;

	mRoot->setBorderVisible( false );
}

//--------------------------------
Window::~Window( )
{
	destroyTarget( );
}

//--------------------------------
void Window::setTag( const Mocha::String& vTag )
{
	mTag = vTag;
}

//--------------------------------
const Mocha::String& Window::getTag( ) const
{
	return mTag;
}

//--------------------------------
void Window::setModal( bool vWhich )
{
	mModal = vWhich;
}

//--------------------------------
bool Window::getModal( ) const
{
	return mModal;
}

//--------------------------------
void Window::centerX( )
{
	Mocha::Vector2 screenSize = getGuiManager( )->getBrush( ).getScreenSize( );
	setPosition( Mocha::Vector2( (screenSize.x/2)-(mRectangle.getWidth( )/2), mRectangle.top ) );
}

//--------------------------------
void Window::centerY( )
{
	Mocha::Vector2 screenSize = getGuiManager( )->getBrush( ).getScreenSize( );
	setPosition( Mocha::Vector2( mRectangle.left, (screenSize.y/2)-(mRectangle.getHeight( )/2) ) );
}

//--------------------------------
bool Window::getResizing( ) const
{
	return (mMouseMode == MOUSEMODE_RESIZING);
}

//--------------------------------
bool Window::getMoving( ) const
{
	return (mMouseMode == MOUSEMODE_MOVING);
}

//--------------------------------
void Window::updateCursor( const Mocha::Vector2& vPoint )
{
	CursorManager* cursorManager = getGuiManager( )->getCursorManager( );
	if ( cursorManager )
	{
		CursorType type = CURSOR_DEFAULT;

		switch ( mMouseMode )
		{
		case MOUSEMODE_NONE:
			{
				Border* border = getRenderBorder( );
				if ( border && mResizeable && pointInResizeCorner( *border, vPoint ) )
					type = CURSOR_RESIZE;
				else
				{
					Widget* w = findWidgetAtPoint( vPoint );
					if ( w )
						type = w->getCursor( );
				}
			}
			break;

		case MOUSEMODE_RESIZING:
			type = CURSOR_RESIZE;
			break;

		case MOUSEMODE_MOVING:
			type = CURSOR_DEFAULT;
			break;
		}

		cursorManager->setCursor( type );
	}
}

//--------------------------------
void Window::setMinSize( const Mocha::Vector2& vValue )
{
	mMinSize = vValue;
}

//--------------------------------
const Mocha::Vector2& Window::getMinSize( ) const
{
	return mMinSize;
}

//--------------------------------
void Window::setMaxSize( const Mocha::Vector2& vValue )
{
	mMaxSize = vValue;
}

//--------------------------------
const Mocha::Vector2& Window::getMaxSize( ) const
{
	return mMaxSize;
}

//--------------------------------
void Window::setFader( WindowFader* vFader )
{
	mFader = vFader;
}

//--------------------------------
WindowFader* Window::getFader( ) const
{
	return mFader;
}

//--------------------------------
void Window::setAnimator( WindowAnimator* vAnimator )
{
	mAnimator = vAnimator;
}

//--------------------------------
WindowAnimator* Window::getAnimator( ) const
{
	return mAnimator;
}

//--------------------------------
Mocha::Vector2 Window::getScreenPosition( const Mocha::Vector2& vWindowPos )
{
	return mRectangle.getPosition( ) + vWindowPos;
}

//--------------------------------
void Window::setFocused( Widget* vWidget )
{
	if ( mFocused != vWidget )
	{
		if ( mFocused )
			mFocused->handleFocusLost( );

		mFocused = vWidget;
		if ( mFocused )
			mFocused->handleFocusRecieved( );
	}
}

//--------------------------------
bool Window::pointInTitle( const Border& vBorder, const Mocha::Vector2& vPoint ) const
{
	// See if this is an intersection with the title bar

	Mocha::Rectangle r;

	r.setHeight( vBorder.getPart( BORDER_TOP ).getHeight( ) );
	r.setWidth( mRectangle.getWidth( ) -
			   (vBorder.getPart( BORDER_TOPLEFT ).getWidth( ) +
			    vBorder.getPart( BORDER_TOPRIGHT).getWidth( )) );

	r.setPosition( vBorder.getPart( BORDER_TOPLEFT ).getWidth( ), 0 );

	// See if the point is inside the bar

	return r.pointInside( vPoint );
}

//--------------------------------
bool Window::pointInResizeCorner( const Border& vBorder, const Mocha::Vector2& vPoint ) const
{
	// See if this is an intersection with the resize corner

	Mocha::Rectangle r;
	r.setHeight( vBorder.getPart( BORDER_BOTTOMRIGHT ).getHeight( ) );
	r.setWidth( vBorder.getPart( BORDER_BOTTOMRIGHT ).getWidth( ) );

	r.setPosition( mRectangle.getWidth( ) - r.getWidth( ),
				   mRectangle.getHeight( ) - r.getHeight( ) );

	// Make sure point is inside corner, and not inside client region

	if ( r.pointInside( vPoint ) )
	{
		if ( mClientRect.pointInside( vPoint ) != true )
			return true;
	}

	// Point not in corner!

	return false;
}

//--------------------------------
void Window::onMousePressed( MouseButtonID vButtonID, const Mocha::Vector2& vPoint, bool vDoubleClick )
{
	// Get border

	Border* border = getRenderBorder( );

	// See if the close button is pressed, or the mouse mode needs to change

	if ( mCloseable && border && border->pointInButton( vPoint + getPosition( ), mRectangle ) )
	{
		mClosePressed = true;
		mCloseDown = true;

		flagDirty( );
	}
	else if ( mMovable && border && pointInTitle( *border, vPoint ) )
	{
		// Start move mode

		mMouseMode = MOUSEMODE_MOVING;

		// Notify window animator

		if ( mAnimator )
			mAnimator->onMoveStarted( *this, vPoint );
	}
	else if ( mResizeable && border && pointInResizeCorner( *border, vPoint ) )
	{
		// Start resize mode

		mMouseMode = MOUSEMODE_RESIZING;

		// Notify window animator

		if ( mAnimator )
			mAnimator->onResizeStarted( *this, vPoint );
	}
	else
	{
		// Select new focused widget

		setFocused( mRoot->findWidgetAtPoint( vPoint ) );

		// Send event to widget

		if ( mFocused && mFocused->getEnabled( ) )
		{
			const Mocha::Vector2 point = vPoint - mFocused->getClientRectangle( ).getPosition( );
			mFocused->handleMousePressed( vButtonID, point );

			if ( mFocused && vDoubleClick )
				mFocused->handleDoubleClick( vButtonID, point );
		}
	}
}

//--------------------------------
void Window::onMouseReleased( MouseButtonID vButtonID, const Mocha::Vector2& vPoint )
{
	// If close button is pressed, we may need to close the window

	if ( mClosePressed )
	{
		Border* border = getRenderBorder( );

		if ( border && border->pointInButton( vPoint + getPosition( ), mRectangle ) )
		{
			if ( mHideOnClose )
				hide( );
			else
				close( );
		}

		mClosePressed = false;
		mCloseDown = false;

		flagDirty( );
	}
	else if ( mMouseMode != MOUSEMODE_NONE )
	{
		// Reset mouse mode

		mMouseMode = MOUSEMODE_NONE;
	}
	else
	{
		// Send event to widget

		if ( mFocused && mFocused->getEnabled( ) )
			mFocused->handleMouseReleased( vButtonID, vPoint - mFocused->getClientRectangle( ).getPosition( ) );
	}
}

//--------------------------------
void Window::onMouseMotion( const Mocha::Vector2& vRel, const Mocha::Vector2& vPoint )
{
	if ( mClosePressed )
	{
		Border* border = getRenderBorder( );
		
		bool which = (border && border->pointInButton( vPoint + getPosition( ), mRectangle ));
		if ( which != mCloseDown )
		{
			mCloseDown = which;
			flagDirty( );
		}
	}
	else if ( mMouseMode == MOUSEMODE_MOVING )
	{
		// Move window

		mRectangle.translate( vRel );

		// Notify animator

		if ( mAnimator )
			mAnimator->onMoved( *this, vRel, vPoint );
	}
	else if ( mMouseMode == MOUSEMODE_RESIZING )
	{
		// Figure out new size

		Mocha::Vector2 size = mRectangle.getSize( ) + vRel;

		// Set new size

		setSize( size );

		// Notify animator

		if ( mAnimator )
			mAnimator->onResized( *this, vRel, vPoint );
	}
	else
	{
		// Send event to widget

		if ( mFocused && mFocused->getEnabled( ) )
			mFocused->handleMouseMotion( vRel, vPoint - mFocused->getClientRectangle( ).getPosition( ) );
	}
}

//--------------------------------
void Window::onMouseScrolled( float vAmount, const Mocha::Vector2& vPoint )
{
	Widget* w = findWidgetAtPoint( vPoint );
	if ( w && w->getEnabled( ) )
		w->handleMouseScrolled( vAmount );
}

//--------------------------------
void Window::onKeyPressed( KeyID vKey )
{
	if ( mFocused && mFocused->getEnabled( ) )
		mFocused->handleKeyPressed( vKey );
}

//--------------------------------
void Window::onKeyReleased( KeyID vKey )
{
	if ( mFocused && mFocused->getEnabled( ) )
		mFocused->handleKeyReleased( vKey );
}

//--------------------------------
void Window::onFocusLost( )
{
	// Release widget focus

	setFocused( 0 );

	// Do callback

	doCallback( "FocusLost" );
}

//--------------------------------
void Window::onFocusRecieved( )
{
	// Do callback

	doCallback( "FocusRecieved" );
}

//--------------------------------
void Window::setOpacity( float vValue )
{
	mOpacity = vValue;
}

//--------------------------------
float Window::getOpacity( ) const
{
	return mOpacity;
}

//--------------------------------
bool Window::getFading( ) const
{
	return ( mFader != 0 ) ? mFader->getFading( *this ) : false;
}

//--------------------------------
void Window::setMovable( bool vWhich )
{
	mMovable = vWhich;
}

//--------------------------------
bool Window::getMovable( ) const
{
	return mMovable;
}

//--------------------------------
void Window::setResizeable( bool vWhich )
{
	mResizeable = vWhich;
}

//--------------------------------
bool Window::getResizeable( ) const
{
	return mResizeable;
}

//--------------------------------
void Window::setCloseable( bool vWhich )
{
	mCloseable = vWhich;
	flagDirty( );
}

//--------------------------------
bool Window::getCloseable( ) const
{
	return mCloseable;
}

//--------------------------------
/*void Window::setVisible( bool vWhich )
{
	if ( mVisible != vWhich )
	{
		mVisible = vWhich;
		flagDirty( );

		if ( mVisible )
		{
			if ( mFader )
				mFader->onWindowOpened( *this );
			else
				mOpacity = 1.0f;
		}
		else
		{
			if ( mFader )
				mFader->onWindowClosed( *this );
			else
				mOpacity = 0.0f;
		}
	}
}*/

//--------------------------------
bool Window::getVisible( ) const
{
	return (mState == WINDOWSTATE_NORMAL) || getFading( );
}

//--------------------------------
Border* Window::getRenderBorder( ) const
{
	// Make sure border is visible

	if ( mBorderVisible == false )
		return 0;

	// Get the theme to use

	Theme* theme = getRenderTheme( );

	// Try custom border

	if ( mBorder != "" )
		return theme->getBorder( mBorder );

	// Try default theme

	return theme->getBorder( "Window" );
}

//--------------------------------
Theme* Window::getRenderTheme( ) const
{
	if ( mTheme != "" )
	{
		try
		{
			Theme* theme = Core::Get( ).getThemeManager( ).getTheme( mTheme );
			if ( theme )
				return theme;
		}
		catch ( Mocha::Exception& )
		{
			// ...
		}
	}

	return Core::Get( ).getThemeManager( ).getDefaultTheme( );
}

//--------------------------------
Font* Window::getRenderFont( ) const
{
	Theme* theme = getRenderTheme( );
	if ( theme )
		return theme->getFont( "Window" );

	return 0;
}

//--------------------------------
void Window::tick( float vDelta )
{
	// Update window animator and fader

	if ( mAnimator )
		mAnimator->onTick( *this, vDelta );

	if ( mFader )
		mFader->onTick( *this, vDelta );

	// Can we destroy the texture?

	if ( (mOpacity <= 0.0f) && (getFading( ) == false) )
		destroyTarget( );
}

//--------------------------------
void Window::show( )
{
	mState = WINDOWSTATE_NORMAL;

	if ( mFader )
		mFader->onWindowOpened( *this );
	else
		mOpacity = 1.0f;
}

//--------------------------------
void Window::hide( )
{
	mState = WINDOWSTATE_HIDDEN;

	if ( mFader )
		mFader->onWindowClosed( *this );
	else
		mOpacity = 0.0f;
}

//--------------------------------
void Window::close( )
{
	// Flag window as closed

	mState = WINDOWSTATE_CLOSED;

	// Make sure the window is no longer focused

	if ( mManager->getFocused( ) == this )
		mManager->setFocused( 0 );

	// Notify fader

	if ( mFader )
		mFader->onWindowClosed( *this );

	// Do callback

	doCallback( "Close" );
}

//--------------------------------
WindowState Window::getState( ) const
{
	return mState;
}

//--------------------------------
bool Window::getClosed( ) const
{
	return (mState == WINDOWSTATE_CLOSED);
}

//--------------------------------
void Window::destroyTarget( )
{
	if ( mTarget )
	{
		Core::Get( ).getTextureManager( ).destroyTexture( mTarget );
		mTarget = 0;
	}
}

//--------------------------------
void Window::prepareTarget( )
{
	if ( mTargetDirty || (mTarget == 0) )
	{
		Mocha::Vector2 size = mRectangle.getSize( );

		if ( mTarget == 0 )
		{
			// Create texture

			mTarget = Core::Get( ).getTextureManager( ).createRenderTarget( size );
		}
		else
		{
			// Just resize the texture

			mTarget->resize( size );
		}

		mTargetDirty = false;
	}
}

//--------------------------------
void Window::setName( const Mocha::String& vName )
{
	mName = vName;
}

//--------------------------------
const Mocha::String& Window::getName( ) const
{
	return mName;
}

//--------------------------------
void Window::setText( const Mocha::String& vText )
{
	mText = vText;
}

//--------------------------------
const Mocha::String& Window::getText( ) const
{
	return mText;
}

//--------------------------------
void Window::flagDirty( )
{
	mDirty = true;
}

//--------------------------------
bool Window::getDirty( )
{
	return mDirty || (mTarget == 0);
}

//--------------------------------
void Window::clearDirty( )
{
	mDirty = false;
}

//--------------------------------
void Window::setPosition( const Mocha::Vector2& vPosition )
{
	mRectangle.setPosition( vPosition );
}

//--------------------------------
Mocha::Vector2 Window::getPosition( ) const
{
	return mRectangle.getPosition( );
}

//--------------------------------
void Window::setSize( const Mocha::Vector2& vSize )
{
	mRectangle.setSize( vSize );

	checkRectSize( );
	updateClientRect( );

	doCallback( "Resized" );
	mTargetDirty = true;
}

//--------------------------------
Mocha::Vector2 Window::getSize( ) const
{
	return mRectangle.getSize( );
}

//--------------------------------
void Window::checkRectSize( )
{
	// Get size of rectangle

	Mocha::Vector2 size = mRectangle.getSize( );

	// Make sure size is greater than 0

	size.x = Mocha::max( 0.0f, size.x );
	size.y = Mocha::max( 0.0f, size.y );

	// Make sure rectangle is within range

	size.x = Mocha::clamp( size.x, mMinSize.x, ( mMaxSize.x > 0.0f ) ? mMaxSize.x : 4096.0f );
	size.y = Mocha::clamp( size.y, mMinSize.y, ( mMaxSize.y > 0.0f ) ? mMaxSize.y : 4096.0f );

	// Make sure window is not smaller than border will allow

	Border* border = getRenderBorder( );
	if ( border )
	{
		const Mocha::Vector2& minSize = border->getMinSize( );
		size.x = Mocha::max( size.x, minSize.x );
		size.y = Mocha::max( size.y, minSize.y );
	}

	// Make sure rectangle is not larger than screen

	Mocha::Vector2 screenSize = getGuiManager( )->getBrush( ).getScreenSize( );
	size.x = Mocha::min( screenSize.x, size.x );
	size.y = Mocha::min( screenSize.y, size.y );

	// Resize rect

	mRectangle.setSize( size );
}

//--------------------------------
void Window::setRectangle( const Mocha::Rectangle& vRectangle )
{
	if ( mRectangle.getSize( ) != vRectangle.getSize( ) )
	{
		mTargetDirty = true;
		mRectangle = vRectangle;

		checkRectSize( );
		updateClientRect( );

		doCallback( "Resized" );
	}
	else
		mRectangle = vRectangle;
}

//--------------------------------
const Mocha::Rectangle& Window::getClientRectangle( ) const
{
	return mClientRect;
}

//--------------------------------
const Mocha::Rectangle& Window::getRectangle( ) const
{
	return mRectangle;
}

//--------------------------------
void Window::updateClientRect( )
{
	// Calculate new client rect

	mClientRect = Mocha::Rectangle( );
	mClientRect.setSize( mRectangle.getSize( ) );
	
	Border* border = getRenderBorder( );
	if ( border )
		mClientRect += border->getClientAdjust( );

	// Adjust root widget to fit inside client rect

	mRoot->setRectangle( mClientRect );

	// Force redraw

	flagDirty( );
}

//--------------------------------
void Window::setBorderVisible( bool vWhich )
{
	mBorderVisible = vWhich;
	updateClientRect( );
}

//--------------------------------
bool Window::getBorderVisible( ) const
{
	return mBorderVisible;
}

//--------------------------------
void Window::setTheme( const Mocha::String& vName )
{
	mTheme = vName;

	updateClientRect( );
	flagDirty( );
}

//--------------------------------
const Mocha::String& Window::getTheme( ) const
{
	return mTheme;
}

//--------------------------------
void Window::drawBorder( Brush& vBrush ) const
{
	// Draw the border

	Border* border = getRenderBorder( );

	if ( border )
	{
		Mocha::Rectangle r;
		r.setSize( mRectangle.getWidth( ),
				   mRectangle.getHeight( ) );

		vBrush.setBlendMode( BRUSHBLEND_NONE );

		// Draw the border images

		border->draw( vBrush, r, true, mCloseable, mCloseDown );

		// Draw the window title

		Font* f = getRenderFont( );
		if ( f )
		{
			Mocha::Rectangle rect;

			rect.left = border->getPart( BORDER_TOPLEFT ).getWidth( ) + border->getTextOffset( ).x;
			rect.top = border->getTextOffset( ).y;

			rect.right = mRectangle.getWidth( ) - ( border->getPart( BORDER_TOPRIGHT ).getWidth( ) + abs( border->getCloseButtonOffset( ).x ) );
			rect.bottom = border->getPart( BORDER_TOP ).getHeight( );

			vBrush.setBlendMode( BRUSHBLEND_ALPHA );
			vBrush.setColor( getRenderTheme( )->getColor( "WindowTitle", Mocha::Color( 0.0f, 0.0f, 0.0f, 1.0f ) ) );

			vBrush.setClipRegion( rect );
			vBrush.drawText( f, mText, rect );
		}
	}
}

//--------------------------------
void Window::draw( Brush& vBrush )
{
	// Make sure target is up to date

	prepareTarget( );

	// Start using target

	vBrush.setTarget( mTarget );

	// Clear the target

	vBrush.setColor( Mocha::Color::Transparent );
	vBrush.clear( );

	// Draw border

	if ( mBorderVisible )
		drawBorder( vBrush );

	// Initialize clip region

	vBrush.setClipRegion( mClientRect );

	// Draw widgets

	mRoot->draw( vBrush );
}

//--------------------------------
void Window::setHideOnClose( bool vWhich )
{
	mHideOnClose = vWhich;
}

//--------------------------------
bool Window::getHideOnClose( ) const
{
	return mHideOnClose;
}

//--------------------------------
ContainerWidget* Window::getRoot( ) const
{
	return mRoot;
}

//--------------------------------
Texture* Window::getTarget( ) const
{
	return mTarget;
}

//--------------------------------
Widget* Window::createWidget( const Mocha::String& vName )
{
	return mRoot->createChild( vName );
}

//--------------------------------
Widget* Window::findWidgetAtPoint( const Mocha::Vector2& vPoint ) const
{
	return mRoot->findWidgetAtPoint( vPoint );
}

//--------------------------------
Widget* Window::findWidget( const Mocha::String& vName ) const
{
	return mRoot->findWidget( vName );
}

//--------------------------------
void Window::setBorder( const Mocha::String& vName )
{
	mBorder = vName;
	updateClientRect( );
}

//--------------------------------
const Mocha::String& Window::getBorder( ) const
{
	return mBorder;
}

//--------------------------------
GuiManager* Window::getGuiManager( ) const
{
	return mManager;
}

//--------------------------------
Mocha::CommandResult Window::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setText" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setText( vIn[0].getAsString( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getText" )
	{
		vOut.push_back( getText( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setName" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setName( vIn[0].getAsString( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getName" )
	{
		vOut.push_back( getName( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setBorderVisible" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setBorderVisible( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getBorderVisible" )
	{
		vOut.push_back( getBorderVisible( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setCloseable" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setCloseable( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getCloseable" )
	{
		vOut.push_back( getCloseable( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setMovable" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setMovable( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getMovable" )
	{
		vOut.push_back( getMovable( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setRectangle" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setRectangle( vIn[0].getAsRectangle( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getRectangle" )
	{
		vOut.push_back( getRectangle( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setPosition" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setPosition( vIn[0].getAsVector2( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getPosition" )
	{
		vOut.push_back( getPosition( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setSize" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setPosition( vIn[0].getAsVector2( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getSize" )
	{
		vOut.push_back( getSize( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "close" )
	{
		close( );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Mocha::CMDRESULT_INVALIDCOMMAND;
}

}
