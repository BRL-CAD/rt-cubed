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

#ifndef MOCHA_OBJECT_H
#define MOCHA_OBJECT_H

#include <vector>
#include <string>

#include "Mocha/RefCounted.h"
#include "Mocha/Exception.h"
#include "Mocha/Platform.h"
#include "Mocha/Value.h"

namespace Mocha
{

//--------------------------------
/// Stores data for a value entry on an object
class ObjectValueEntry
{
public:
	inline ObjectValueEntry( )
		: persistant( false )
	{
		// ...
	}

	inline ObjectValueEntry( const String& vName, const String& vOptions, const String& vTitle, bool vPersistant = true )
		: name( vName ), options( vOptions ), title( vTitle ), persistant( vPersistant )
	{
		// ...
	}

	String name;

	String options;

	String title;

	bool persistant;
};

typedef std::vector<ObjectValueEntry> ObjectValueEntryList;

//--------------------------------
enum CommandResult
{
	CMDRESULT_SUCCESS = 0,
	CMDRESULT_BADARGUMENTS,
	CMDRESULT_INVALIDCOMMAND
};

//--------------------------------
/// Base class for reference counted, scriptable objects
class MOCHA_EXPORT Object : public RefCounted
{
public:
	Object( );

	virtual ~Object( );

	/// Calls a command on the object
	/*! \param vName The name of the command to call
		\param vIn The input parameter value list
		\param vOut The output parameter value list */
	virtual CommandResult invoke( const String& vName, const ValueList& vIn, ValueList& vOut );

	/// Gets a list of values that can be edited on the object with 'set/get' commands
	/*! \param vOut The list of values to be filled in. See ObjectValueEntry */
	virtual void getValueList( ObjectValueEntryList& vOut ) const;

	/// Gets the name of the class this object belongs to
	virtual String getClassName( ) const;

	/// Gets a string representation of the object
	virtual String getAsString( ) const;

	/// Sets a value on the object
	/*! \param vName The name of the value to set
		\param vValue The value to use */
	CommandResult setValue( const String& vName, const Value& vValue );

	/// Gets a value on the object
	/*! \param vName The name of the value to get
		\param vValue The value object to be filled in */
	CommandResult getValue( const String& vName, Value& vValue ) const;
};

//--------------------------------
typedef Object* (*ObjectFactory)( ); 

}

#endif
