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

#include "RBGui/GuiManager.h"

#include "RBGui/Widgets/MenuEntryWidget.h"
#include "RBGui/Widgets/RectangleWidget.h"

#define YPADDING 6.0f

namespace RBGui
{

//--------------------------------
class SubMenuFocusLostWindowCallback : public GuiCallback
{
private:
	Mocha::WeakRefPointer<MenuEntryWidget> mOwner;

	bool mClosed;

public:
	SubMenuFocusLostWindowCallback( MenuEntryWidget* vOwner )
		: mOwner( vOwner ), mClosed( false )
	{
		// ...
	}

	virtual void onGuiEvent( GuiElement& vElement, const Mocha::ValueList& vData )
	{
		// Close window

		static_cast<Window&>( vElement ).close( );
	}
};

//--------------------------------
class SubMenuCloseWindowCallback : public GuiCallback
{
private:
	Mocha::WeakRefPointer<MenuEntryWidget> mOwner;

	bool mClosed;

public:
	SubMenuCloseWindowCallback( MenuEntryWidget* vOwner )
		: mOwner( vOwner ), mClosed( false )
	{
		// ...
	}

	virtual void onGuiEvent( GuiElement& vElement, const Mocha::ValueList& vData )
	{
		if ( mClosed == false )
		{
			// Make sure the callback isn't called again...

			mClosed = true;

			// Close owner window

			if ( mOwner && mOwner->getSubMenu( ) )
			{
				// Only close the owning window if it does not have the new focus

				if ( mOwner->getGuiManager( )->getFocused( ) != mOwner->getWindow( ) )
				{
					mOwner->getWindow( )->close( );
					mOwner->deselectSiblings( );
				}
			}

			// Make sure owner widget is no longer selected

			if ( mOwner )
				mOwner->setSelected( false );
		}
	}
};

//--------------------------------
MenuEntryWidget::MenuEntryWidget( GuiManager* vManager, MenuWidget* vMenu )
: Widget( vManager ), mTextAlignMode( TEXTALIGN_CENTER ), mSubMenu( false ), mSelected( false ), mMenu( vMenu )
{
	// ...
}

//--------------------------------
MenuEntryWidget::~MenuEntryWidget( )
{
	// ...
}

//--------------------------------
void MenuEntryWidget::setTextAlignment( TextAlignmentMode vAlign )
{
	mTextAlignMode = vAlign;
	flagDirty( );
}

//--------------------------------
void MenuEntryWidget::deselectSiblings( )
{
	Widget* parent = getParent( );
	if ( parent )
	{
		const WidgetList& siblings = parent->getChildren( );

		WidgetList::const_iterator it;
		for ( it = siblings.begin( ); it != siblings.end( ); it++ )
		{
			MenuEntryWidget* menu = dynamic_cast<MenuEntryWidget*>( (*it).get( ) );
			if ( menu && (menu != this) && (menu->mDropWindow == 0) )
				menu->setSelected( false );
		}
	}
}

//--------------------------------
void MenuEntryWidget::onMenuClosed( )
{
	setSelected( false );
	deselectSiblings( );
}

//--------------------------------
void MenuEntryWidget::setSubMenu( bool vWhich )
{
	mSubMenu = vWhich;
}

//--------------------------------
bool MenuEntryWidget::getSubMenu( ) const
{
	return mSubMenu;
}

//--------------------------------
void MenuEntryWidget::onTextChanged( )
{
	const float xpadding = 8.0f;

	// Make sure we have a Window

	if ( getWindow( ) == 0 )
		return;

	// Calculate new size of widget

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	float width = f->getTextWidth( getText( ) ) + xpadding;
	float height = f->getMaxGlyphHeight( );

	/*if ( mEntry )
	{
		const Mocha::String& icon = mEntry->getIcon( );
		if ( icon != "" )
		{
			Texture* t = getTheme( )->getImage( icon );
			width += t->getWidth( );
		}
	}*/

	Mocha::Rectangle rect = getRectangle( );
	rect.setSize( width, height );

	setRectangle( rect );
}

//--------------------------------
void MenuEntryWidget::createSubMenu( MenuEntry* vEntry )
{
	// Calculate the position of the Window

	Mocha::Rectangle rect = getScreenRectangle( );

	Mocha::Vector2 pos;
	if ( mSubMenu == false )
		pos = getWindow( )->getScreenPosition( Mocha::Vector2( rect.left, rect.top + rect.getHeight( )+1 ) );
	else
		pos = getWindow( )->getScreenPosition( Mocha::Vector2( rect.left + rect.getWidth( ), rect.top ) );

	// Calculate the size of the menu

	float width = 216.0f;
	float height = 0.0f;
	
	Font* f = getRenderFont( );
	if ( f )
	{
		size_t x;
		for ( x = 0; x < vEntry->getEntryCount( ); x++ )
		{
			if ( vEntry->getEntry( x ).getText( ) != "-" )
				height += f->getMaxGlyphHeight( ) + YPADDING;
			else
				height += 4.0f;
		}
	}

	// Adjust width and height for menu border

	Border* border = getRenderTheme( )->getBorder( "DropMenu" );
	if ( border )
	{
		const Mocha::Rectangle& adjust = border->getClientAdjust( );

		width += adjust.left - adjust.right;
		height += adjust.left - adjust.bottom;
	}

	Window* win;
	if ( mSubMenu )
		win = getWindow( );
	else
		win = 0;

	// Create the Window
	
	mDropWindow = getGuiManager( )->createWindow( false );
	mDropWindow->setCallback( new SubMenuFocusLostWindowCallback( this ), "FocusLost" );
	mDropWindow->setCallback( new SubMenuCloseWindowCallback( this ), "Close" );
	mDropWindow->setBorder( "DropMenu" );
	mDropWindow->setSize( Mocha::Vector2( width, height ) );
	mDropWindow->setPosition( pos );
	mDropWindow->setMovable( false );
	mDropWindow->show( );
	
	getGuiManager( )->setFocused( mDropWindow, true );
	fillSubMenu( vEntry );

	// Inherit widget scale

	//mDropWindow->setScaleX( mWindow->getScaleX( ) );
	//mDropWindow->setScaleY( mWindow->getScaleX( ) );
}

//--------------------------------
void MenuEntryWidget::fillSubMenu( MenuEntry* vEntry )
{
	// Setup menu widgets for each entry

	float ypos = 0.0f;

	size_t x;
	for ( x = 0; x < vEntry->getEntryCount( ); x++ )
	{
		const MenuEntry& entry = vEntry->getEntry( x );
		if ( entry.getText( ) != "-" )
		{
			// Create a menu for the entry

			MenuEntryWidget* menu = new MenuEntryWidget( getGuiManager( ), mMenu );
			mDropWindow->getRoot( )->addChild( menu );

			menu->setTextAlignment( TEXTALIGN_LEFT );
			menu->setSubMenu( true );
			menu->setName( entry.getName( ) );
			menu->setText( entry.getText( ) );
			menu->setGenerated( true );

			// Set position and adjust size

			Mocha::Rectangle r = menu->getRectangle( );
			r.setWidth( mDropWindow->getClientRectangle( ).getWidth( ) );
			r.setHeight( r.getHeight( ) + YPADDING );
			r.setPosition( 0.0f, ypos );

			menu->setRectangle( r );

			// Move further down

			ypos += r.getHeight( );
		}
		else
		{
			// Create a break in the menu

			RectangleWidget* rect = new RectangleWidget( getGuiManager( ) );
			mDropWindow->getRoot( )->addChild( rect );

			rect->setColor( Mocha::Color( 0.0f, 0.0f, 0.0f, 0.3f ) );
			rect->setBorderVisible( false );

			Mocha::Rectangle r;
			r.setWidth( mDropWindow->getClientRectangle( ).getWidth( ) - 32.0f );
			r.setHeight( 1.0f );
			r.setPosition( 16.0f, ypos + 1.0f );

			rect->setRectangle( r );

			// Move further down

			ypos += 4.0f;
		}
	}
}

//--------------------------------
void MenuEntryWidget::setSelected( bool vWhich )
{
	// Deselect other menu items

	if ( vWhich == true )
		deselectSiblings( );

	mSelected = vWhich;
	flagDirty( );
}

//--------------------------------
bool MenuEntryWidget::getSelected( ) const
{
	return mSelected;
}

//--------------------------------
void MenuEntryWidget::onMousePressed( MouseButtonID vButtonID, const Mocha::Vector2& vPoint )
{
	// Select this entry

	setSelected( true );

	// Get menu entry

	MenuEntry* entry = getEntry( );
	if ( entry == 0  )
		return;

	// Create sub menu

	if ( entry->getEntryCount( ) > 0 )
	{
		// Open sub menu

		createSubMenu( entry );
	}
	else
	{
		// Do callback

		mMenu->entrySelected( entry->getID( ) );

		// Close window

		if ( mSubMenu )
			getWindow( )->close( );
	}
}

//--------------------------------
void MenuEntryWidget::onMouseReleased( MouseButtonID vButtonID, const Mocha::Vector2& vPoint )
{
	setSelected( false );
}

//--------------------------------
void MenuEntryWidget::onMouseEnter( const Mocha::Vector2& vPoint )
{
	setSelected( true );
}

//--------------------------------
void MenuEntryWidget::onMouseLeave( )
{
	if ( mDropWindow == 0 )
		setSelected( false );
}

//--------------------------------
MenuEntry* MenuEntryWidget::getEntry( ) const
{
	// Bail out if menu was destroyed (Probably shouldn't happen...)

	if ( mMenu == 0 )
		return 0;

	// Get the entry for this menu

	Mocha::String rootName;
	return mMenu->getEntry( getName( ), rootName );
}

//--------------------------------
void MenuEntryWidget::onDraw( Brush& vBrush ) const
{
	const Mocha::Rectangle& client = getClientRectangle( );

	// Get theme

	Theme* theme = getRenderTheme( );
	if ( theme == 0 )
		return;

	// Get font

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	// Use alpha blending

	vBrush.setBlendMode( BRUSHBLEND_ALPHA );

	// Draw highlight if we're selected

	if ( mSelected )
	{
		Border* border = theme->getBorder( "MenuEntrySelected" );
		if ( border )
			border->draw( vBrush, client );
	}

	const Mocha::Color& color = ( mSelected ? theme->getColor( "MenuEntrySelectedColor", Mocha::Color::White ) : theme->getColor( "MenuEntryColor", Mocha::Color::Black ) );
	vBrush.setColor( color );

	// Draw the arrow if this is a submenu

	MenuEntry* entry = getEntry( );
	if ( mSubMenu && (entry && entry->getEntryCount( ) > 0) )
	{
		Texture* arrow = theme->getTexture( "MenuEntryArrow" );
		if ( arrow )
		{
			const Mocha::Vector2 size = arrow->getSize( );

			Mocha::Rectangle r;
			r.setSize( size );
			r.setPosition( client.right - size.x,
						   client.top + (client.getHeight( )/2) - (size.y/2) );

			vBrush.setTexture( arrow );
			vBrush.drawRectangle( r );
		}
	}

	// Draw the icon

	/*if ( mEntry )
	{
		const Mocha::String& icon = mEntry->getIcon( );
		if ( icon != "" )
		{
			Texture* img = theme->getTexture( icon );
			
			Mocha::Rectangle r;
			r.setSize( img->getWidth( ), img->getHeight( ) );
			r.setPosition( client.left, client.top );

			vBrush.setTexture( img );
			vBrush.drawRectangle( r );
		}
	}*/

	// Draw the menu text

	Mocha::Rectangle textRect = client;

	if ( mSubMenu )
		textRect.left += 18.0f;

	vBrush.setColor( color );
	vBrush.drawText( f, getText( ), textRect, false,
					 mTextAlignMode, TEXTALIGN_CENTER );
}

}
