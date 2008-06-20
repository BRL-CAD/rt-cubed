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

#include "Mocha/DataSection.h"

#include "RBGui/ThemeManager.h"
#include "RBGui/Core.h"

namespace RBGui
{

//--------------------------------
ThemeManager::ThemeManager( )
{
	// ...
}

//--------------------------------
ThemeManager::~ThemeManager( )
{
	// ...
}

//--------------------------------
Theme* ThemeManager::getTheme( const Mocha::String& vName )
{
	// See if theme is already loaded

	ThemeMap::const_iterator it = mThemes.find( vName );
	if ( it != mThemes.end( ) )
		return (*it).second;

	// Open theme file

	Mocha::RefPointer<Mocha::Stream> stream = Core::Get( ).getResourceManager( ).getResource( vName );

	// Parse stream

	Mocha::DataSection section;
	section.read( *stream ); 

	// Load theme from data file

	Theme* theme = new Theme( );
	theme->open( section );

	// All done!

	return theme;
}

//--------------------------------
void ThemeManager::setDefaultTheme( const Mocha::String& vName )
{
	Mocha::RefPointer<Theme> theme = getTheme( vName );
	if ( theme )
		setDefaultTheme( theme );
}

//--------------------------------
void ThemeManager::setDefaultTheme( Theme* vTheme )
{
	mDefaultTheme = vTheme;
}

//--------------------------------
Theme* ThemeManager::getDefaultTheme( ) const
{
	return mDefaultTheme;
}

}
