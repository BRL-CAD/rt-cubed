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

#ifndef GUI_WINDOWFADER_H
#define GUI_WINDOWFADER_H

#include "RBGui/GuiDefines.h"

#include "Mocha/Object.h"

namespace RBGui
{

//--------------------------------
class Window;

//--------------------------------
/// Controls how a window fades in/out
class GUI_EXPORT WindowFader : public Mocha::Object
{
public:
	WindowFader( );

	virtual ~WindowFader( );

	/// Called when a window has been closed
	/*! \param vWindow The window that was closed */
	virtual void onWindowClosed( Window& vWindow );

	/// Called when a window has been opened
	/*! \param vWindow The window that was opened */
	virtual void onWindowOpened( Window& vWindow );

	/// Called each frame to update the fade
	/*! \param vWindow The window to fade
		\param vDelta The amount of time that has passed, in seconds */
	virtual void onTick( Window& vWindow, float vDelta );

	/// Returns whether or not the class is currently fading the window
	virtual bool getFading( const Window& vWindow ) const;
};

}

#endif
