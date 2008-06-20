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

#include "RBGui/Core.h"
#include "RBGui/InputDefines.h"

#include "RBGui/Widgets/TextEntryWidget.h"
#include "RBGui/Widgets/ScrollWidget.h"

namespace RBGui
{

//--------------------------------
TextEntryWidget::TextEntryWidget( GuiManager* vManager )
: Widget( vManager ), mEnableReturn( true ), mMultiLine( false ), mDrawCursor( false ), mNumericOnly( false ), mDragging( false ),
  mLocked( false ), mWrapWidth( 0 ), mTextHeight( 0 ), mCursorPos( 0 ), mSelectOrigin( -1 ), mSelectStart( -1 ),
  mSelectEnd( -1 ), mWrap( false ), mOffsetX( 0 ), mOffsetY( 0 ), mScrollBar( 0 ), mPassword( false )
{
	// Create the scroll bar

	mScrollBar = new ScrollWidget( vManager );
	mScrollBar->setCallback( &TextEntryWidget::textScrolled, this );
	mScrollBar->setGenerated( true );
	mScrollBar->setVisible( false );

	attach( mScrollBar );
}

//--------------------------------
TextEntryWidget::~TextEntryWidget( )
{
	// ...
}

//--------------------------------
void TextEntryWidget::setPassword( bool vWhich )
{
	mPassword = vWhich;

	onTextChanged( );
	flagDirty( );
}

//--------------------------------
bool TextEntryWidget::getPassword( ) const
{
	return mPassword;
}

//--------------------------------
const Mocha::String& TextEntryWidget::getRealText( ) const
{
	if ( mPassword )
		return mPasswordText;

	return getText( );
}

//--------------------------------
CursorType TextEntryWidget::getCursor( ) const
{
	return ( mLocked ? CURSOR_DEFAULT : CURSOR_TEXT );
}

//--------------------------------
void TextEntryWidget::textScrolled( GuiElement& vElement, const Mocha::ValueList& vData )
{
	adjustScrollY( );
}

//--------------------------------
void TextEntryWidget::findLineStart( bool vShift )
{
	int pos = mCursorPos;

	int x;
	for ( x = pos; x >= 1; x-- )
	{
		if ( getRealText( )[x-1] == '\n' )
			break;
	}

	setCursorPos( x, vShift );
}

//--------------------------------
void TextEntryWidget::findLineEnd( bool vShift )
{
	const Mocha::String& text = getRealText( );
	int pos = mCursorPos;

	int x;
	for ( x = pos; x < (int)text.size( ); x++ )
	{
		if ( text[x] == '\n' )
			break;
	}

	setCursorPos( x, vShift );
}

//--------------------------------
void TextEntryWidget::setLocked( bool vWhich )
{
	mLocked = vWhich;
}

//--------------------------------
bool TextEntryWidget::getLocked( ) const
{
	return mLocked;
}

//--------------------------------
void TextEntryWidget::setScrollY( float vValue )
{
	mScrollBar->setValue( vValue );
	adjustScrollY( );
}

//--------------------------------
float TextEntryWidget::getScrollY( ) const
{
	return mScrollBar->getValue( );
}

//--------------------------------
void TextEntryWidget::adjustScrollY( )
{
	// Calculate scroll offset

	float value = mScrollBar->getValue( );

	float tmp = mTextHeight - getClientRectangle( ).getHeight( );
	if ( tmp < 0 )
		tmp = 0.0f;

	// Adjust Y offset

	mOffsetY = tmp * value;
	updateTextRect( );
}

//--------------------------------
void TextEntryWidget::updateTextHeight( )
{
	Font* f = getRenderFont( );
	if ( f )
	{
		LineInfoList lines;
		f->processText( getRealText( ), mWrap, mTextRect.getWidth( ), lines );

		mTextHeight = lines.size( ) * f->getMaxGlyphHeight( );
	}
}

//--------------------------------
void TextEntryWidget::setNumericOnly( bool vWhich )
{
	mNumericOnly = true;
}

//--------------------------------
bool TextEntryWidget::getNumericOnly( ) const
{
	return mNumericOnly;
}

//--------------------------------
void TextEntryWidget::updateTextRect( )
{
	// Update the text rectangle

	mTextRect = getClientRectangle( );
	if ( mScrollBar->getVisible( ) )
		mTextRect.right -= mScrollBar->getRectangle( ).getWidth( );

	mWrapWidth = mTextRect.getWidth( );

	// Adjust for scroll amount

	mTextRect.left -= mOffsetX;
	mTextRect.top -= mOffsetY;
}

//--------------------------------
void TextEntryWidget::onRectangleChanged( )
{
	// Get new client rectangle

	const Mocha::Rectangle& rect = getClientRectangle( );

	// Adjust size and position of scrollbar

	Theme* theme = getRenderTheme( );
	if ( theme )
	{
		float w = theme->getFloat( "ScrollWidth", 14.0f );

		Mocha::Rectangle r;
		r.setPosition( rect.getWidth( )-w, 0.0f );
		r.setSize( w, rect.getHeight( ) );

		mScrollBar->setRectangle( r );
	}

	// Update the text rectangle

	updateTextRect( );

	// Re-process text

	processText( );

	// Update cursor position

	updateCursorLocation( );
}

//--------------------------------
void TextEntryWidget::setMultiLine( bool vWhich )
{
	mScrollBar->setVisible( vWhich );
	mMultiLine = vWhich;

	updateTextRect( );
}

//--------------------------------
bool TextEntryWidget::getMultiLine( ) const
{
	return mMultiLine;
}

//--------------------------------
void TextEntryWidget::scrollTextX( int vAmount )
{
	mOffsetX += vAmount;

	updateTextRect( );
	updateCursorLocation( );
}

//--------------------------------
void TextEntryWidget::scrollTextY( int vAmount )
{
	mOffsetY += vAmount;

	updateTextRect( );
	updateCursorLocation( );
}

//--------------------------------
void TextEntryWidget::updateCursorLocation( )
{
	Font* f = getRenderFont( );
	if ( f )
		mCursorLocation = f->getCharacterPosition( mLines, mCursorPos, mTextRect.getPosition( ) );
}

//--------------------------------
void TextEntryWidget::setCursorPos( int vPos, bool vSelect )
{
	// Update selection if necessary

	if ( vSelect )
	{
		if ( mSelectOrigin < 0 )
			mSelectOrigin = mCursorPos;

		if ( vPos < mSelectOrigin )
		{
			mSelectStart = vPos;
			mSelectEnd = mSelectOrigin;
		}
		else
		{
			mSelectStart = mSelectOrigin;
			mSelectEnd = vPos;
		}

		mCursorPos = vPos;
	}
	else
	{
		mCursorPos = vPos;
		resetSelection( );
	}

	// Clamp range of position

	if ( mCursorPos < 0 )
		mCursorPos = 0;

	if ( mCursorPos > getRealText( ).size( ) )
		mCursorPos = getRealText( ).size( );

	// Get location of cursor in screen coordinates

	updateCursorLocation( );
	const Mocha::Rectangle& r2 = getClientRectangle( );

	Font* font = getRenderFont( );
	if ( font )
	{
		float height = Mocha::min( font->getMaxGlyphHeight( ), r2.getHeight( ) );

		// Scroll the X text position

		if ( mCursorLocation.x > mTextRect.right )
			scrollTextX( mCursorLocation.x - mTextRect.right );
		if ( mCursorLocation.x < r2.left )
			scrollTextX( -(r2.left - mCursorLocation.x) );

		// Scroll the Y text position

		const Mocha::Rectangle& clientRect = getClientRectangle( );

		Mocha::Vector2 p = mCursorLocation + Mocha::Vector2( -mOffsetX, -mOffsetY );
		Mocha::Vector2 p2 = mCursorLocation;

		if ( p2.y+height >= clientRect.bottom )
		{
			// Scroll down
			scrollTextY( (p2.y+height) - clientRect.bottom );
		}
		else if ( p.y < mTextRect.top )
		{
			// Scroll up
			scrollTextY( p.y - mTextRect.top );
		}
	}

	flagDirty( );
}

//--------------------------------
int TextEntryWidget::getCursorPos( ) const
{
	return mCursorPos;
}

//--------------------------------
void TextEntryWidget::setWrap( bool vWhich )
{
	mWrap = vWhich;
	flagDirty( );
}

//--------------------------------
bool TextEntryWidget::getWrap( ) const
{
	return mWrap;
}

//--------------------------------
void TextEntryWidget::copy( ) const
{
	const Mocha::String& text = getRealText( );

	if ( mSelectStart != mSelectEnd )
		Core::Get( ).getPlatformManager( ).setClipboardText( Mocha::String( text.begin( ) + mSelectStart, text.begin( ) + mSelectEnd ) );
}

//--------------------------------
void TextEntryWidget::paste( )
{
	// Get text from clipboard

	Mocha::String text;
	Core::Get( ).getPlatformManager( ).getClipboardText( text );

	// Insert text

	insertText( text );
}

//--------------------------------
void TextEntryWidget::onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	Mocha::Vector2 point = vPoint;

	if ( mDragging )
	{
		// Find the position of the character under the mouse

		if ( point.y < 0 )
			point.y = -1;
		else if ( point.y > getClientRectangle( ).bottom )
			point.y = getClientRectangle( ).bottom;

		int loc = getCharacterIndexAtPixel( point.x, point.y );
		if ( loc >= 0 )
			setCursorPos( loc, true );
	}
}

//--------------------------------
int TextEntryWidget::getCharacterIndexAtPixel( int vX, int vY )
{
	// Get the font to use

	Font* f = getRenderFont( );
	if ( f )
	{
		// Move the rectangle into local space

		Mocha::Rectangle textRect = mTextRect;
		textRect.setPosition( -mOffsetX, -mOffsetY );

		// Get the character under the pixel coordinate

		return f->getCharacterIndexAt( mLines, textRect.getPosition( ), Mocha::Vector2( vX, vY ) );
	}
	
	return 0;
}

//--------------------------------
void TextEntryWidget::onMousePressed( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	// See if the shift button is pressed

	bool shift = (getGuiManager( )->getKeyModifiers( ) & KM_SHIFT);

	// Select character at index under cursor

	int index = getCharacterIndexAtPixel( vPoint.x, vPoint.y );
	if ( index >= 0 )
		setCursorPos( index, shift );

	// Flag dirty

	mDragging = true;
	flagDirty( );
}

//--------------------------------
void TextEntryWidget::onMouseReleased( MouseButtonID vButton, const Mocha::Vector2& vPoint )
{
	mDragging = false;
	flagDirty( );
}

//--------------------------------
void TextEntryWidget::removeText( int vStart, int vEnd )
{
	if ( vStart < 0 )
		vStart = 0;

	int len = vEnd - vStart;
	if ( len <= 0 )
		len = 1;

	Mocha::String text = getText( );
	text.erase( vStart, len );

	setText( text );
}

//--------------------------------
void TextEntryWidget::insertText( const Mocha::String& vText )
{
	// Store start of selection

	int start = mSelectStart;
	if ( start < 0 )
		start = 0;

	// If we have a selection, remove it

	if ( mSelectStart != mSelectEnd )
		removeText( mSelectStart, mSelectEnd );

	// Insert text

	Mocha::String text = getText( );

	if ( start > (int)text.size( ) )
		start = text.size( );

	text.insert( start, vText );

	setText( text );

	// Adjust cursor position

	setCursorPos( start + vText.size( ) );
}

//--------------------------------
void TextEntryWidget::onReturnPressed( )
{
	doCallback( "onReturnPressed" );
}

//--------------------------------
void TextEntryWidget::moveCursorY( float vDir, bool vSelect )
{
	Font* f = getRenderFont( );
	if ( f )
	{
		// Move cursor location into client space

		Mocha::Vector2 pos = mCursorLocation;
		pos.x -= getClientRectangle( ).left;
		pos.y -= getClientRectangle( ).top;

		pos.y += f->getMaxGlyphHeight( ) * vDir;

		if ( pos.y < -mOffsetY )
			return;
		else if ( pos.y >= mTextRect.getHeight( ) )
			return;

		// Get index of character under cursor

		int index = getCharacterIndexAtPixel( pos.x, pos.y );
		if ( index >= 0 )
			setCursorPos( index, vSelect );
	}
}

//--------------------------------
void TextEntryWidget::setSelectionEnd( int vPos )
{
	mSelectEnd = vPos;
	if ( mSelectEnd < mSelectStart )
		std::swap( mSelectEnd, mSelectStart );
}

//--------------------------------
void TextEntryWidget::setSelectionStart( int vPos )
{
	mSelectStart = vPos;
	if ( mSelectStart > mSelectEnd )
		std::swap( mSelectEnd, mSelectStart );
}

//--------------------------------
void TextEntryWidget::resetSelection( )
{
	mSelectOrigin = -1;
	mSelectStart = mCursorPos;
	mSelectEnd = mCursorPos;
}

//--------------------------------
void TextEntryWidget::onKeyPressed( KeyID vKey )
{
	// Get key modifier mask

	int mods = getGuiManager( )->getKeyModifiers( );

	// Handle copy key

	if ( (mods & KM_CTRL) && (vKey == KEY_C) )
	{
		copy( );
		return;
	}

	// Don't do anything else if widget is locked

	if ( mLocked == true )
		return;

	// Handle paste and cut key

	if ( (mods & KM_CTRL) && (vKey == KEY_V) )
	{
		paste( );
		return;
	}
	else if ( (mods & KM_CTRL) && (vKey == KEY_X) )
	{
		copy( );

		int start = mSelectStart;

		removeText( mSelectStart, mSelectEnd );
		setCursorPos( start );

		return;
	}

	// Do other stuff :)

	switch ( vKey )
	{
	case KEY_BACK:
		{
			if ( mSelectStart == mSelectEnd )
			{
				int pos = getCursorPos( );
				if ( pos > 0 )
				{
					setCursorPos( pos-1 );
					removeText( pos-1, pos );
				}
			}
			else
			{
				int start = mSelectStart;

				removeText( mSelectStart, mSelectEnd );
				setCursorPos( start );
			}
		}
		break;

	case KEY_DELETE:
		{
			int start = mSelectStart;

			removeText( mSelectStart, mSelectEnd );
			setCursorPos( start );
		}
		break;

	case KEY_LEFT:
		{
			int newpos = getCursorPos( )-1;
			setCursorPos( newpos, (mods & KM_SHIFT) );
		}
		break;

	case KEY_RIGHT:
		{
			int newpos = getCursorPos( )+1;
			setCursorPos( newpos, (mods & KM_SHIFT) );
		}
		break;

	case KEY_TAB:
		{
			// For now, just insert 4 spaces
			if ( mMultiLine )
				insertText( "    " );
		}
		break;

	case KEY_DOWN:
		moveCursorY( 1.0f, (mods & KM_SHIFT) );
		break;

	case KEY_UP:
		moveCursorY( -1.0f, (mods & KM_SHIFT) );
		break;

	case KEY_HOME:
		findLineStart( mods & KM_SHIFT );
		break;

	case KEY_END:
		findLineEnd( mods & KM_SHIFT );
		break;

	case KEY_RETURN:
		onReturnPressed( );

		if ( (mMultiLine == false) || (mEnableReturn == false) )
			break;

	default:
		{
			char c = getChar( vKey, mods );
			if ( mNumericOnly && (isdigit( c ) == false) && ( c != '-') && (c != '.') )
				return;

			if ( c != 0 )
				insertText( Mocha::String( ) + c );
		}
		break;
	}
}

//--------------------------------
void TextEntryWidget::setEnableReturn( bool vWhich )
{
	mEnableReturn = vWhich;
}

//--------------------------------
bool TextEntryWidget::getEnableReturn( ) const
{
	return mEnableReturn;
}

//--------------------------------
void TextEntryWidget::onFocusRecieved( )
{
	mDrawCursor = true;
	flagDirty( );
}

//--------------------------------
void TextEntryWidget::onFocusLost( )
{
	mDrawCursor = false;

	resetSelection( );
	flagDirty( );
}

//--------------------------------
void TextEntryWidget::processText( )
{
	// Cache processed lines

	Font* f = getRenderFont( );
	if ( f )
	{
		mLines.clear( );
		f->processText( getRealText( ), mWrap, mWrapWidth, mLines );

		// Update scroll size

		float h = mLines.size( )  * f->getMaxGlyphHeight( );
		mScrollBar->setSliderSize( (h > 0.0f) ? getClientRectangle( ).getHeight( ) / h : 1.0f );
	}
}

//--------------------------------
void TextEntryWidget::onTextChanged( )
{
	if ( getWindow( ) == 0 )
		return;

	updatePasswordText( );

	// Validate position of cursor

	int size = (int)getRealText( ).size( );
	if ( mCursorPos > size )
		setCursorPos( size );

	// Update height of text

	updateTextHeight( );

	// Cache processed lines

	processText( );

	// Do callback

	doCallback( );
}

//--------------------------------
void TextEntryWidget::updatePasswordText( )
{
	if ( mPassword )
	{
		const Mocha::String& text = getText( );
		mPasswordText = "";
		
		Mocha::String::const_iterator it;
		for ( it = text.begin( ); it != text.end( ); it++ )
		{
			if ( (*it) == '\n' )
				mPasswordText += '\n';
			else
				mPasswordText += "*";
		}
	}
}

//--------------------------------
void TextEntryWidget::onDraw( Brush& vBrush ) const
{
	// Get the font to use

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	// Draw the text

	vBrush.setBlendMode( BRUSHBLEND_ALPHA );
	vBrush.setColor( getDerivedColor( getRenderColor( ) ) );

	vBrush.drawText( f, mLines, mTextRect );

	// Draw selection if necessary

	if ( getEnabled( ) == true )
	{
		if ( mSelectStart != mSelectEnd )
		{
			vBrush.setBlendMode( BRUSHBLEND_INVERT );
			vBrush.setColor( Mocha::Color::White );

			vBrush.drawText( f, mLines, mTextRect, TEXTALIGN_LEFT, TEXTALIGN_TOP, true, mSelectStart, mSelectEnd );
		}

		// Draw the cursor if necessary

		if ( mDrawCursor && (mLocked == false) )
		{
			Mocha::Rectangle r;
			r.setPosition( mCursorLocation );

			// Make sure cursor always renders

			const Mocha::Rectangle& client = getClientRectangle( );
			if ( r.left >= client.right )
				r.left = client.right-1;

			r.setSize( 1, f->getMaxGlyphHeight( ) );

			// Draw cursor

			vBrush.setTexture( 0 );
			vBrush.setBlendMode( BRUSHBLEND_INVERT );
			vBrush.setColor( Mocha::Color::White );

			vBrush.drawRectangle( r );
		}
	}
}

//--------------------------------
Mocha::String TextEntryWidget::getClassName( ) const
{
	return "TextEntry";
}

//--------------------------------
void TextEntryWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "MultiLine", "bool", "Multi-Line" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Wrap", "bool", "Word Wrap" ) );
}

//--------------------------------
Mocha::CommandResult TextEntryWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setWrap" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setWrap( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getWrap" )
	{
		vOut.push_back( getWrap( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setMultiLine" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setMultiLine( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getMultiLine" )
	{
		vOut.push_back( getMultiLine( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
Widget* TextEntryWidget::factory( GuiManager* vManager )
{
	return new TextEntryWidget( vManager );
}

}
