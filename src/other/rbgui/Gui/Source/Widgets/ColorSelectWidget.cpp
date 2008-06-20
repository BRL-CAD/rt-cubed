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

#include "RBGui/Widgets/ColorSelectWidget.h"
#include "RBGui/Widgets/ColorRangeWidget.h"
#include "RBGui/Widgets/RectangleWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"
#include "RBGui/Widgets/HSVWidget.h"

#define BUTTON_SIZE 14

namespace RBGui
{

//--------------------------------
ColorSelectWidget::ColorSelectWidget( GuiManager* vManager )
: Widget( vManager ), mAlphaRange( 0 ), mDropHSV( 0 ), mHueRange( 0 ), mDropRect( 0 )
{
	mColorRect = new RectangleWidget( vManager );
	mColorRect->setCallback( &ColorSelectWidget::dropButtonPressed, this, "onMousePressed" );
	mColorRect->setBorder( "ColorSelectWidget" );
	mColorRect->setCheckered( true );
	mColorRect->setGenerated( true );

	mDropButton = new ButtonWidget( vManager );
	mDropButton->setCallback( &ColorSelectWidget::dropButtonPressed, this );
	mDropButton->setAnimatedImage( true );
	mDropButton->setGenerated( true );
	mDropButton->setSink( false );

	attach( mColorRect );
	attach( mDropButton );
}

//--------------------------------
ColorSelectWidget::~ColorSelectWidget( )
{
	if ( mDropWindow )
		mDropWindow->close( );
}

//--------------------------------
void ColorSelectWidget::dropButtonPressed( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	const float padding = 2.0f;

	// Create the drop window

	const Mocha::Rectangle& rect = getScreenRectangle( );
	Mocha::Vector2 pos = getWindow( )->getScreenPosition( Mocha::Vector2( rect.left, rect.top + rect.getHeight( )+1 ) );

	mDropWindow = getGuiManager( )->createWindow( );
	mDropWindow->setCallback( &ColorSelectWidget::dropFocusLost, this, "FocusLost" );
	mDropWindow->setBorder( "DropWindow" );
	mDropWindow->setPosition( pos );
	mDropWindow->setSize( Mocha::Vector2( getRectangle( ).getWidth( ), 100.0f ) );
	mDropWindow->setResizeable( false );
	mDropWindow->setMovable( false );
	mDropWindow->show( );

	getGuiManager( )->setFocused( mDropWindow );

	/*win->setTheme( mWindow->getTheme( ) );
	win->setScaleX( mWindow->getScaleX( ) );
	win->setScaleY( mWindow->getScaleY( ) );
	win->setOrderMode( WINDOWORDER_ALWAYSONTOP );
	win->setConstrained( true );*/

	// Setup the color palette image

	const Mocha::Rectangle& client = mDropWindow->getClientRectangle( );

	float width = client.getWidth( );
	float height = client.getHeight( );

	// Setup the color palette image

	mDropHSV = new HSVWidget( getGuiManager( ) );
	mDropHSV->setBorder( "ColorSelectWidget" );
	mDropHSV->setCallback( &ColorSelectWidget::hsvPicked, this );
	mDropHSV->setRectangle( padding, padding, width-22-padding, height-22-padding );

	mDropWindow->getRoot( )->addChild( mDropHSV );

	// Setup color rectangle

	mDropRect = new RectangleWidget( getGuiManager( ) );
	mDropRect->setBorder( "ColorSelectWidget" );
	mDropRect->setColor( getColor( ) );
	mDropRect->setRectangle( width-20-padding, height-20-padding, 20, 20 );
	mDropRect->setCheckered( true );

	mDropWindow->getRoot( )->addChild( mDropRect );

	// Setup the hue range

	mHueRange = new ColorRangeWidget( getGuiManager( ) );
	mHueRange->setRectangle( width - 20, 0, 20, height - 21 );
	mHueRange->setCallback( &ColorSelectWidget::hueChanged, this );
	
	mHueRange->addRange( Mocha::Color( 1.0f, 0.0f, 0.0f, 1.0f ),
						 Mocha::Color( 1.0f, 0.0f, 1.0f, 1.0f ) );

	mHueRange->addRange( Mocha::Color( 1.0f, 0.0f, 1.0f, 1.0f ),
						 Mocha::Color( 0.0f, 0.0f, 1.0f, 1.0f ) );

	mHueRange->addRange( Mocha::Color( 0.0f, 0.0f, 1.0f, 1.0f ),
						 Mocha::Color( 0.0f, 1.0f, 1.0f, 1.0f ) );

	mHueRange->addRange( Mocha::Color( 0.0f, 1.0f, 1.0f, 1.0f ),
						 Mocha::Color( 0.0f, 1.0f, 0.0f, 1.0f ) );

	mHueRange->addRange( Mocha::Color( 0.0f, 1.0f, 0.0f, 1.0f ),
						 Mocha::Color( 1.0f, 1.0f, 0.0f, 1.0f ) );

	mHueRange->addRange( Mocha::Color( 1.0f, 1.0f, 0.0f, 1.0f ),
						 Mocha::Color( 1.0f, 0.0f, 0.0f, 1.0f ) );

	mDropWindow->getRoot( )->addChild( mHueRange );

	// Set hue, sat, lum from color select widget

	float h;
	float s;
	float v;

	const Mocha::Color& c = getColor( );
	c.getHSV( h, s, v );

	mHueRange->setValue( 1.0f - h );
	mDropRect->setColor( c );
	
	mDropHSV->setHue( h );
	mDropHSV->setPoint( Mocha::Vector2( v, 1.0f - s ) );

	// Setup the alpha range

	mAlphaRange = new ColorRangeWidget( getGuiManager( ) );
	mAlphaRange->setCallback( &ColorSelectWidget::alphaChanged, this );
	mAlphaRange->setRectangle( 0, height - 20, width - 21, 20 );
	mAlphaRange->setValue( c.a );

	mDropWindow->getRoot( )->addChild( mAlphaRange );

	Mocha::Color c2 = c;
	c2.a = 0.0f;

	Mocha::Color c3 = c;
	c3.a = 1.0f;

	mAlphaRange->addRange( c2, c3 );
}

//--------------------------------
void ColorSelectWidget::updateDropWidgets( )
{
	const Mocha::Color& c = getColor( );

	// Change color of alpha range

	Mocha::Color c2 = c;
	c2.a = 0.0f;

	Mocha::Color c3 = c;
	c3.a = 1.0f;

	mAlphaRange->clear( );
	mAlphaRange->addRange( c2, c3 );

	// Set final color on rectangle

	mDropRect->setColor( c );
}

//--------------------------------
void ColorSelectWidget::dropFocusLost( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	// Close the drop window

	static_cast<Window&>( vElement ).close( );
}

//--------------------------------
void ColorSelectWidget::hsvPicked( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	Mocha::Color c = mDropHSV->getColor( );
	c.a = mAlphaRange->getValue( );

	setColor( c );
	updateDropWidgets( );
}

//--------------------------------
void ColorSelectWidget::hueChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	mDropHSV->setHue( 1.0f - mHueRange->getValue( ) );

	Mocha::Color c = mDropHSV->getColor( );
	c.a = mAlphaRange->getValue( );

	setColor( c );
	updateDropWidgets( );
}

//--------------------------------
void ColorSelectWidget::alphaChanged( GuiElement& vElement, const Mocha::ValueList& vValues )
{
	Mocha::Color c = mDropHSV->getColor( );
	c.a = mAlphaRange->getValue( );

	setColor( c );
	updateDropWidgets( );
}

//--------------------------------
void ColorSelectWidget::onRectangleChanged( )
{
	// Calculate size of color and button rect

	const Mocha::Rectangle& client = getClientRectangle( );

	mColorRect->setSize( Mocha::Vector2( client.getWidth( ) - BUTTON_SIZE - 1, client.getHeight( ) ) );

	Mocha::Rectangle rect;
	rect.setPosition( client.getWidth( ) - BUTTON_SIZE, 0.0f );
	rect.setSize( BUTTON_SIZE, client.getHeight( ) );

	mDropButton->setRectangle( rect );
}

//--------------------------------
void ColorSelectWidget::onDraw( Brush& vBrush ) const
{
	// Set image on drop button widget

	Theme* theme = getRenderTheme( );
	if ( theme )
		mDropButton->setImage( theme->getTexture( "DropArrow" ) );
}

//--------------------------------
void ColorSelectWidget::onColorChanged( )
{
	const Mocha::Color& color = getColor( );
	mColorRect->setColor( color );

	Mocha::ValueList v;
	v.push_back( color );

	doCallback( v );
}

//--------------------------------
Mocha::String ColorSelectWidget::getClassName( ) const
{
	return "ColorSelect";
}

//--------------------------------
Widget* ColorSelectWidget::factory( GuiManager* vManager )
{
	return new ColorSelectWidget( vManager );
}

}
