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

#include "RBGui/OgreSupport/OgreTexture.h"

namespace RBGui
{

//--------------------------------
OgreTexture::OgreTexture( const Ogre::TexturePtr& vTexture, bool vRenderTarget )
: mTexture( vTexture ), mRenderTarget( vRenderTarget )
{
	// ...
}

//--------------------------------
OgreTexture::~OgreTexture( )
{
	// ...
}

//--------------------------------
Mocha::String OgreTexture::getName( ) const
{
	return mTexture->getName( );
}

//--------------------------------
void* OgreTexture::lock( )
{
	return mTexture->getBuffer( )->lock( Ogre::HardwareBuffer::HBL_DISCARD );
}

//--------------------------------
void OgreTexture::unlock( )
{
	mTexture->getBuffer( )->unlock( );
}

//--------------------------------
size_t OgreTexture::getBytes( ) const
{
	return mTexture->getBuffer( )->getSizeInBytes( );
}

//--------------------------------
Mocha::Vector2 OgreTexture::getSize( ) const
{
	return Mocha::Vector2( (float)mTexture->getWidth( ), (float)mTexture->getHeight( ) );
}

//--------------------------------
bool OgreTexture::getRenderTarget( ) const
{
	return mRenderTarget;
}

//--------------------------------
void OgreTexture::resize( const Mocha::Vector2& vNewSize )
{
	Ogre::TextureManager& manager = Ogre::TextureManager::getSingleton( );

	// Reduce the log level so we don't get spammed while creating the texture

	Ogre::Log* log = Ogre::LogManager::getSingleton( ).getDefaultLog( );
	Ogre::LoggingLevel level = log->getLogDetail( );

	log->setLogDetail( Ogre::LL_LOW );

	// Get name of old texture

	Mocha::String name = mTexture->getName( );

	// Destroy existing texture

	manager.remove( mTexture->getName( ) );
	mTexture.setNull( );

	int usage = ( mRenderTarget ? Ogre::TU_RENDERTARGET : Ogre::TU_DEFAULT );

	// Create new texture with the same name

	mTexture = manager.createManual( name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
									 Ogre::TEX_TYPE_2D, (int)vNewSize.x, (int)vNewSize.y, 1, 0, Ogre::PF_R8G8B8A8, usage );

	mTexture->load( );

	// Add viewport if this is a render target

	if ( mRenderTarget )
		mTexture->getBuffer( )->getRenderTarget( )->addViewport( 0 );

	// Return the log level to previous

	log->setLogDetail( level );
}

//--------------------------------
const Ogre::TexturePtr& OgreTexture::getOgreTexture( ) const
{
	return mTexture;
}

}
