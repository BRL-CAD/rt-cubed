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

#include "Mocha/WeakRefPointer.h"

#include "RBGui/GuiManager.h"

#include "RBGui/Widgets/DropSplineWidget.h"

#define BUTTON_SIZE 14

namespace RBGui
{

//--------------------------------------------
DropSplineWidget::DropSplineWidget( GuiManager* vManager )
: Widget( vManager )
{
	// Create the preview spline widget

	mPreviewSpline = new SplineWidget( vManager );
	mPreviewSpline->setCallback( &DropSplineWidget::dropButtonPressed, this, "onMousePressed" );
	mPreviewSpline->setGenerated( true );

	mDropButton = new ButtonWidget( vManager );
	mDropButton->setCallback( &DropSplineWidget::dropButtonPressed, this );
	mDropButton->setAnimatedImage( true );
	mDropButton->setGenerated( true );
	mDropButton->setSink( false );

	//mDropButton->setBorderName( "DropButton" );

	attach( mPreviewSpline );
	attach( mDropButton );
}

//--------------------------------------------
DropSplineWidget::~DropSplineWidget( )
{
	if ( mDropWindow )
		mDropWindow->close( );
}

//--------------------------------------------
void DropSplineWidget::dropFocusLost( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Close the drop window

	static_cast<Window&>( vElement ).close( );
}

//--------------------------------------------
void DropSplineWidget::dropButtonPressed( GuiElement& vElement, const Mocha::ValueList& vData )
{
	createDropWindow( );
}

//--------------------------------------------
void DropSplineWidget::splineChanged( GuiElement& vElement, const Mocha::ValueList& vData )
{
	mPreviewSpline->setHandles( static_cast<SplineWidget&>( vElement ).getHandles( ) );
	doCallback( );
}

//--------------------------------------------
void DropSplineWidget::createDropWindow( )
{
	// Calculate screen space position of window

	const Mocha::Rectangle& rect = getScreenRectangle( );
	Mocha::Vector2 pos = getWindow( )->getScreenPosition( Mocha::Vector2( rect.left, rect.top + rect.getHeight( )+1 ) );
	
	// Create the window

	mDropWindow = getGuiManager( )->createWindow( );
	mDropWindow->setSize( rect.getSize( ) * Mocha::Vector2( 1.0f, 0.8f ) );
	mDropWindow->setPosition( pos );
	mDropWindow->setBorderVisible( false );
	mDropWindow->setResizeable( false );
	mDropWindow->setMovable( false );
	mDropWindow->show( );

	getGuiManager( )->setFocused( mDropWindow );

	// Setup spline

	Mocha::RefPointer<SplineWidget> spline = static_cast<SplineWidget*>( mDropWindow->createWidget( "Spline" ) );
	spline->setCallback( &DropSplineWidget::splineChanged, this );
	spline->setSize( mDropWindow->getClientRectangle( ).getSize( ) );
	spline->setHandles( mPreviewSpline->getHandles( ) );
	spline->setEditable( true );

	// Set FocusLost window callback

	mDropWindow->setCallback( &DropSplineWidget::dropFocusLost, this, "FocusLost" );
}

//--------------------------------------------
void DropSplineWidget::onRectangleChanged( )
{
	const Mocha::Rectangle& client = getClientRectangle( );

	// Calculate button size

	Mocha::Rectangle rect;
	rect.setPosition( client.getWidth( ) - BUTTON_SIZE, 0.0f );
	rect.setSize( BUTTON_SIZE, client.getHeight( ) );

	mDropButton->setRectangle( rect );

	// Resize the preview spline to fit within own rectangle

	mPreviewSpline->setSize( Mocha::Vector2( client.getWidth( ) - BUTTON_SIZE - 1, client.getHeight( ) ) );
}

//--------------------------------------------
void DropSplineWidget::onDraw( Brush& vBrush ) const
{
	// Set the drop button image

	Theme* theme = getRenderTheme( );
	if ( theme )
		mDropButton->setImage( theme->getTexture( "DropArrow" ) );
}

//--------------------------------------------
const Mocha::Vector2List& DropSplineWidget::getHandles( ) const
{
	return mPreviewSpline->getHandles( );
}

//--------------------------------------------
void DropSplineWidget::setHandles( const Mocha::Vector2List& vHandles )
{
    mPreviewSpline->setHandles( vHandles );
}

//--------------------------------------------
Mocha::String DropSplineWidget::getClassName( ) const
{
	return "DropSpline";
}

//--------------------------------------------
Widget* DropSplineWidget::factory( GuiManager* vManager )
{
	return new DropSplineWidget( vManager );
}

}
