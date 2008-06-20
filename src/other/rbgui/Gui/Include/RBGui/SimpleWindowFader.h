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

#ifndef GUI_SIMPLEWINDOWFADER_H
#define GUI_SIMPLEWINDOWFADER_H

#include "RBGui/WindowFader.h"

namespace RBGui
{

/// A window fader that performs a simple, linear fade
class GUI_EXPORT SimpleWindowFader : public WindowFader
{
private:
	enum FadeMode
	{
		FADEMODE_NONE = 0,
		FADEMODE_FADEOUT,
		FADEMODE_FADEIN
	};

	FadeMode mMode;

	float mSpeed;

public:
	SimpleWindowFader( float vSpeed = 0.15f );

	virtual ~SimpleWindowFader( );

	virtual void onWindowClosed( Window& vWindow );

	virtual void onWindowOpened( Window& vWindow );

	virtual void onTick( Window& vWindow, float vDelta );

	virtual bool getFading( const Window& vWindow ) const;

	void setSpeed( float vValue );

	float getSpeed( ) const;

	static WindowFader* factory( );
};

}

#endif
