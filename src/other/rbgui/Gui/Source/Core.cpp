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

#include "RBGui/Core.h"
#include "RBGui/Exception.h"

namespace RBGui
{

//--------------------------------
static Core* ptr = 0;

//--------------------------------
Core::Core( TextureManager* vTextureManager, PlatformManager* vPlatformManager, ResourceManager* vResourceManager, Brush* vDefaultBrush )
: mResourceManager( vResourceManager ), mTextureManager( vTextureManager ), mPlatformManager( vPlatformManager ), mDefaultBrush( vDefaultBrush )
{
	ptr = this;

	// Create theme manager

	mThemeManager = new ThemeManager( );

	// Create font manager

	mFontManager = new FontManager( );
}

//--------------------------------
Core::~Core( )
{
	// Destory all GUIs

	mGuis.clear( );
}

//--------------------------------
void Core::tick( float vDelta )
{
	GuiMap::const_iterator it;
	for ( it = mGuis.begin( ); it != mGuis.end( ); it++ )
		(*it).second->tick( vDelta );
}

//--------------------------------
void Core::invalidate( )
{
	GuiMap::const_iterator it;
	for ( it = mGuis.begin( ); it != mGuis.end( ); it++ )
		(*it).second->invalidate( );
}

//--------------------------------
void Core::draw( )
{
	GuiMap::const_iterator it;
	for ( it = mGuis.begin( ); it != mGuis.end( ); it++ )
		(*it).second->draw( );
}

//--------------------------------
GuiManager* Core::createGui( const Mocha::String& vName, Brush* vBrush )
{
	Mocha::RefPointer<GuiManager> gui = new GuiManager( ( vBrush == 0 ) ? mDefaultBrush : vBrush );
	mGuis[vName] = gui;

	return gui;
}

//--------------------------------
GuiManager* Core::getGui( const Mocha::String& vName )
{
	GuiMap::const_iterator it = mGuis.find( vName );
	if ( it != mGuis.end( ) )
		return (*it).second;

	throw Exception( "No Gui named '" + vName + "'" );
}

//--------------------------------
void Core::destroyGui( const Mocha::String& vName )
{
	GuiMap::iterator it = mGuis.find( vName );
	if ( it != mGuis.end( ) )
		mGuis.erase( it );
}

//--------------------------------
ResourceManager& Core::getResourceManager( )
{
	return *mResourceManager;
}

//--------------------------------
PlatformManager& Core::getPlatformManager( )
{
	return *mPlatformManager;
}

//--------------------------------
TextureManager& Core::getTextureManager( )
{
	return *mTextureManager;
}

//--------------------------------
ThemeManager& Core::getThemeManager( )
{
	return *mThemeManager;
}

//--------------------------------
FontManager& Core::getFontManager( )
{
	return *mFontManager;
}

//--------------------------------
Core& Core::Get( )
{
	return *ptr;
}

}
