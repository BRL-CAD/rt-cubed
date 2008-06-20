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

#ifndef GUI_WOBBLEWINDOWANIMATOR_H
#define GUI_WOBBLEWINDOWANIMATOR_H

#include "RBGui/WindowAnimator.h"
#include "Mocha/Vector2.h"

#define WINDOW_TESSELATION 16

namespace RBGui
{

/// A window animator that performs a wobbly effect when moved/resized
class GUI_EXPORT WobbleWindowAnimator : public WindowAnimator
{
private:
	Mocha::Vector2 mInertia;

	Mocha::Vector2 mInertiaPoint;

	Mocha::Vector2 mDragOffset;

	float mDragStrength;

	float mResizeStrength;

	struct Vertex
	{
		Mocha::Vector2 point;

		Mocha::Vector2 uv;
	};

	Vertex mVertices[(WINDOW_TESSELATION + 1) * (WINDOW_TESSELATION + 1)];

	int mIndices[WINDOW_TESSELATION * WINDOW_TESSELATION * 6];

	bool mInertiaMode;

	void addInertia( const Mocha::Vector2& vAmount );

	void buildMesh( const Mocha::Rectangle& vRect );

public:
	WobbleWindowAnimator( );

	virtual ~WobbleWindowAnimator( );

	virtual void onTick( Window& vWindow, float vDelta );

	virtual void onMoved( Window& vWindow, const Mocha::Vector2& vAmount, const Mocha::Vector2& vMousePosition );

	virtual void onMoveStarted( Window& vWindow, const Mocha::Vector2& vMousePosition );

	virtual void onResized( Window& vWindow, const Mocha::Vector2& vAmount, const Mocha::Vector2& vMousePosition );

	virtual void onResizeStarted( Window& vWindow, const Mocha::Vector2& vMousePosition );

	virtual void onDraw( Window& vWindow, Brush& vBrush );

	void setDragStrength( float vValue );

	void setResizeStrength( float vValue );

	static WindowAnimator* factory( );
};

}

#endif
