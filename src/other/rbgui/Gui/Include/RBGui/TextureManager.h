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

#ifndef GUI_TEXTUREMANAGER_H
#define GUI_TEXTUREMANAGER_H

#include "Mocha/Object.h"

namespace RBGui
{

//--------------------------------
class Mocha::Vector2;
class Texture;
class Brush;
class Font;

//--------------------------------
/// Manages the creation and loading of textures
class TextureManager : public Mocha::Object
{
public:
	/// Creates a new texture that can be used as a render target
	/*! \param vSize The size of the texture to create, in pixels
		\param vManage Whether or not the texture should be stored and managed
		\return A pointer to the new texture on success, or 0 on failure */
	virtual Texture* createRenderTarget( const Mocha::Vector2& vSize ) = 0;

	/// Creates a new blank texture
	/*! \param vSize The size of the texture to create, in pixels
		\return A pointer to the new texture on success, or 0 on failure */
	virtual Texture* createTexture( const Mocha::Vector2& vSize ) = 0;

	/// Loads a texture from a resource name
	/*! \param vName The name of the texture to load
		\return A pointer to the texture, or 0 on failure */
	virtual Texture* getTexture( const Mocha::String& vName ) = 0;

	/// Notifies the texture manager that a particular texture should be destroyed
	/*! \param vTexture The texture resource to destroy */
	virtual void destroyTexture( Texture* vTexture ) = 0;
};

}

#endif
