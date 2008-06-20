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

#ifndef GUI_TEXTURE_H
#define GUI_TEXTURE_H

#include "Mocha/Object.h"

#include "RBGui/GuiDefines.h"

namespace RBGui
{

//--------------------------------
/// Wrapper class around an API dependent texture resource
class Texture : public Mocha::Object
{
public:
	/// The string version of a texture is its resource name
	virtual Mocha::String getAsString( ) const
	{
		return getName( );
	}

	/// Locks the texture and returns a pointer to the pixel data
	/*! \return A pointer to the pixel data buffer */
	virtual void* lock( ) = 0;

	/// Unlocks the texture after a lock operation
	virtual void unlock( ) = 0;

	/// Returns the number of bytes in the texture data
	virtual size_t getBytes( ) const = 0;

	/// Gets the size of the texture, in pixels
	/*! \return A Mocha::Vector2 containing the size of the texture in pixels */
	virtual Mocha::Vector2 getSize( ) const = 0;

	/// Returns whether or not the texture can be rendered to
	/*! \return True if the texture is a render target, false if not */
	virtual bool getRenderTarget( ) const = 0;

	///  Returns the name of the texture
	/*! \return The string name of the texture */
	virtual Mocha::String getName( ) const = 0;

	/// Resizes the texture
	/*! \param vNewSize The new size, in pixels, that the texture should be resized to */
	virtual void resize( const Mocha::Vector2& vNewSize ) = 0;
};

}

#endif
