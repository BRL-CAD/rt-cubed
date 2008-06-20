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

#ifndef GUI_OGRETEXTUREMANAGER_H
#define GUI_OGRETEXTUREMANAGER_H

#include "Ogre.h"

#include "RBGui/TextureManager.h"

#include "RBGui/OgreSupport/Defines.h"

namespace RBGui
{

class OGREGUISUPPORT_EXPORT OgreTextureManager : public TextureManager
{
public:
	OgreTextureManager( );

	virtual ~OgreTextureManager( );

	virtual Texture* createRenderTarget( const Mocha::Vector2& vSize );

	virtual Texture* createTexture( const Mocha::Vector2& vSize );

	virtual Texture* getTexture( const Mocha::String& vName );

	virtual void destroyTexture( Texture* vTexture );
};

}

#endif
