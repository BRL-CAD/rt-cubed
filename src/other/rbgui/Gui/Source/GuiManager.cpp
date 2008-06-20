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

#include "Mocha/DataSection.h"

#include "RBGui/GuiManager.h"
#include "RBGui/Exception.h"
#include "RBGui/Core.h"

#include "RBGui/Widgets/ButtonWidget.h"
#include "RBGui/Widgets/ScrollWidget.h"
#include "RBGui/Widgets/ImageWidget.h"
#include "RBGui/Widgets/MenuWidget.h"
#include "RBGui/Widgets/TextWidget.h"
#include "RBGui/Widgets/TextEntryWidget.h"
#include "RBGui/Widgets/EvaluatorWidget.h"
#include "RBGui/Widgets/CheckWidget.h"
#include "RBGui/Widgets/OptionWidget.h"
#include "RBGui/Widgets/SplineWidget.h"
#include "RBGui/Widgets/ListWidget.h"
#include "RBGui/Widgets/RectangleWidget.h"
#include "RBGui/Widgets/DropSplineWidget.h"
#include "RBGui/Widgets/ProgressWidget.h"
#include "RBGui/Widgets/DropListWidget.h"
#include "RBGui/Widgets/ColorSelectWidget.h"
#include "RBGui/Widgets/AttributeEditWidget.h"
#include "RBGui/Widgets/DirectoryListWidget.h"

#include "RBGui/WobbleWindowAnimator.h"
#include "RBGui/SimpleWindowFader.h"

//#include "RBGui/Widgets/BrowserWidget.h"

namespace RBGui
{

//--------------------------------
typedef std::map<Mocha::String, WidgetFactory> FactoryMap;
static FactoryMap factories;

//--------------------------------
typedef std::map<Mocha::String, WindowAnimatorFactory> WindowAnimatorFactoryMap;
static WindowAnimatorFactoryMap animatorFactories;

//--------------------------------
typedef std::map<Mocha::String, WindowFaderFactory> WindowFaderFactoryMap;
static WindowFaderFactoryMap faderFactories;

//--------------------------------
GuiManager::GuiManager( Brush* vBrush )
: mBrush( vBrush ), mClickTimer( 0.0f ), mButtonMask( 0 ), mKeyRepeatTimer( 0.0f ), mFirstKeyDelay( true ), mLastKey( KEY_NONE ), mKeyModifiers( 0 )
{
	// ...
}

//--------------------------------
GuiManager::~GuiManager( )
{
	shutdown( );
}

//--------------------------------
void GuiManager::setDefaultWindowAnimator( const Mocha::String& vName )
{
	mDefaultWindowAnimator = vName;
}

//--------------------------------
void GuiManager::setDefaultWindowFader( const Mocha::String& vName )
{
	mDefaultWindowFader = vName;
}

//--------------------------------
int GuiManager::getKeyModifiers( ) const
{
	return mKeyModifiers;
}

//--------------------------------
void GuiManager::setCursorManager( CursorManager* vManager )
{
	mCursorManager = vManager;
}

//--------------------------------
CursorManager* GuiManager::getCursorManager( ) const
{
	return mCursorManager;
}

//--------------------------------
Widget* GuiManager::createWidget( const Mocha::String& vName )
{
	FactoryMap::const_iterator it = factories.find( vName );
	if ( it != factories.end( ) )
		return (*it).second( this );

	throw Exception( "No widget factory named '" + vName + "'" );
}

//--------------------------------
void GuiManager::bringToFront( Window* vWindow )
{
	// Hold a reference to the window to make sure it doesn't get garbage collected

	Mocha::RefPointer<Window> win = vWindow;

	// Find window and remove it from list

	WindowList::iterator it = std::find( mWindows.begin( ), mWindows.end( ), win );
	if ( it != mWindows.end( ) )
		mWindows.erase( it );

	// Push window to end of list

	mWindows.push_back( win );
}

//--------------------------------
void GuiManager::sendToBack( Window* vWindow )
{
	// Hold a reference to the window to make sure it doesn't get garbage collected

	Mocha::RefPointer<Window> win = vWindow;

	// Find window and remove it from list

	WindowList::iterator it = std::find( mWindows.begin( ), mWindows.end( ), win );
	if ( it != mWindows.end( ) )
		mWindows.erase( it );

	// Push window to end of list

	mWindows.push_front( win );
}

//--------------------------------
Window* GuiManager::createWindow( bool vSetFocused )
{
	Mocha::RefPointer<Window> win = new Window( this );
	mWindows.push_back( win );

	// Set as new focused window if necessary

	if ( vSetFocused )
		setFocused( win );

	// Set window animator

	if ( mDefaultWindowAnimator != "" )
	{
		WindowAnimatorFactoryMap::const_iterator it = animatorFactories.find( mDefaultWindowAnimator );
		if ( it != animatorFactories.end( ) )
			win->setAnimator( (*it).second( ) );
	}

	// Set window fader

	if ( mDefaultWindowFader != "" )
	{
		WindowFaderFactoryMap::const_iterator it = faderFactories.find( mDefaultWindowFader );
		if ( it != faderFactories.end( ) )
			win->setFader( (*it).second( ) );
	}

	// Return new window

	return win;
}

//--------------------------------
void GuiManager::destroyWindow( Window* vWindow )
{
	WindowList::iterator it = std::find( mWindows.begin( ), mWindows.end( ), vWindow );
	if ( it != mWindows.end( ) )
		mWindows.erase( it );
}

//--------------------------------
Window* GuiManager::findWindow( const Mocha::String& vName ) const
{
	WindowList::const_iterator it;
	for ( it = mWindows.begin( ); it != mWindows.end( ); it++ )
	{
		Window* win = (*it);
		if ( win->getName( ) == vName )
			return win;
	}

	return 0;
}

//--------------------------------
const WindowList& GuiManager::getWindows( ) const
{
	return mWindows;
}

//--------------------------------
void GuiManager::clear( )
{
	mWindows.clear( );
}

//--------------------------------
void GuiManager::updateCursor( const Mocha::Vector2& vPoint )
{
	if ( mCursorManager )
	{
		if ( (mFocused == 0) || ((mFocused->getMoving( ) == false) && (mFocused->getResizing( ) == false)) )
		{
			Window* win = findWindowAtPoint( vPoint );
			if ( win )
			{
				// Tell window to update cursor

				win->updateCursor( vPoint - win->getPosition( ) );
			}
			else
				mCursorManager->setCursor( CURSOR_DEFAULT );
		}
		else if ( mFocused->getMoving( ) )
		{
			// If the window is moving, always use default cursor

			mCursorManager->setCursor( CURSOR_DEFAULT );
		}
		else if ( mFocused->getResizing( ) )
		{
			// If the window is resizing, always use resize cursor

			mCursorManager->setCursor( CURSOR_RESIZE );
		}

		// Set cursor position

		mCursorManager->onMouseMoved( vPoint ); 
	}
}

//--------------------------------
void GuiManager::updateKeyRepeat( float vDelta )
{
	PlatformManager& platformManager = Core::Get( ).getPlatformManager( );

	float keyDelay = ( mFirstKeyDelay ? platformManager.getKeyRepeatDelay( ) : platformManager.getKeyRepeatSpeed( ) );
	mKeyRepeatTimer += vDelta;

	if ( (mLastKey != KEY_NONE) && (mKeyRepeatTimer >= keyDelay) )
	{
		injectKeyPressed( mLastKey );

		mKeyRepeatTimer = 0.0f;
		mFirstKeyDelay = false;
	}	
}

//--------------------------------
void GuiManager::tick( float vDelta )
{
	// Update double click timer

	mClickTimer += vDelta;

	// Update windows and remove any that are closed

	WindowList::iterator it = mWindows.begin( );
	while ( it != mWindows.end( ) )
	{
		Window* win = (*it);
		win->tick( vDelta );

		if ( win->getClosed( ) && (win->getFading( ) == false) )
			it = mWindows.erase( it );
		else
			it++;
	}

	// Update key repeat

	updateKeyRepeat( vDelta );
}

//--------------------------------
void GuiManager::shutdown( )
{
	// ...
}

//--------------------------------
Brush& GuiManager::getBrush( )
{
	return *mBrush;
}

//--------------------------------
void GuiManager::invalidate( )
{
	WindowList::const_iterator it;
	for ( it = mWindows.begin( ); it != mWindows.end( ); it++ )
		(*it)->updateClientRect( );
}

//--------------------------------
void GuiManager::closeTagged( const Mocha::String& vTag )
{
	WindowList::const_iterator it;
	for ( it = mWindows.begin( ); it != mWindows.end( ); it++ )
	{
		Window* win = (*it);
		if ( win->getTag( ) == vTag )
			win->close( );
	}
}

//--------------------------------
void GuiManager::setFocused( Window* vWindow, bool vSuppressLost )
{
	if ( mFocused != vWindow )
	{
		Mocha::RefPointer<Window> oldFocused(mFocused);
		mFocused = vWindow;

		if ( oldFocused && (vSuppressLost == false) )
			oldFocused->onFocusLost( );

		if ( mFocused )
		{
			bringToFront( mFocused );
			mFocused->onFocusRecieved( );
		}
	}
}

//--------------------------------
Window* GuiManager::getFocused( ) const
{
	return mFocused;
}

//--------------------------------
Window* GuiManager::findWindowAtPoint( const Mocha::Vector2& vPoint ) const
{
	Window* win = 0;

	WindowList::const_reverse_iterator it;
	for ( it = mWindows.rbegin( ); it != mWindows.rend( ); it++ )
	{
		Window* w = (*it);
		if ( (w->getVisible( ) == true) && (w->getClosed( ) == false) && w->getRectangle( ).pointInside( vPoint ) )
		{
			win = w;
			break;
		}

		// Stop search if the window is modal

		if ( w->getModal( ) && (w->getVisible( ) == true) && (w->getClosed( ) == false) )
			return w;
	}

	return win;
}

//--------------------------------
bool GuiManager::injectMousePressed( MouseButtonID vButtonID, const Mocha::Vector2& vPoint )
{
	// Modify mask

	mButtonMask |= (1<<vButtonID);

	// Reset key repeat timer

	mKeyRepeatTimer = 0.0f;

	// Set new focused window

	setFocused( findWindowAtPoint( vPoint ) );

	// Notify cursor manager

	if ( mCursorManager )
		mCursorManager->onMousePressed( vButtonID );

	// Send mouse pressed event

	float timer = mClickTimer;
	mClickTimer = 0.0f;

	if ( mFocused )
	{
		bool doubleClick = ( timer <= Core::Get( ).getPlatformManager( ).getDoubleClickTime( ) );
		mFocused->onMousePressed( vButtonID, vPoint - mFocused->getPosition( ), doubleClick );

		return true;
	}

	// Reset mouse click timer

	return false;
}

//--------------------------------
bool GuiManager::injectMouseReleased( MouseButtonID vButtonID, const Mocha::Vector2& vPoint )
{
	// Modify mask

	mButtonMask &= ~(1<<vButtonID);

	// Notify cursor manager

	if ( mCursorManager )
		mCursorManager->onMousePressed( vButtonID );

	if ( mFocused )
	{
		mFocused->onMouseReleased( vButtonID, vPoint - mFocused->getPosition( ) );
		return true;
	}

	return false;
}

//--------------------------------
bool GuiManager::injectMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	// Find the widget under the mouse

	Window* win = findWindowAtPoint( vPoint );
	if ( win )
	{
		const Mocha::Vector2& winpos = vPoint - win->getPosition( );

		Widget* w =	win->findWidgetAtPoint( winpos );
		if ( mUnderMouse != w )
		{
			if ( mUnderMouse && (mUnderMouse->getWindow( )->getClosed( ) == false) )
				mUnderMouse->handleMouseLeave( );

			mUnderMouse = w;

			if ( mUnderMouse )
				mUnderMouse->handleMouseEnter( winpos - mUnderMouse->getPosition( ) );
		}
	}
	else
	{
		if ( mUnderMouse && (mUnderMouse->getWindow( )->getClosed( ) == false) )
		{
			mUnderMouse->handleMouseLeave( );
			mUnderMouse = 0;
		}
	}

	// Update mouse cursor

	updateCursor( vPoint );

	// Send mouse motion event to focused window

	if ( mFocused )
	{
		mFocused->onMouseMotion( vRelative, vPoint - mFocused->getPosition( ) );
		return ( mButtonMask != 0 );
	}

	return false;
}

//--------------------------------
bool GuiManager::injectMouseScrolled( float vAmount, const Mocha::Vector2& vPoint )
{
	Window* win = findWindowAtPoint( vPoint );
	if ( win )
	{
		win->onMouseScrolled( vAmount, vPoint - win->getPosition( ) );
		return true;
	}

	return false;
}

//--------------------------------
bool GuiManager::injectKeyPressed( KeyID vKey )
{
	// Update key mods

	switch ( vKey )
	{
	case KEY_LSHIFT:
	case KEY_RSHIFT:
		mKeyModifiers |= KM_SHIFT;
		break;

	case KEY_CAPITAL:
		{
			if ( (mKeyModifiers & KM_CAPS) == false )
				mKeyModifiers |= KM_CAPS;
			else
				mKeyModifiers &= ~KM_CAPS;
		}
		break;

	case KEY_LMENU:
	case KEY_RMENU:
		mKeyModifiers |= KM_ALT;
		break;

	case KEY_RCONTROL:
	case KEY_LCONTROL:
		mKeyModifiers |= KM_CTRL;
		break;
	}

	// Reset key repeat

	mKeyRepeatTimer = 0.0f;
	mFirstKeyDelay = true;
	mLastKey = vKey;

	// Send event to focused window

	if ( mFocused )
	{
		mFocused->onKeyPressed( vKey );
		return true;
	}

	return false;
}

//--------------------------------
bool GuiManager::injectKeyReleased( KeyID vKey )
{
	// Update key mods

	switch ( vKey )
	{
	case KEY_LSHIFT:
	case KEY_RSHIFT:
		mKeyModifiers &= ~KM_SHIFT;
		break;

	case KEY_LMENU:
	case KEY_RMENU:
		mKeyModifiers &= ~KM_ALT;
		break;

	case KEY_RCONTROL:
	case KEY_LCONTROL:
		mKeyModifiers &= ~KM_CTRL;
		break;
	}

	// Store as last key pressed for key repeat

	mLastKey = KEY_NONE;

	// Send event to focused window

	if ( mFocused )
	{
		mFocused->onKeyReleased( vKey );
		return true;
	}

	return false;
}

//--------------------------------
void GuiManager::draw( ) const
{
	if ( mBrush )
	{
		// Begin drawing

		mBrush->begin( );

		// Composite windows to screen

		WindowList::const_iterator it;
		for ( it = mWindows.begin( ); it != mWindows.end( ); it++ )
		{
			Window* win = (*it);
			if ( (win->getState( ) == WINDOWSTATE_NORMAL) || win->getFading( ) )
			{
				// Update window contents

				if ( win->getDirty( ) )
				{
					win->draw( *mBrush );
					win->clearDirty( );
				}

				// Composite window to screen

				mBrush->setTarget( 0 );
				mBrush->setBlendMode( BRUSHBLEND_ALPHA );
				mBrush->setFilterMode( BRUSHFILTER_LINEAR );

				// Have animator draw window to screen

				WindowAnimator* anim = win->getAnimator( );
				if ( anim == 0 )
				{
					mBrush->setColor( Mocha::Color( 1.0f, 1.0f, 1.0f, win->getOpacity( ) ) );
					mBrush->setTexture( win->getTarget( ) );

					Mocha::Vector2 size = win->getSize( ) / win->getTarget( )->getSize( );
					mBrush->drawRectangle( win->getRectangle( ), Mocha::Rectangle( 0.0f, 0.0f, size.x, size.y ) );
				}
				else
					anim->onDraw( *win, *mBrush );
			}
		}

		// Draw the cursor

		if ( mCursorManager )
		{
			mBrush->setTarget( 0 );
			mCursorManager->draw( *mBrush );
		}

		// All done!

		mBrush->end( );
	}
}

//--------------------------------
void AddWidgetFactory( const Mocha::String& vName, WidgetFactory vFactory )
{
	FactoryMap::iterator it = factories.find( vName );
	if ( it != factories.end( ) )
		throw Exception( "Widget factory with name '" + vName + "' already defined" );

	factories[vName] = vFactory;
}

//--------------------------------
void Initialize( )
{
	// Add all of the default widgets

	AddWidgetFactory( "Button", ButtonWidget::factory );
	AddWidgetFactory( "Menu", MenuWidget::factory );
	AddWidgetFactory( "Image", ImageWidget::factory );
	AddWidgetFactory( "Text", TextWidget::factory );
	AddWidgetFactory( "Scroll", ScrollWidget::factory );
	AddWidgetFactory( "TextEntry", TextEntryWidget::factory );
	AddWidgetFactory( "Evaluator", EvaluatorWidget::factory );
	AddWidgetFactory( "Option", OptionWidget::factory );
	AddWidgetFactory( "Check", CheckWidget::factory );
	AddWidgetFactory( "Spline", SplineWidget::factory );
	AddWidgetFactory( "DropSpline", DropSplineWidget::factory );
	AddWidgetFactory( "Mocha::Rectangle", RectangleWidget::factory );
	AddWidgetFactory( "Progress", ProgressWidget::factory );
	AddWidgetFactory( "ColorSelect", ColorSelectWidget::factory );
	AddWidgetFactory( "DropList", DropListWidget::factory );
	AddWidgetFactory( "List", ListWidget::factory );
	AddWidgetFactory( "AttributeEdit", AttributeEditWidget::factory );
	AddWidgetFactory( "DirectoryList", DirectoryListWidget::factory );

	// Add default fader and animator factories

	AddWindowFaderFactory( "Simple", SimpleWindowFader::factory );
	AddWindowAnimatorFactory( "Wobble", WobbleWindowAnimator::factory );

	// Add all of the default attribute widgets

	InitializeAttributeWidgets( );
}

//--------------------------------
void GetWidgetFactoryList( Mocha::StringList& vOut )
{
	FactoryMap::const_iterator it;
	for ( it = factories.begin( ); it != factories.end( ); it++ )
		vOut.push_back( (*it).first );
}

//--------------------------------
void AddWindowAnimatorFactory( const Mocha::String& vName, WindowAnimatorFactory vFactory )
{
	WindowAnimatorFactoryMap::iterator it = animatorFactories.find( vName );
	if ( it != animatorFactories.end( ) )
		throw Exception( "Window animator factory with name '" + vName + "' already defined" );

	animatorFactories[vName] = vFactory;
}

//--------------------------------
void GetWindowAnimatorFactoryList( Mocha::StringList& vOut )
{
	WindowAnimatorFactoryMap::const_iterator it;
	for ( it = animatorFactories.begin( ); it != animatorFactories.end( ); it++ )
		vOut.push_back( (*it).first );
}

//--------------------------------
void AddWindowFaderFactory( const Mocha::String& vName, WindowFaderFactory vFactory )
{
	WindowFaderFactoryMap::iterator it = faderFactories.find( vName );
	if ( it != faderFactories.end( ) )
		throw Exception( "Window fader factory with name '" + vName + "' already defined" );

	faderFactories[vName] = vFactory;
}

//--------------------------------
void GetWindowFaderFactoryList( Mocha::StringList& vOut )
{
	WindowFaderFactoryMap::const_iterator it;
	for ( it = faderFactories.begin( ); it != faderFactories.end( ); it++ )
		vOut.push_back( (*it).first );
}

}
