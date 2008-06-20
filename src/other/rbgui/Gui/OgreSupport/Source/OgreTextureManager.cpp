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

#include "Mocha/Vector2.h"
#include "RBGui/Exception.h"

#include "RBGui/OgreSupport/OgreTextureManager.h"
#include "RBGui/OgreSupport/OgreTexture.h"

namespace RBGui
{

//--------------------------------
OgreTextureManager::OgreTextureManager( )
{
	// ...
}

//--------------------------------
OgreTextureManager::~OgreTextureManager( )
{
	// ...
}

//--------------------------------
Texture* OgreTextureManager::createRenderTarget( const Mocha::Vector2& vSize )
{
	try
	{
		// Reduce the log level so we don't get spammed while creating the texture

		Ogre::Log* log = Ogre::LogManager::getSingleton( ).getDefaultLog( );
		Ogre::LoggingLevel level = log->getLogDetail( );

		log->setLogDetail( Ogre::LL_LOW );

		// Setup name to use

		static size_t texCount = 0;

		std::ostringstream s;
		s << "Gui_Target_" << texCount++;

		// Create texture

		Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton( ).createManual( s.str( ), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
																				   Ogre::TEX_TYPE_2D, (int)vSize.x, (int)vSize.y, 1, 0, Ogre::PF_R8G8B8A8, Ogre::TU_RENDERTARGET );

		// Add a single viewport

		tex->getBuffer( )->getRenderTarget( )->addViewport( 0 );

		// Return the log level to previous

		log->setLogDetail( level );

		// Return Ogre texture wrapper

		return new OgreTexture( tex, true );
	}
	catch ( Ogre::Exception& )
	{
		throw Exception( "Unable to create render target" );
	}
}

//--------------------------------
Texture* OgreTextureManager::createTexture( const Mocha::Vector2& vSize )
{
	try
	{
		// Setup name to use

		static size_t texCount = 0;

		std::ostringstream s;
		s << "Gui_Texture_" << texCount++;

		// Create texture

		Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton( ).createManual( s.str( ), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
																				   Ogre::TEX_TYPE_2D, (int)vSize.x, (int)vSize.y, 1, 0, Ogre::PF_R8G8B8A8, Ogre::TU_DEFAULT );

		// Return Ogre texture wrapper

		return new OgreTexture( tex, false );
	}
	catch ( Ogre::Exception& )
	{
		throw Exception( "Unable to create texture" );
	}
}

//--------------------------------
Texture* OgreTextureManager::getTexture( const Mocha::String& vName )
{
	// Load texture

	try
	{
		Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton( ).load( vName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, 0 );
		return new OgreTexture( tex, false );
	}
	catch ( Ogre::Exception& )
	{
		throw Exception( "Unable to get texture '" + vName + "'" );
	}
}

//--------------------------------
void OgreTextureManager::destroyTexture( Texture* vTexture )
{
	// Tell the Ogre texture manager to destroy the texture

	Ogre::TextureManager::getSingleton( ).remove( static_cast<OgreTexture*>( vTexture )->getOgreTexture( )->getName( ) );
}

}
