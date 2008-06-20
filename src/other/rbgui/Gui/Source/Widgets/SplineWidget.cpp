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

#include "RBGui/Widgets/SplineWidget.h"

namespace RBGui
{

//--------------------------------
SplineWidget::SplineWidget( GuiManager* vManager )
: Widget( vManager ), mDragging( false ), mEditable( false ), mDraggingHandle( 0 )
{
	mHandles.push_back( Mocha::Vector2( 0.0f, 0.0f ) );
	mHandles.push_back( Mocha::Vector2( 0.2f, 0.33f ) );
	mHandles.push_back( Mocha::Vector2( 0.8f, 0.66f ) );
	mHandles.push_back( Mocha::Vector2( 1.0f, 1.0f ) );
}

//--------------------------------
SplineWidget::~SplineWidget( )
{
	// ...
}

//--------------------------------
CursorType SplineWidget::getCursor( ) const
{
	return ( mEditable ? CURSOR_CROSS : CURSOR_DEFAULT );
}

//--------------------------------
void SplineWidget::setHandles( const Mocha::Vector2List& vHandles )
{
	mHandles = vHandles;
	flagDirty( );
}

//--------------------------------
bool SplineWidget::isFlipped() const
{
	const Mocha::Rectangle& client = getClientRectangle( );

	if( client.getWidth( ) > client.getHeight( ) )
		return true;
	
	return false;
}

//--------------------------------
Mocha::Vector2 SplineWidget::flipIfFlipped( const Mocha::Vector2& vA ) const
{
	if( isFlipped() )
	{
		Mocha::Vector2 vB;
		vB.x = vA.y;
		vB.y = 1.0f - vA.x;
		return vB;
	}
	return vA;
}

//--------------------------------
void SplineWidget::onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	if( mEditable == false )
		return;

	const Mocha::Rectangle& client = getClientRectangle( );
	
	// Delete if right-click
	if( vID == MOUSEBUTTON_RIGHT )
	{
		for( int a = 1; a < mHandles.size() - 1; a ++ )
		{
			Mocha::Vector2 Point = flipIfFlipped( mHandles[a] );
			Mocha::Vector2 Diff = Mocha::Vector2(Point.x * client.getWidth(), Point.y * client.getHeight()) - vPoint;
			if( Diff.length() < 10 )
			{
				mHandles.erase( mHandles.begin() + a );
				mDragging = false;
				flagDirty();
				return;
			}
		}
		return;
	}

	// Select for dragging if left-click (and in range)
	for( int a = 0; a < mHandles.size(); a ++ )
	{
		Mocha::Vector2 Point = flipIfFlipped( mHandles[a] );
		Mocha::Vector2 Diff = Mocha::Vector2(Point.x * client.getWidth(), Point.y * client.getHeight()) - vPoint;
		if( Diff.length() < 10 )
		{
            mDraggingHandle = a;
			mDragging = true;
			return;
		}
	}

	// Didn't hit a handle.. create one?
	for( int a = (int)mHandles.size() - 1; a >= 0; a -- )
	{
		bool found = false;
		if( isFlipped() )
		{
            if( mHandles[a].y * client.getWidth() < vPoint.x )
			{
				mHandles.insert(mHandles.begin() + a+1, Mocha::Vector2( 1-(vPoint.y / client.getHeight()), vPoint.x / client.getWidth() ));
				found = true;
			}
		}
		else
		{
			if( mHandles[a].y * client.getHeight() < vPoint.y )
			{
				mHandles.insert(mHandles.begin() + a+1, Mocha::Vector2( vPoint.x / client.getWidth(), vPoint.y / client.getHeight() ));
				found = true;
			}
		}

		if( found )
		{
			mDraggingHandle = a+1;
			mDragging = true;
			flagDirty();
			return;
		}
	}
}

//--------------------------------
void SplineWidget::onMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	mDragging = false;
	doCallback( );
}

//--------------------------------
void SplineWidget::onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint )
{
	if( mEditable == false )
		return;

	if( mDragging )
	{
		const Mocha::Rectangle& client = getClientRectangle( );
		Mocha::Vector2& handle = mHandles[mDraggingHandle];

		if( isFlipped() )
		{
			handle.x -= vRelative.y / client.getHeight();
			handle.y += vRelative.x / client.getWidth();
		}
		else
		{
			handle.x += vRelative.x / client.getWidth();
			handle.y += vRelative.y / client.getHeight();
		}
		if( mDraggingHandle == 0 )
		{
			// if first, force it to 0
			handle.y = 0;
		}
		else if( mDraggingHandle == mHandles.size() - 1 )
		{
			// if last, force to 1.
			handle.y = 1;
		}
		else
		{
			// Don't allow it too close to prior or next entry.
			handle.y = Mocha::max( handle.y,  mHandles[mDraggingHandle-1].y );
			handle.y = Mocha::min( handle.y,  mHandles[mDraggingHandle+1].y );
		}

		handle.x = Mocha::max( handle.x, 0.0f );
		handle.x = Mocha::min( handle.x, 1.0f );

		flagDirty( );
	}
}

//--------------------------------
void SplineWidget::onDraw( Brush& vBrush ) const
{
	const Mocha::Rectangle& client = getClientRectangle( );
	Mocha::Spline2 Spline;

	vBrush.setColor( Mocha::Color( 0.0f, 0.0f, 0.0f, 0.3f ) );
	vBrush.setBlendMode( BRUSHBLEND_ALPHA );
	vBrush.setTexture( 0 );

	if( mEditable )
	{
		vBrush.beginLines( );

		// Render Grid
		for( float a = 0.25f; a < 1; a += 0.25f )
		{
			Mocha::Vector2 PointA = Mocha::Vector2( a * client.getWidth(), 0);
			Mocha::Vector2 PointB = Mocha::Vector2( a * client.getWidth(), client.getHeight() );
			vBrush.addLine( client.getPosition( ) + PointA, client.getPosition( ) + PointB );

			PointA = Mocha::Vector2( 0, a * client.getHeight());
			PointB = Mocha::Vector2( client.getWidth(), a * client.getHeight() );
			vBrush.addLine( client.getPosition( ) + PointA, client.getPosition( ) + PointB );
		}
		vBrush.endLines( );
	}

	// Setup Splines

	Mocha::Vector2List::const_iterator i;
	for( i = mHandles.begin( ); i < mHandles.end( ); i ++ )
	{
		// Scale to fill widget
		Mocha::Vector2 ThisHandle = flipIfFlipped(*i);
		ThisHandle.x = ThisHandle.x * (client.getWidth() - 1);
		ThisHandle.y = ThisHandle.y * (client.getHeight() - 1) + 1;

		Spline.addPoint( ThisHandle );
	}

	if( mEditable )
	{
		// Render untesellated 'base'
		Mocha::Vector2List& SplinePoints2 = Spline.tessellate( 0 );

		vBrush.setColor( Mocha::Color(0.0f, 0.0f, 0.0f, 0.2f) );
		vBrush.setBlendMode( BRUSHBLEND_ALPHA );

		vBrush.beginLines();

		Mocha::Vector2List::const_iterator i;
		for( i = SplinePoints2.begin(); i < SplinePoints2.end() - 1; i ++ )
		{
			Mocha::Vector2 PointA = *i;
			Mocha::Vector2 PointB = *(i+1);

			vBrush.addLine( client.getPosition( ) + PointA, client.getPosition( ) + PointB );
		}

		vBrush.endLines();
	}

	// Render high-res 'final'
	Mocha::Vector2List& SplinePoints = Spline.tessellate( 3 );

	vBrush.setColor( Mocha::Color::Red );
	vBrush.setBlendMode( BRUSHBLEND_ALPHA );

	vBrush.beginLines();

	for( i = SplinePoints.begin(); i < SplinePoints.end() - 1; i ++ )
	{
		Mocha::Vector2 PointA = *i;
		Mocha::Vector2 PointB = *(i+1);

		vBrush.addLine( client.getPosition( ) + PointA, client.getPosition( ) + PointB );
	}
	vBrush.endLines();

	if( mEditable )
	{
		// Render Handles

		Mocha::Vector2List::const_iterator i;
		for( i = mHandles.begin(); i < mHandles.end(); i ++ )
		{
			vBrush.setColor( Mocha::Color::Blue );
			vBrush.setBlendMode( BRUSHBLEND_ALPHA );

			Mocha::Vector2 Point = flipIfFlipped( *i );

			Mocha::Rectangle Rect;
			Rect.setPosition( Point.x * client.getWidth() - 2 + client.getPosition( ).x, Point.y * client.getHeight() - 2 + client.getPosition( ).y );
			Rect.setSize( 5, 5 );

			vBrush.drawRectangle( Rect );
		}
	}
}

//--------------------------------
float SplineWidget::sample( float vY )
{
	// Eventally, we'll want to cache mSpline unless it changes.  for now, we'll just rebuild it each time.
	mSpline.clear();
	for( Mocha::Vector2List::iterator i = mHandles.begin(); i < mHandles.end(); i ++ )
	{
        mSpline.addPoint( *i );
	}

	mSpline.tessellate( 4 );
    
	return mSpline.sampleY( vY );
}

//--------------------------------
const Mocha::Vector2List& SplineWidget::getHandles( ) const
{
    return mHandles;
}

//--------------------------------
void SplineWidget::addHandle( const Mocha::Vector2& vPoint )
{
	mHandles.push_back( vPoint );
	flagDirty( );
}

//--------------------------------
void SplineWidget::clearHandles( )
{
	mHandles.clear( );
	flagDirty( );
}

//--------------------------------
void SplineWidget::insertHandle( int vAfter, Mocha::Vector2& vPoint )
{
    mHandles.insert( mHandles.begin() + vAfter, vPoint );
	flagDirty( );
}

//--------------------------------
void SplineWidget::removeHandle( int vIndex )
{
    mHandles.erase( mHandles.begin() + vIndex );
	flagDirty( );
}

//--------------------------------
void SplineWidget::setEditable( bool vEditable )
{
    mEditable = vEditable;
	flagDirty( );
}

//--------------------------------
bool SplineWidget::getEditable( ) const
{
	return mEditable;
}

//--------------------------------
void SplineWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Editable", "bool", "Editable" ) );
}

//--------------------------------
Mocha::CommandResult SplineWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setEditable" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		setEditable( vIn[0].getAsBool( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getEditable" )
	{
		vOut.push_back( getEditable( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
Mocha::String SplineWidget::getClassName( ) const
{
	return "Spline";
}

//--------------------------------
Widget* SplineWidget::factory( GuiManager* vManager )
{
	return new SplineWidget( vManager );
}

}
