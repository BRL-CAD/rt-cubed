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

#include "RBGui/Brush.h"
#include "RBGui/Core.h"
#include "RBGui/Exception.h"

#include "RBGui/Widgets/ImageWidget.h"

namespace RBGui
{

//--------------------------------
ImageWidget::ImageWidget( GuiManager* vManager )
: Widget( vManager )
{
	setColor( Mocha::Color::White );
}

//--------------------------------
ImageWidget::~ImageWidget( )
{
	// ...
}

//--------------------------------
Mocha::String ImageWidget::getClassName( ) const
{
	return "Image";
}

//--------------------------------
void ImageWidget::onDraw( Brush& vBrush ) const
{
	vBrush.setColor( getRenderColor( ) );

	vBrush.setFilterMode( BRUSHFILTER_LINEAR );
	vBrush.setBlendMode( BRUSHBLEND_ALPHA );
	vBrush.setTexture( mImage );

	vBrush.drawRectangle( getClientRectangle( ) );
}

//--------------------------------
void ImageWidget::getValueList( Mocha::ObjectValueEntryList& vOut ) const
{
	Widget::getValueList( vOut );

	vOut.push_back( Mocha::ObjectValueEntry( "Image", "text", "Image" ) );
}

//--------------------------------
Mocha::CommandResult ImageWidget::invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut )
{
	if ( vName == "setImage" )
	{
		if ( vIn.size( ) != 1 )
			return Mocha::CMDRESULT_BADARGUMENTS;

		if ( vIn[0].isObject( ) )
			setImage( dynamic_cast<Texture*>( vIn[0].getObject( ) ) );
		else
			setImage( vIn[0].getAsString( ) );

		return Mocha::CMDRESULT_SUCCESS;
	}
	else if ( vName == "getImage" )
	{
		vOut.push_back( getImage( ) );
		return Mocha::CMDRESULT_SUCCESS;
	}

	return Widget::invoke( vName, vIn, vOut );
}

//--------------------------------
void ImageWidget::setImage( const Mocha::String& vTexture )
{
	try
	{
		Mocha::RefPointer<Texture> tex = Core::Get( ).getTextureManager( ).getTexture( vTexture );
		setImage( tex );
	}
	catch ( Exception& )
	{
		// ...
	}
}

//--------------------------------
void ImageWidget::setImage( Texture* vTexture )
{
	mImage = vTexture;
	flagDirty( );
}

//--------------------------------
Texture* ImageWidget::getImage( ) const
{
	return mImage;
}

//--------------------------------
Widget* ImageWidget::factory( GuiManager* vManager )
{
	return new ImageWidget( vManager );
}

}
