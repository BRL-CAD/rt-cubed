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

#ifndef GUI_ATTRIBUTEEDITWIDGET_H
#define GUI_ATTRIBUTEEDITWIDGET_H

#include "RBGui/Widgets/GroupWidget.h"

namespace RBGui
{

//--------------------------------
class AttributeWidget;
typedef AttributeWidget* (*AttributeWidgetFactory)( GuiManager* vManager );

//--------------------------------
class AttributeEntry
{
public:
	inline AttributeEntry( const Mocha::String& vTitle, const Mocha::String& vID, const Mocha::String& vOptions, const Mocha::Value& vValue = Mocha::Value( ) )
		: title( vTitle ), id( vID ), options( vOptions ), value( vValue )
	{
		// ...
	}

	inline AttributeEntry( )
	{
		// ...
	}

	Mocha::String title;

	Mocha::String options;

	Mocha::String id;

	Mocha::Value value;
};

//--------------------------------
typedef std::vector<AttributeEntry> AttributeEntryList;
typedef std::map<Mocha::String, AttributeEntryList> AttributeMap;

//--------------------------------
/// A widget that displays a list of attributes that can be edited
class GUI_EXPORT AttributeEditWidget : public GroupWidget
{

friend class AttributeWidget;

protected:
	virtual void onRectangleChanged( );

	void valueChanged( const Mocha::String& vName, const Mocha::Value& vNewValue );

public:
	AttributeEditWidget( GuiManager* vManager );

	virtual ~AttributeEditWidget( );

	virtual Mocha::String getClassName( ) const;

	void clearAttributes( );

	void setAttributes( const AttributeMap& vAttributes );

	void setAttributes( Mocha::Object* vObject );

	void updateTitle( const Mocha::String& vAttributeID, const Mocha::String& vTitle );

	void updateAttribute( const Mocha::String& vID, const Mocha::Value& vValue );

	void getAttribute( const Mocha::String& vID, Mocha::Value& vValue ) const;

	void updateOptions( const Mocha::String& vID, const Mocha::StringList& vParams );

	static Widget* factory( GuiManager* vManager );
};

//--------------------------------
GUI_EXPORT extern void AddAttributeWidgetFactory( const Mocha::String& vName, AttributeWidgetFactory vFactory );

//--------------------------------
GUI_EXPORT extern void InitializeAttributeWidgets( );

}

#endif
