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

#include "Mocha/StringTools.h"
#include "RBGui/Exception.h"

#include "RBGui/Widgets/AttributeEditWidget.h"
#include "RBGui/Widgets/AttributeWidget.h"
#include "RBGui/Widgets/TextWidget.h"
#include "RBGui/Widgets/ScrollWidget.h"

#include "RBGui/Widgets/AttributeWidgets/FloatAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/Vector2AttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/Vector3AttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/ColorAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/BoolAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/TextAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/IntAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/ListAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/ButtonAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/SliderAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/SplineAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/FileAttributeWidget.h"

#define YPADDING 4
#define XPADDING 4

namespace RBGui
{

//--------------------------------
typedef std::map<Mocha::String, AttributeWidgetFactory> AttributeFactoryMap;
static AttributeFactoryMap attribFactories;

//--------------------------------
AttributeEditWidget::AttributeEditWidget( GuiManager* vManager )
: GroupWidget( vManager )
{
	// ...
}

//--------------------------------
AttributeEditWidget::~AttributeEditWidget( )
{
	// ...
}

//--------------------------------
void AttributeEditWidget::valueChanged( const Mocha::String& vName, const Mocha::Value& vNewValue )
{
	Mocha::ValueList v;
	v.push_back( vName );
	v.push_back( vNewValue );

	doCallback( v );
}

//--------------------------------
void AttributeEditWidget::onRectangleChanged( )
{
	// Do base adjusting

	GroupWidget::onRectangleChanged( );

	// Resize all widgets

	const Mocha::Rectangle& client = getClientRectangle( );
	float padding = mScrollBar->getRectangle( ).getWidth( ) + YPADDING;

	const WidgetList& children = getChildren( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{	
		Widget* w = (*it);
		if ( w != mScrollBar )
		{
			Mocha::Rectangle r = w->getRectangle( );
			r.right = client.getWidth( ) - padding;

			w->setRectangle( r );
		}
	}
}

//--------------------------------
void AttributeEditWidget::setAttributes( const AttributeMap& vAttributes )
{
	clearAttributes( );

	// Setup some constants...

	const float width = getClientRectangle( ).getWidth( ) - mScrollBar->getRectangle( ).getWidth( );
	const float textHeight = 16.0f;
	const float ypadding = YPADDING;
	const float xpadding = XPADDING;

	float ypos = ypadding;

	// For each entry, create a group of widgets

	AttributeMap::const_iterator it;
	for ( it = vAttributes.begin( ); it != vAttributes.end( ); it++ )
	{
		const AttributeEntryList& attribs = (*it).second;
		if ( attribs.empty( ) )
			continue;

		// Create a title for the group

		TextWidget* groupTitle = new TextWidget( getGuiManager( ) );
		groupTitle->setRectangle( xpadding, ypos, width - (xpadding*2), textHeight );
		groupTitle->setBorder( "AttributeGroupTitle" );
		groupTitle->setVerticalTextAlignment( TEXTALIGN_CENTER );
		groupTitle->setHorizontalTextAlignment( TEXTALIGN_CENTER );
		groupTitle->setText( (*it).first );

		attach( groupTitle );

		ypos += textHeight + ypadding;

		// Add a widget for each entry in the group

		AttributeEntryList::const_iterator cit;
		for ( cit = attribs.begin( ); cit != attribs.end( ); cit++ )
		{
			// Get the name of the attribute and its handler

			const AttributeEntry& entry = (*cit);		

			// Get the information to use to decide which widget to create

			Mocha::StringList tokens = Mocha::SplitString( entry.options, "|" );
			if ( tokens.size( ) == 0 )
				throw Exception( "Invalid attribute widget options string" );

			const Mocha::String& widget = tokens[0];

			// Try to select a widget to use for this attribute

			AttributeWidget* w = 0;

			AttributeFactoryMap::const_iterator it = attribFactories.find( widget );
			if ( it != attribFactories.end( ) )
				w = (*it).second( getGuiManager( ) );
			else
				throw Exception( "Invalid attribute widget type '" + widget + "'" );

			// Bind to attribute and flag as generated from code

			w->setName( entry.id );
			w->setGenerated( true );

			// Create title widget if needed

			if ( w->showTitle( ) )
			{
				TextWidget* title = new TextWidget( getGuiManager( ) );
				title->setRectangle( xpadding, ypos, width - (xpadding*2), textHeight );
				title->setText( entry.title );
				title->setName( entry.id );

				attach( title );

				ypos += textHeight;
			}

			// Attach the widget to the group

			attach( w );

			// Setup the widget

			w->setOptions( Mocha::StringList( tokens.begin( ) + 1, tokens.end( ) ) );
			w->setTitle( entry.title );

			try
			{
				if ( entry.value.getType( ) != Mocha::VALUE_NONE )
					w->setAttribute( entry.value );
			}
			catch ( Mocha::ValueErrorException& )
			{
				// Ignore value errors...
			}

			float height = w->getAttributeHeight( );
			w->setRectangle( xpadding, ypos, width - (xpadding*2), height );

			// Increase y offset

			ypos += height + ypadding;
		}
	}

	updateRegionSize( );
}

//--------------------------------
void AttributeEditWidget::setAttributes( Mocha::Object* vObject )
{
	// Get the actor attributes

	Mocha::ObjectValueEntryList attribs;
	vObject->getValueList( attribs );

	// Add them to the attribute window

	RBGui::AttributeMap entries;

	Mocha::ObjectValueEntryList::const_iterator it;
	for ( it = attribs.begin( ); it != attribs.end( ); it++ )
	{
		const Mocha::ObjectValueEntry& entry = (*it);
		
		Mocha::Value v;
		vObject->getValue( entry.name, v );

		entries["Attributes"].push_back( RBGui::AttributeEntry( entry.title, entry.name, entry.options, v ) );
	}

	// Set attributes

	setAttributes( entries );
}

//--------------------------------
void AttributeEditWidget::updateTitle( const Mocha::String& vAttributeID, const Mocha::String& vTitle )
{
	const WidgetList& children = getChildren( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{
		Widget* w = (*it);
		if ( w->getName( ) == vAttributeID )
		{
			TextWidget* title = dynamic_cast<TextWidget*>( w );
			if ( title && (title->getName( ) == vAttributeID) )
				title->setText( vTitle );
		}
	}	
}

//--------------------------------
void AttributeEditWidget::updateAttribute( const Mocha::String& vID, const Mocha::Value& vValue )
{
	const WidgetList& children = getChildren( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{
		Widget* w = (*it);
		if ( w->getName( ) == vID )
		{
			AttributeWidget* attrib = dynamic_cast<AttributeWidget*>( w );
			if ( attrib )
				attrib->setAttribute( vValue );
		}
	}
}

//--------------------------------
void AttributeEditWidget::getAttribute( const Mocha::String& vID, Mocha::Value& vValue ) const
{
	const WidgetList& children = getChildren( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{
		Widget* w = (*it);
		if ( w->getName( ) == vID )
		{
			AttributeWidget* attrib = dynamic_cast<AttributeWidget*>( w );
			if ( attrib )
			{
				attrib->getAttribute( vValue );
				break;
			}
		}
	}	
}

//--------------------------------
void AttributeEditWidget::updateOptions( const Mocha::String& vID, const Mocha::StringList& vParams )
{
	const WidgetList& children = getChildren( );

	WidgetList::const_iterator it;
	for ( it = children.begin( ); it != children.end( ); it++ )
	{
		Widget* w = (*it);
		if ( w->getName( ) == vID )
		{
			AttributeWidget* attrib = dynamic_cast<AttributeWidget*>( w );
			if ( attrib )
				attrib->setOptions( vParams );
		}
	}
}

//--------------------------------
void AttributeEditWidget::clearAttributes( )
{
	// This will erase the labels

	clearChildren( );

	// This will erase the generated attribute widgets

	WidgetList tmp = getChildren( );

	WidgetList::iterator it;
	for ( it = tmp.begin( ); it != tmp.end( ); it++ )
	{
		AttributeWidget* w = dynamic_cast<AttributeWidget*>( (*it).get( ) );
		if ( w )
			detach( w );
	}
}

//--------------------------------
Mocha::String AttributeEditWidget::getClassName( ) const
{
	return "AttributeEdit";
}

//--------------------------------
Widget* AttributeEditWidget::factory( GuiManager* vManager )
{
	return new AttributeEditWidget( vManager );
}

//--------------------------------
void AddAttributeWidgetFactory( const Mocha::String& vName, AttributeWidgetFactory vFactory )
{
	AttributeFactoryMap::iterator it = attribFactories.find( vName );
	if ( it != attribFactories.end( ) )
		throw Exception( "Attribute widget factory with name '" + vName + "' already defined" );

	attribFactories[vName] = vFactory;
}

//--------------------------------
void InitializeAttributeWidgets( )
{
	AddAttributeWidgetFactory( "float", FloatAttributeWidget::factory );
	AddAttributeWidgetFactory( "int", IntAttributeWidget::factory );
	AddAttributeWidgetFactory( "list", ListAttributeWidget::factory );
	AddAttributeWidgetFactory( "button", ButtonAttributeWidget::factory );
	AddAttributeWidgetFactory( "text", TextAttributeWidget::factory );
	AddAttributeWidgetFactory( "vector2", Vector2AttributeWidget::factory );
	AddAttributeWidgetFactory( "vector3", Vector3AttributeWidget::factory );
	AddAttributeWidgetFactory( "color", ColorAttributeWidget::factory );
	AddAttributeWidgetFactory( "bool", BoolAttributeWidget::factory );
	AddAttributeWidgetFactory( "slider", SliderAttributeWidget::factory );
	AddAttributeWidgetFactory( "spline", SplineAttributeWidget::factory );
	AddAttributeWidgetFactory( "file", FileAttributeWidget::factory );
}

}
