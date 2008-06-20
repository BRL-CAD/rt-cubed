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

#ifndef GUI_WINDOWANIMATOR_H
#define GUI_WINDOWANIMATOR_H

#include "RBGui/GuiDefines.h"

#include "Mocha/Object.h"

namespace RBGui
{

//--------------------------------
class Window;
class Brush;

//--------------------------------
/// Animates a window
class GUI_EXPORT WindowAnimator : public Mocha::Object
{
public:
	WindowAnimator( );

	virtual ~WindowAnimator( );

	/// Called each frame to update the animation
	/*! \param vWindow The window that owns the animator
		\param vDelta The amount of time that has passed, in seconds */
	virtual void onTick( Window& vWindow, float vDelta );

	/// Called when the user has moved the window
	/*! \param vWindow The window that owns the animator
		\param vAmount The relative amount, in pixels, of the movement
		\param vMousePosition The position of the mouse in window-space */
	virtual void onMoved( Window& vWindow, const Mocha::Vector2& vAmount, const Mocha::Vector2& vMousePosition );

	/// Called when the user starts to move the window
	/*! \param vWindow The window that owns the animator
		\param vMousePosition The position of the mouse in window-space */
	virtual void onMoveStarted( Window& vWindow, const Mocha::Vector2& vMousePosition );

	/// Called when the user has resized the window
	/*! \param vWindow The window that owns the animator
		\param vAmount The relative amount, in pixels, of the resize
		\param vMousePosition The position of the mouse in window-space */
	virtual void onResized( Window& vWindow, const Mocha::Vector2& vAmount, const Mocha::Vector2& vMousePosition );

	/// Called when the user starts to resize the window
	/*! \param vWindow The window that owns the animator
		\param vMousePosition The position of the mouse in window-space */
	virtual void onResizeStarted( Window& vWindow, const Mocha::Vector2& vMousePosition );

	/// Called by the GuiManager to draw the window
	/*! \param vWindow The window that owns the animator
		\param vBrush The brush to use for drawing */
	virtual void onDraw( Window& vWindow, Brush& vBrush );
};

}

#endif
