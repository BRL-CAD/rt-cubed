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

#ifndef GUI_CORE_H
#define GUI_CORE_H

#include <map>

#include "Mocha/RefPointer.h"

#include "RBGui/ResourceManager.h"
#include "RBGui/TextureManager.h"
#include "RBGui/PlatformManager.h"
#include "RBGui/ThemeManager.h"
#include "RBGui/FontManager.h"
#include "RBGui/GuiManager.h"

namespace RBGui
{

/// Root class of the entire GUI system. Controls multiple independent GUIs and manager classes.
class GUI_EXPORT Core : public Mocha::Object
{
private:
	typedef std::map< Mocha::String, Mocha::RefPointer<GuiManager> > GuiMap;
	GuiMap mGuis;

	Mocha::RefPointer<ResourceManager> mResourceManager;

	Mocha::RefPointer<PlatformManager> mPlatformManager;

	Mocha::RefPointer<TextureManager> mTextureManager;

	Mocha::RefPointer<ThemeManager> mThemeManager;

	Mocha::RefPointer<FontManager> mFontManager;

	Mocha::RefPointer<Brush> mDefaultBrush;

public:
	/// Constructor
	/*! \param vTextureManager The texture manager to use (See TextureManager)
		\param vPlatformManager The platform manager to use (See PlatformManager)
		\param vDefaultBrush The optional default brush to use (See Brush) */
	Core( TextureManager* vTextureManager, PlatformManager* vPlatformManager, ResourceManager* vResourceManager, Brush* vDefaultBrush = 0 );

	/// Destructor
	virtual ~Core( );

	/// Updates all Guis
	/*! \param vDelta The time that has passed, in seconds */
	void tick( float vDelta );

	/// Creates a new Gui
	/*! \param vName The unique name to assign to this Gui
		\param vThe Brush interface to use for rendering this gui. Use 0 for the default Brush passed into the constructor */
	GuiManager* createGui( const Mocha::String& vName, Brush* vBrush = 0 );

	/// Gets a gui
	/*! \param vName The name of the Gui to get
		\return A pointer to the Gui */
	GuiManager* getGui( const Mocha::String& vName );

	/// Destroys a Gui
	/*! \param vName The name of the Gui to destroy */
	void destroyGui( const Mocha::String& vName );

	/// Tells all Guis to draw themselves
	void draw( );

	/// Gets the resource manager
	ResourceManager& getResourceManager( );

	/// Gets the platform manager
	PlatformManager& getPlatformManager( );

	/// Gets the texture manager
	TextureManager& getTextureManager( );

	/// Gets the theme manager
	ThemeManager& getThemeManager( );

	/// Gets the font manager
	FontManager& getFontManager( );

	/// Invalidates all Guis, forcing them to recalculate rectangles and redraw. Call this after changing/reloading a theme
	void invalidate( );

	/// Singleton accessor
	static Core& Get( );
};

}

#endif
