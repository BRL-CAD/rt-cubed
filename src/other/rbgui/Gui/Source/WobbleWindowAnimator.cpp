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

#include "RBGui/WobbleWindowAnimator.h"
#include "RBGui/Window.h"
#include "RBGui/Brush.h"

#define WINDOW_TESSELATION 16
#define DRAG_SPEED 4

namespace RBGui
{

//--------------------------------
WobbleWindowAnimator::WobbleWindowAnimator( )
: mDragStrength( 0.001f ), mResizeStrength( 0.0009f ), mInertiaMode( false )
{
	// Setup indices

	size_t i = 0;

	size_t x;
	for( x = 0; x < WINDOW_TESSELATION; x ++ )
	{
		size_t y;
		for( y = 0; y < WINDOW_TESSELATION; y ++ )
		{
            mIndices[i++] = x + (y * (WINDOW_TESSELATION+1));
			mIndices[i++] = (x+1) + (y * (WINDOW_TESSELATION+1));
			mIndices[i++] = x + ((y+1) * (WINDOW_TESSELATION+1));
			mIndices[i++] = x + ((y+1) * (WINDOW_TESSELATION+1));
			mIndices[i++] = (x+1) + (y * (WINDOW_TESSELATION+1));
			mIndices[i++] = (x+1) + ((y+1) * (WINDOW_TESSELATION+1));
		}
	}
}

//--------------------------------
WobbleWindowAnimator::~WobbleWindowAnimator( )
{
	// ...
}

//--------------------------------
void WobbleWindowAnimator::setDragStrength( float vValue )
{
	mDragStrength = vValue;
}

//--------------------------------
void WobbleWindowAnimator::setResizeStrength( float vValue )
{
	mResizeStrength = vValue;
}

//--------------------------------
void WobbleWindowAnimator::addInertia( const Mocha::Vector2& vAmount )
{
	const float clampFactor = 50.0f;

    mInertia = mInertia + vAmount;
	if ( mInertia.length( ) > clampFactor )
		mInertia.setLength( clampFactor );
}

//--------------------------------
void WobbleWindowAnimator::onTick( Window& vWindow, float vDelta )
{
	// Clamp delta

	vDelta = Mocha::min( 0.05f, vDelta );

	Mocha::Vector2 previousdrag = mDragOffset;
	mDragOffset = mDragOffset + mInertia * 5.0f * DRAG_SPEED * vDelta;
	
	mInertia += (mInertia * -5 * DRAG_SPEED * vDelta);
	mInertia += (previousdrag * -4.0f * DRAG_SPEED * vDelta);
}

//--------------------------------
void WobbleWindowAnimator::onMoved( Window& vWindow, const Mocha::Vector2& vAmount, const Mocha::Vector2& vMousePosition )
{
	addInertia( Mocha::Vector2( -vAmount.x, vAmount.y ) );
}

//--------------------------------
void WobbleWindowAnimator::onMoveStarted( Window& vWindow, const Mocha::Vector2& vMousePosition )
{
	mInertiaPoint = vMousePosition / vWindow.getSize( );
	mInertiaMode = false;
}

//--------------------------------
void WobbleWindowAnimator::onResized( Window& vWindow, const Mocha::Vector2& vAmount, const Mocha::Vector2& vMousePosition )
{
	addInertia( Mocha::Vector2( -vAmount.x, vAmount.y ) );
}

//--------------------------------
void WobbleWindowAnimator::onResizeStarted( Window& vWindow, const Mocha::Vector2& vMousePosition )
{
	mInertiaMode = true;
}

//--------------------------------
void WobbleWindowAnimator::buildMesh( const Mocha::Rectangle& vRect )
{
	float wleft = vRect.left;
	float wtop = vRect.top;
	float wwidth = vRect.getWidth( );
	float wheight = vRect.getHeight( );

	const Mocha::Vector2& drag = mDragOffset;
	const Mocha::Vector2& point = mInertiaPoint;
	bool iMode = mInertiaMode;

	size_t count = 0;

	int rx;
	for( rx = 0; rx < WINDOW_TESSELATION + 1; rx++ )
	{
		int ry;
		for( ry = 0; ry < WINDOW_TESSELATION + 1; ry++ )
		{
			float px = rx / (float)WINDOW_TESSELATION;
			float py = ry / (float)WINDOW_TESSELATION;

			float fx = wleft + wwidth * px;
			float fy = wtop + wheight * py;

			float drageffect = 0;
			if( iMode )
			{
				Mocha::Vector2 cp( px, py );
				float drageffect1 = cp.squaredDistance( Mocha::Vector2( 0, 0 ) ) * mResizeStrength;
				float drageffect2 = cp.squaredDistance( Mocha::Vector2( 1, 1 ) ) * mResizeStrength;

				if( drageffect1 < drageffect2 )
					drageffect = drageffect1;
				else
					drageffect = drageffect2;
			}
			else
			{
				drageffect = point.squaredDistance( Mocha::Vector2( px, py ) ) * mDragStrength;
			}

			Mocha::Vector2 vert( fx + drag.x * drageffect, fy + drag.y * drageffect );
			Mocha::Vector2 uv( px, py );

			mVertices[count].point = vert;
			mVertices[count].uv = uv;

			count++;
		}
	}
}

//--------------------------------
void WobbleWindowAnimator::onDraw( Window& vWindow, Brush& vBrush )
{
	// Build mesh

	buildMesh( vBrush.getScreenRectangle( vWindow.getRectangle( ) ) );

	// Output mesh to brush

	vBrush.setColor( Mocha::Color( 1.0f, 1.0f, 1.0f, vWindow.getOpacity( ) ) );
	vBrush.setFilterMode( BRUSHFILTER_LINEAR );
	vBrush.setTexture( vWindow.getTarget( ) );

	if ( mDragOffset.squaredLength( ) >= 0.3f )
	{
		vBrush.beginTriangles( );

		int x;
		for ( x = 0; x < (WINDOW_TESSELATION * WINDOW_TESSELATION * 6); x++ )
		{
			int index = mIndices[x];
			vBrush.addTriangleVertex( mVertices[index].point, mVertices[index].uv, true );
		}

		vBrush.endTriangles( );
	}
	else
		vBrush.drawRectangle( vWindow.getRectangle( ) );
}

//--------------------------------
WindowAnimator* WobbleWindowAnimator::factory( )
{
	return new WobbleWindowAnimator( );
}

}
