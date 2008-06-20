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

#include "Mocha/Math.h"

#include "RBGui/SimpleWindowFader.h"
#include "RBGui/Window.h"

namespace RBGui
{

//--------------------------------
SimpleWindowFader::SimpleWindowFader( float vSpeed )
: mMode( FADEMODE_NONE ), mSpeed( vSpeed )
{
	// ...
}

//--------------------------------
SimpleWindowFader::~SimpleWindowFader( )
{
	// ...
}

//--------------------------------
void SimpleWindowFader::setSpeed( float vValue )
{
	mSpeed = vValue;
}

//--------------------------------
float SimpleWindowFader::getSpeed( ) const
{
	return mSpeed;
}

//--------------------------------
void SimpleWindowFader::onWindowClosed( Window& vWindow )
{
	mMode = FADEMODE_FADEOUT;
}

//--------------------------------
void SimpleWindowFader::onWindowOpened( Window& vWindow )
{
	mMode = FADEMODE_FADEIN;
}

//--------------------------------
void SimpleWindowFader::onTick( Window& vWindow, float vDelta )
{
	switch ( mMode )
	{
	case FADEMODE_FADEIN:
		{
			float opacity = vWindow.getOpacity( );

			opacity = Mocha::saturate( ( mSpeed > 0.0f ) ? opacity + ((1.0f/mSpeed) * vDelta) : 1.0f );
			vWindow.setOpacity( opacity );

			if ( opacity >= 1.0f )
				mMode = FADEMODE_NONE;
		}
		break;

	case FADEMODE_FADEOUT:
		{
			float opacity = vWindow.getOpacity( );

			opacity = Mocha::saturate( ( mSpeed > 0.0f ) ? opacity - ((1.0f/mSpeed) * vDelta) : 0.0f );
			vWindow.setOpacity( opacity );

			if ( opacity <= 0.0f )
				mMode = FADEMODE_NONE;
		}
		break;
	}
}

//--------------------------------
bool SimpleWindowFader::getFading( const Window& vWindow ) const
{
	return ( mMode != FADEMODE_NONE );
}

//--------------------------------
WindowFader* SimpleWindowFader::factory( )
{
	return new SimpleWindowFader( );
}

}
