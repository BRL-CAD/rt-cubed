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

#include "RBGui/Exception.h"
#include "RBGui/Core.h"

#include "RBGui/Widgets/ButtonWidget.h"

namespace RBGui
{

//--------------------------------
ButtonWidget::ButtonWidget( GuiManager* vManager )
: Widget( vManager ), mPressed( false ), mDown( false ), mAnimatedImage( false ), mSink( true ), mImageAlign( BUTTONIMAGEALIGN_CENTER )
{
	// ...
}

//--------------------------------
ButtonWidget::~ButtonWidget( )
{
	// ...
}

//--------------------------------
void ButtonWidget::setAnimatedImage( bool vWhich )
{
	mAnimatedImage = vWhich;
	flagDirty( );
}

//--------------------------------
bool ButtonWidget::getAnimatedImage( ) const
{
	return mAnimatedImage;
}

//--------------------------------
Mocha::String ButtonWidget::getClassName( ) const
{
	return "Button";
}

//--------------------------------
void ButtonWidget::setImageAlignment( ButtonImageAlign vMode )
{
	mImageAlign = vMode;
}

//--------------------------------
ButtonImageAlign ButtonWidget::getImageAlignment( ) const
{
	return mImageAlign;
}

//--------------------------------
void ButtonWidget::onDraw( Brush& vBrush ) const
{
	vBrush.setBlendMode( BRUSHBLEND_ALPHA );

	// Calculate offset

	Mocha::Vector2 offset;
	if ( mDown && mSink )
	{
		Border* border = getRenderBorder( );
		if ( border )
		{
			offset.x = border->getPart( BORDER_LEFT ).getWidth( );
			offset.y = border->getPart( BORDER_TOP ).getHeight( );
		}
	}

	// Get the font

	Font* f = getRenderFont( );
	if ( f == 0 )
		return;

	// Get width of text

	float textWidth = f->getTextWidth( getText( ) );

	// Get the real width of the image

	float imageWidth;
	if ( mImage )
		imageWidth = ( mAnimatedImage ? mImage->getSize( ).x / 2.0f : mImage->getSize( ).x );
	else
		imageWidth = 0.0f;

	float totalWidth = textWidth + imageWidth;
	float textLeft = getClientRectangle( ).left;

	// Draw the image

	if ( mImage )
	{
		const Mocha::Rectangle& client = getClientRectangle( );
		const Mocha::Vector2& size = mImage->getSize( );

		vBrush.setFilterMode( BRUSHFILTER_LINEAR );
		vBrush.setColor( getDerivedColor( Mocha::Color::White ) );

		float realWidth = ( mAnimatedImage ? size.x / 2.0f : size.x );
		Mocha::Rectangle tmp;

		if ( mImageAlign == BUTTONIMAGEALIGN_CENTER )
			tmp.setXPosition( client.left + ((client.getWidth( )/2) - (totalWidth/2)) );
		else
			tmp.setXPosition( client.left );

		tmp.setYPosition( client.top + ((client.getHeight( )/2) - (size.y/2)) );

		if ( mAnimatedImage == false )
			tmp.setSize( size );
		else
			tmp.setSize( realWidth, size.y );

		textLeft = tmp.right;
		tmp.translate( offset );

		Mocha::Rectangle uv;
		if ( mAnimatedImage )
		{
			uv.left = 0.5f * ( mDown ? 1.0f : 0.0f );
			uv.right = uv.left + 0.5f;
			uv.bottom = 1.0f;
			uv.top = 0.0f;
		}
		else
			uv = Mocha::Rectangle( 0.0f, 0.0f, 1.0f, 1.0f );

		vBrush.setTexture( mImage );
		vBrush.drawRectangle( tmp, uv );
	}

	// Draw the text

	vBrush.setColor( getDerivedColor( getRenderColor( ) ) );
	vBrush.setFilterMode( BRUSHFILTER_NEAREST );

	Mocha::Rectangle rect = getClientRectangle( );

	TextAlignmentMode mode;
	if ( (mImage == 0) || (mImageAlign == BUTTONIMAGEALIGN_LEFT) )
		mode = TEXTALIGN_CENTER;
	else
	{
		rect.left = textLeft;
		mode = TEXTALIGN_LEFT;
	}

	rect.translate( offset );
	vBrush.drawText( f, getText( ), rect, false, mode, TEXTALIGN_CENTER );
}

//--------------------------------
void ButtonWidget::onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	mPressed = true;
	mDown = true;

	setBorderState( "pressed" );
	flagDirty( );
}

//--------------------------------
void ButtonWidget::onMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	if ( mPressed )
	{
		setBorderState( "default" );
		flagDirty( );

		// Test to see if local space coordinate is within world space rectangle of widget

		if ( getLocalPointInside( vPoint ) )
			doCallback( );

		mPressed = false;
		mDown = false;
	}
}

//--------------------------------
void ButtonWidget::onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	if ( mPressed )
	{
		Mocha::String state;
		if ( getLocalPointInside( vPoint ) )
		{
			mDown = true;
			state = "pressed";
		}
		else
		{
			mDown = false;
			state = "default";
		}

		if ( state != getBorderState( ) )
			setBorderState( state );
	}
}

//--------------------------------
void ButtonWidget::setImage( const Mocha::String& vName )
{
	try
	{
		Mocha::RefPointer<Texture> img = Core::Get( ).getTextureManager( ).getTexture( vName );
		setImage( img );
	}
	catch ( Exception& )
	{
		// ...
	}
}

//--------------------------------
void ButtonWidget::setImage( Texture* vTexture )
{
	mImage = vTexture;
	flagDirty( );
}

//--------------------------------
Texture* ButtonWidget::getImage( ) const
{
	return mImage;
}

//--------------------------------
void ButtonWidget::setSink( bool vWhich )
{
	mSink = vWhich;
	flagDirty( );
}

//--------------------------------
bool ButtonWidget::getSink( ) const
{
	return mSink;
}

//--------------------------------
Mocha::CommandResult ButtonWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setImage" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		if ( vIn[0].isObject( ) )
			setImage( dynamic_cast<Texture*>( vIn[0].getObject( ) ) );
		else
			setImage( vIn[0].getAsString( ) );

		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getImage" )
	{
		vOut.push_back( getImage( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setAnimatedImage" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setAnimatedImage( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getAnimatedImage" )
	{
		vOut.push_back( getAnimatedImage( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setImageAlignment" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setImageAlignment( (vIn[0].getAsString( ) == "left") ? BUTTONIMAGEALIGN_LEFT : BUTTONIMAGEALIGN_CENTER );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getImageAlignment" )
	{
		vOut.push_back( (getImageAlignment( ) == BUTTONIMAGEALIGN_LEFT) ? "left" : "center" );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "setSink" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setSink( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getSink" )
	{
		vOut.push_back( getSink( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
void ButtonWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "AnimatedImage", "bool", "Animated Image" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "ImageAlignment", "list|center|left", "Image Alignment" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Sink", "bool", "Sink When Pushed" ) );
	vOut.push_back( Mocha::ObjectValueEntry( "Image", "text", "Image" ) );
}

//--------------------------------
Widget* ButtonWidget::factory( GuiManager* vManager )
{
	return new ButtonWidget( vManager );
}

}
