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

#include "Ogre.h"

#include "RBGui/Exception.h"
#include "RBGui/OgreSupport/OgreResourceManager.h"

namespace RBGui
{

//--------------------------------
class OgreFileStream : public Mocha::Stream
{
private:
	Ogre::DataStreamPtr mStream;

public:
	OgreFileStream( const Ogre::DataStreamPtr& vStream )
		: mStream( vStream )
	{
		// ...
	}

	virtual ~OgreFileStream( )
	{
		// ...
	}

	virtual size_t writeData( const void* vData, size_t vSize )
	{
		return 0;
	}

	virtual size_t readData( void* vData, size_t vSize ) const
	{
		return mStream->read( vData, vSize );
	}

	virtual void seek( size_t vPosition ) const
	{
		return mStream->seek( vPosition );
	}

	virtual size_t getSize( ) const
	{
		return mStream->size( );
	}

	virtual size_t getPosition( ) const
	{
		return mStream->tell( );
	}

	virtual bool getEndOfStream( ) const
	{
		return mStream->eof( );
	}
};

//--------------------------------
OgreResourceManager::OgreResourceManager( )
{
	// ...
}

//--------------------------------
OgreResourceManager::~OgreResourceManager( )
{
	// ...
}

//--------------------------------
Mocha::Stream* OgreResourceManager::getResource( const Mocha::String& vPath )
{
	try
	{
		Ogre::DataStreamPtr ptr = Ogre::ResourceGroupManager::getSingleton( ).openResource( vPath );
		return new OgreFileStream( ptr );
	}
	catch ( Ogre::Exception& )
	{
		throw Exception( "Unable to load file '" + vPath + "'" );
	}

	// Just to keep the compiler happy...

	return 0;
}

}
