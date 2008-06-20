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

#ifndef GUI_FONTMANAGER_H
#define GUI_FONTMANAGER_H

#include "RBGui/Font.h"
#include "RBGui/TextureManager.h"
#include "RBGui/PlatformManager.h"

namespace RBGui
{

/// Manages all of the fonts
class FontManager : public Mocha::Object
{
private:
	class FontEntry
	{
	public:
		inline FontEntry( const Mocha::String& vName, size_t vSize, Font* vFont )
		{
			name = vName;
			font = vFont;
			size = vSize;
		}

		inline FontEntry( )
			: size( 0 )
		{
			// ...
		}

		Mocha::RefPointer<Font> font;

		Mocha::String name;

		size_t size;
	};

	typedef std::vector< FontEntry > FontList;
	mutable FontList mFonts;

	Font* loadFont( const Mocha::String& vName, size_t vSize );

public:
	FontManager( );

	virtual ~FontManager( );

	/// Gets a font by name. The font will be loaded if it doesn't exist
	/*! \param vName The name of the font resource to load
		\param vSize The size to render the font glyphs at
		\return A pointer to the Font object */
	Font* getFont( const Mocha::String& vName, size_t vSize );

	/// Removes all fonts that are not being referenced by anything
	void flush( );
};

}

#endif
