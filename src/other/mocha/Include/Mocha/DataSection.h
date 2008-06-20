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

#ifndef MOCHA_DATAFILEPARSER_H
#define MOCHA_DATAFILEPARSER_H

#include <vector>

#include "Mocha/Rectangle.h"
#include "Mocha/Vector3.h"
#include "Mocha/Vector2.h"
#include "Mocha/Color.h"

namespace Mocha
{

//--------------------------------
class Stream;

//--------------------------------
/// A single component of a data file, with a name and optional parameters
class MOCHA_EXPORT DataComponent
{
private:
	String mName;

	StringList mParams;

public:
	/// Constructor
	DataComponent( );

	/// Destructor
	~DataComponent( );

	/// Sets the name of the data component
	/*! \param vName The name of the data component to use */
	void setName( const String& vName );

	/// Gets the name of the data component
	/*! \return The name of the data component to use */
	const String& getName( ) const;

	/// Adds a parameter to the data component
	/*! \param vParam The string parameter to add */
	void addParam( const String& vParam );

	/// Gets a parameter from the data component
	/*	\param vIndex The index of the parameter to get
		\return A reference to the parameter */
	const String& getParam( size_t vIndex ) const;

	/// Gets a parameter as an integer value
	/*! \param vIndex The index of the parameter to get
		\return The integer value of the parameter */
	int getParamInt( size_t vIndex ) const;

	/// Gets a parameter as a float value
	/*! \param vIndex The index of the parameter to get
		\return The float value of the parameter */
	float getParamFloat( size_t vIndex ) const;

	/// Gets a parameter as a color value
	/*! \param vIndex The index of the parameter to get
		\return The color value of the parameter */
	Color getParamColor( size_t vIndex ) const;

	/// Gets a parameter as a vector2 value
	/*! \param vIndex The index of the parameter to get
		\return The vector2 value of the parameter */
	Vector2 getParamVector2( size_t vIndex ) const;

	/// Gets a parameter as a vector3 value
	/*! \param vIndex The index of the parameter to get
		\return The vector3 value of the parameter */
	Vector3 getParamVector3( size_t vIndex ) const;

	/// Gets a parameter as a rectangle, using x y width height semantics
	/*! \param vIndex The index of the parameter to get
		\return The rectangle value of the parameter */
	Rectangle getParamRectangle( size_t vIndex ) const;

	/// Gets a parameter as a rectangle, using top left right bottom semantics
	/*! \param vIndex The index of the parameter to get
		\return The rectangle value of the parameter */
	Rectangle getParamRectangleLTRB( size_t vIndex ) const;

	/// Gets a parameter as a boolean value
	/*! \param vIndex The index of the parameter to get
		\return The parameter as a boolean value */
	bool getParamBool( size_t vIndex ) const;

	/// Gets the number of parameters on the component
	/*! \return The number of parameters */
	size_t getParamCount( ) const;
};

//--------------------------------
class MOCHA_EXPORT DataSection
{
private:
	typedef std::vector<DataSection> DataSectionList;
	DataSectionList mChildren;

	typedef std::vector<DataComponent> DataComponentList;
	DataComponentList mComponents;

	StringList mParams;

	String mType;

	String readLine( const Stream& vStream );

	void writeLine( Stream& vStream, const String& vText, int vDepth ) const;

	void readSection( const Stream& vStream, int vDepth );

	void writeSection( Stream& vStream, int vDepth ) const;

public:
	/// Constructor
	DataSection( );

	/// Destructor
	~DataSection( );

	/// Sets the type name of the section
	/*! \param vType The type name of the section */
	void setType( const String& vType );

	/// Gets the type name of the section
	/*! \return The type name of the section */
	const String& getType( ) const;

	/// Adds a section parameter
	/*! \param vParam The string parameter */
	void addParam( const String& vParam );

	/// Gets a section parameter
	/*! \param vIndex The index of the parameter
		\return The string parameter */
	const String& getParam( size_t vIndex ) const;

	/// Gets the number of section parameters
	/*! \return The number of section parameters */
	size_t getParamCount( ) const;

	/// Adds a data component to the section
	/*! \param Reference to the data component to add */
	void addComponent( const DataComponent& vComponent );

	/// Gets a data component of the section
	/*! \param vIndex The index of the data component
		\return A reference to the data component */
	const DataComponent& getComponent( size_t vIndex ) const;

	/// Adds a float value component
	void addComponent( const String& vName, float vValue );

	/// Adds a vector2 value component
	void addComponent( const String& vName, const Vector2& vValue );

	/// Adds a vector3 value component
	void addComponent( const String& vName, const Vector3& vValue );

	/// Add a color value component
	void addComponent( const String& vName, const Color& vValue );

	/// Adds a rectangle value component
	void addComponent( const String& vName, const Rectangle& vValue );

	/// Adds a string value component
	void addComponent( const String& vName, const String& vValue );

	/// Adds a string value component
	void addComponent( const String& vName, const char* vValue );

	/// Adds a boolean value component
	void addComponent( const String& vName, bool vValue );

	/// Finds a component by name
	/*! \param vName The name of the component to find
		\return A pointer to the component, or 0 if a component by that name does not exist */
	const DataComponent* findComponent( const String& vName ) const;

	/// Gets the number of data components in the section
	/*! \return The number of data components in the section */
	size_t getComponentCount( ) const;

	/// Adds a nested section as a child
	/*! \param vSection The section to add as a child */
	void addSection( const DataSection& vSection );

	/// Gets a nested sections
	/*! \param vIndex The index of the nested section to get
		\return A reference to the nested section */
	const DataSection& getSection( size_t vIndex ) const;

	/// Gets the number of nested sections
	/*! \return The number of nested sections */
	size_t getSectionCount( ) const;

	/// Removes all data from the section
	void clear( );

	/// Reads the data section from the given stream
	/*! \param vStream The stream to read the data from */
	void read( const Stream& vStream );

	/// Writes the data section to the given stream
	/*! \param vStream The stream to write to */
	void write( Stream& vStream ) const;
};

}

#endif
