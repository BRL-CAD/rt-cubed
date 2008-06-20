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

#ifndef GUI_GUITHEME_H
#define GUI_GUITHEME_H

#include "Mocha/Object.h"
#include "Mocha/RefPointer.h"
#include "Mocha/Color.h"

#include "RBGui/Border.h"
#include "RBGui/Font.h"
#include "RBGui/Texture.h"

namespace RBGui
{

//--------------------------------
class Mocha::DataSection;
class GuiManager;

//--------------------------------
/// A theme describes the visual appearance of gui elements
class GUI_EXPORT Theme : public Mocha::Object
{
private:
	typedef std::map< Mocha::String, Mocha::RefPointer<Texture> > TextureMap;
	TextureMap mTextures;

	typedef std::map< Mocha::String, Mocha::RefPointer<Border> > BorderMap;
	BorderMap mBorders;

	typedef std::map<Mocha::String, Mocha::Color> ColorMap;
	ColorMap mColors;

	typedef std::map<Mocha::String, Mocha::RefPointer<Font> > FontMap;
	FontMap mFonts;

	typedef std::map<Mocha::String, float> FloatMap;
	FloatMap mFloats;

	Mocha::RefPointer<Font> mDefaultFont;

public:
	Theme( );

	virtual ~Theme( );

	/// Sets the default font to use. This font will be returned if a GUI element requests a font that does not exist
	void setDefaultFont( Font* vFont );

	/// Gets the default font that will be used. This font will be returned if a GUI element requests a font that does not exist
	Font* getDefaultFont( ) const;

	/// Sets a border
	/*! \param vName The string name of the border
		\param vBorder A pointer to the border */
	void setBorder( const Mocha::String& vName, Border* vBorder );

	/// Gets a border by name
	/*! \param The name of the border to get
		\return A pointer to the border, or 0 if the border is not found */
	Border* getBorder( const Mocha::String& vName ) const;

	/// Sets a color
	/*! \param vName The string name of the color
		\param vColor The color value */
	void setColor( const Mocha::String& vName, const Mocha::Color& vColor );

	/// Gets a color by name
	/*! \param vName The name of the color to get
		\param vDefault The color to return instead if the requested color cannot be found */
	Mocha::Color getColor( const Mocha::String& vName, const Mocha::Color& vDefault = Mocha::Color::White ) const;

	/// Sets a font
	/*! \param vName The name to use for the font
		\param vFont A pointer to the font */
	void setFont( const Mocha::String& vName, Font* vFont );

	/// Gets a font by name
	/*! \param vName The name of the font to get
		\return A pointer to the font, or a pointer to the default font if the requested font does not exist */
	Font* getFont( const Mocha::String& vName ) const;

	/// Sets a texture
	/*! \param vName The name to assign to the texture
		\param vTexture A pointer to the texture */
	void setTexture( const Mocha::String& vName, Texture* vTexture );

	/// Gets a texture by name
	/*! \param vName The name of the texture to get
		\return A pointer to the texture, or 0 if the texture does not exist */
	Texture* getTexture( const Mocha::String& vName ) const;

	/// Sets a float
	/*! \param vName The name to give to the font
		\param vValue The value to set */
	void setFloat( const Mocha::String& vName, float vValue );

	/// Gets a float by name
	/*! \param vName The name of the float value
		\param vDefault The default value to return if the requested value does not exist
		\return A requested value, or the default value if the requested value does not exist */
	float getFloat( const Mocha::String& vName, float vDefault ) const;

	/// Loads a theme from a data file
	/*! \param vSection the section of the data file to read from
		\param vManager The GuiManager to load the resources into */
	void open( const Mocha::DataSection& vSection );
};

}

#endif
