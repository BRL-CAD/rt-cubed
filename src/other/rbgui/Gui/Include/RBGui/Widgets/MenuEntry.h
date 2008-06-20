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

#ifndef OLIVIA_MENUENTRY_H
#define OLIVIA_MENUENTRY_H

#include "RBGui/Platform.h"

#include <vector>

namespace RBGui
{

//--------------------------------
class MenuEntry
{
private:
	typedef std::pair<Mocha::String, MenuEntry> EntryIndex;
	typedef std::vector<EntryIndex> MenuList;

	MenuList mChildren;

	Mocha::String mName;

	Mocha::String mText;

	Mocha::String mID;

public:
	inline MenuEntry( const Mocha::String& vName, const Mocha::String& vID )
		: mName( vName ), mID( vID )
	{
		// ...
	}

	inline MenuEntry( )
	{
		// ...
	}

	inline MenuEntry& getEntry( const Mocha::String& vName )
	{
		// Look for existing entry

		if ( vName != "-" )
		{
			MenuList::iterator it;
			for ( it = mChildren.begin( ); it != mChildren.end( ); it++ )
			{
				if ( (*it).first == vName )
					return (*it).second;
			}
		}

		// Add new entry

		mChildren.push_back( EntryIndex( vName, MenuEntry( ) ) );
		return mChildren.back( ).second;
	}

	inline const MenuEntry& getEntry( size_t vIndex ) const
	{
		return mChildren[vIndex].second;
	}

	inline size_t getEntryCount( ) const
	{
		return mChildren.size( );
	}

	inline void setName( const Mocha::String& vName )
	{
		mName = vName;
	}

	inline const Mocha::String& getName( ) const
	{
		return mName;
	}

	inline void setID( const Mocha::String& vID )
	{
		mID = vID;
	}

	inline const Mocha::String& getID( ) const
	{
		return mID;
	}

	inline void setText( const Mocha::String& vText )
	{
		mText = vText;
	}

	inline const Mocha::String& getText( ) const
	{
		return mText;
	}

	inline void clear( )
	{
		mChildren.clear( );

		mName = "";
		mText = "";
		mID = "";
	}
};

}

#endif
