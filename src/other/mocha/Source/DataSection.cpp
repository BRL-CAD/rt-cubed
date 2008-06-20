/*
-----------------------------------------------------------------------------
This source file is part of Mocha
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
#include "Mocha/StringTools.h"
#include "Mocha/RefPointer.h"

namespace Mocha
{

//--------------------------------
DataComponent::DataComponent( )
{
	// ...
}

//--------------------------------
DataComponent::~DataComponent( )
{
	// ...
}

//--------------------------------
void DataComponent::setName( const String& vName )
{
	mName = vName;
}

//--------------------------------
const String& DataComponent::getName( ) const
{
	return mName;
}

//--------------------------------
void DataComponent::addParam( const String& vParam )
{
	mParams.push_back( vParam );
}

//--------------------------------
const String& DataComponent::getParam( size_t vIndex ) const
{
	return mParams[vIndex];
}

//--------------------------------
int DataComponent::getParamInt( size_t vIndex ) const
{
	return StringToInt( mParams[vIndex] );
}

//--------------------------------
float DataComponent::getParamFloat( size_t vIndex ) const
{
	return StringToFloat( mParams[vIndex] );
}

//--------------------------------
Color DataComponent::getParamColor( size_t vIndex ) const
{
	return StringToColor( mParams[vIndex] );
}

//--------------------------------
Rectangle DataComponent::getParamRectangle( size_t vIndex ) const
{
	return StringToRectangle( mParams[vIndex] );
}

//--------------------------------
Rectangle DataComponent::getParamRectangleLTRB( size_t vIndex ) const
{
	return StringToRectangleLTRB( mParams[vIndex] );
}

//--------------------------------
Vector2 DataComponent::getParamVector2( size_t vIndex ) const
{
	return StringToVector2( mParams[vIndex] );
}

//--------------------------------
Vector3 DataComponent::getParamVector3( size_t vIndex ) const
{
	return StringToVector3( mParams[vIndex] );
}

//--------------------------------
bool DataComponent::getParamBool( size_t vIndex ) const
{
	return StringToBool( mParams[vIndex] );
}

//--------------------------------
size_t DataComponent::getParamCount( ) const
{
	return mParams.size( );
}

//--------------------------------
DataSection::DataSection( )
{
	// ...
}

//--------------------------------
DataSection::~DataSection( )
{
	// ...
}

//--------------------------------
void DataSection::setType( const String& vType )
{
	mType = vType;
}

//--------------------------------
const String& DataSection::getType( ) const
{
	return mType;
}

//--------------------------------
void DataSection::addParam( const String& vParam )
{
	mParams.push_back( vParam );
}

//--------------------------------
const String& DataSection::getParam( size_t vIndex ) const
{
	return mParams[vIndex];
}

//--------------------------------
size_t DataSection::getParamCount( ) const
{
	return mParams.size( );
}

//--------------------------------
void DataSection::addComponent( const DataComponent& vComponent )
{
	mComponents.push_back( vComponent );
}

//--------------------------------
const DataComponent& DataSection::getComponent( size_t vIndex ) const
{
	return mComponents[vIndex];
}

//--------------------------------
void DataSection::addComponent( const String& vName, float vValue )
{
	DataComponent comp;
	comp.setName( vName );
	comp.addParam( FloatToString( vValue ) );

	addComponent( comp );
}

//--------------------------------
void DataSection::addComponent( const String& vName, const Vector2& vValue )
{
	DataComponent comp;
	comp.setName( vName );
	comp.addParam( Vector2ToString( vValue ) );

	addComponent( comp );
}

//--------------------------------
void DataSection::addComponent( const String& vName, const Vector3& vValue )
{
	DataComponent comp;
	comp.setName( vName );
	comp.addParam( Vector3ToString( vValue ) );

	addComponent( comp );
}

//--------------------------------
void DataSection::addComponent( const String& vName, const Color& vValue )
{
	DataComponent comp;
	comp.setName( vName );
	comp.addParam( ColorToString( vValue ) );

	addComponent( comp );
}

//--------------------------------
void DataSection::addComponent( const String& vName, const Rectangle& vValue )
{
	DataComponent comp;
	comp.setName( vName );
	comp.addParam( RectangleToString( vValue ) );

	addComponent( comp );
}

//--------------------------------
void DataSection::addComponent( const String& vName, const String& vValue )
{
	DataComponent comp;
	comp.setName( vName );
	comp.addParam( vValue );

	addComponent( comp );
}

//--------------------------------
void DataSection::addComponent( const String& vName, const char* vValue )
{
	addComponent( vName, String( vValue ) );
}

//--------------------------------
void DataSection::addComponent( const String& vName, bool vValue )
{
	DataComponent comp;
	comp.setName( vName );
	comp.addParam( BoolToString( vValue ) );

	addComponent( comp );	
}

//--------------------------------
const DataComponent* DataSection::findComponent( const String& vName ) const
{
	size_t x;
	for ( x = 0; x < mComponents.size( ); x++ )
	{
		if ( mComponents[x].getName( ) == vName )
			return &mComponents[x];
	}

	return 0;
}

//--------------------------------
size_t DataSection::getComponentCount( ) const
{
	return mComponents.size( );
}

//--------------------------------
void DataSection::addSection( const DataSection& vSection )
{
	mChildren.push_back( vSection );
}

//--------------------------------
const DataSection& DataSection::getSection( size_t vIndex ) const
{
	return mChildren[vIndex];
}

//--------------------------------
size_t DataSection::getSectionCount( ) const
{
	return (int)mChildren.size( );
}

//--------------------------------
void DataSection::clear( )
{
	mType = "";
	mChildren.clear( );
	mParams.clear( );
}

//--------------------------------
String DataSection::readLine( const Stream& vStream )
{
	String tmp;

	while ( vStream.getEndOfStream( ) != true )
	{
		// Read the next character

		char c = vStream.read<Mocha::int8>( );
		if ( c == '\n' )
			break;

		// Skip the evil '\r' character

		if ( c != '\r' )
			tmp += c;
	}

	return tmp;
}

//--------------------------------
void DataSection::writeLine( Stream& vStream, const String& vText, int vDepth ) const
{
	// Write indentation

	int x;
	for ( x = 0; x < vDepth; x++ )
		vStream.write<char>( '\t' );

	// Write text

	vStream.writeData( vText.c_str( ), vText.size( ) );

	// Write new-line

	vStream.write<char>( '\n' );
}

//--------------------------------
void DataSection::readSection( const Stream& vStream, int vDepth )
{
	while ( vStream.getEndOfStream( ) != true )
	{
		// Tokenize line

		StringList tokens = TokenizeString( readLine( vStream ) );
		if ( tokens.size( ) == 0 )
			continue;

		// See if this is the end of the section

		const String& name = LowerString( tokens[0] );
		if ( name == "end" )
		{
			if ( vDepth <= 0 )
				throw Exception( "Unexpected 'end' tag found" );

			return;
		}

		// See if this is a section

		if ( name == "begin" )
		{
			// Parse section

			DataSection section;

			if ( tokens.size( ) > 1 )
			{
				// Set type of section

				section.setType( tokens[1] );

				// Get section parameters

				if ( tokens.size( ) > 2 )
				{
					StringList::iterator it;
					for ( it = tokens.begin( ) + 2; it != tokens.end( ); it++ )
						section.addParam( (*it) );
				}
			}

			section.readSection( vStream, vDepth + 1 );

			// Add to current section

			addSection( section );
		}
		else
		{
			// Parse component tokens

			DataComponent component;
			component.setName( name );

			if ( tokens.size( ) > 1 )
			{
				StringList::iterator it;
				for ( it = tokens.begin( ) + 1; it != tokens.end( ); it++ )
					component.addParam( (*it) );
			}

			// Add it to the section

			addComponent( component );
		}
	}

	if ( vDepth != 0 )
		throw Exception( "Unexpected end of file" );
}

//--------------------------------
void DataSection::writeSection( Stream& vStream, int vDepth ) const
{
	size_t x;

	// Write out section header

	String header = "begin " + getType( );

	for ( x = 0; x < getParamCount( ); x++ )
		header += " " + getParam( x );

	writeLine( vStream, header, vDepth );

	// Write section components

	for ( x = 0; x < getComponentCount( ); x++ )
	{
		const DataComponent& comp = getComponent( x );
		String compLine = comp.getName( );

		size_t y;
		for ( y = 0; y < comp.getParamCount( ); y++ )
			compLine += String( " " ) + "\"" + comp.getParam( y ) + "\"";

		writeLine( vStream, compLine, vDepth+1 );
	}

	// Write sub-sections

	for ( x = 0; x < getSectionCount( ); x++ )
	{
		// Write section

		getSection( x ).writeSection( vStream, vDepth+1 );
	}

	// End section

	writeLine( vStream, "end", vDepth );
}

//--------------------------------
void DataSection::read( const Stream& vStream )
{
	readSection( vStream, 0 );
}

//--------------------------------
void DataSection::write( Stream& vStream ) const
{
	writeSection( vStream, 0 );
}

}
