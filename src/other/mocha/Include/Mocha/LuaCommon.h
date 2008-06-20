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

#ifndef MOCHA_LUACOMMON_H
#define MOCHA_LUACOMMON_H

extern "C"
{
#include <lua.h>
#include <lstate.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "Mocha/Object.h"
#include "Mocha/Value.h"

namespace Mocha
{

//--------------------------------
inline void convertValues( lua_State* vState, int vCount, ValueList& vValues );
inline void pushValues( lua_State* vState, const ValueList& vValues );

//--------------------------------
static int callCmd( lua_State* vState )
{
	int count = lua_gettop( vState );

	// Get the object pointer

	Object* ptr = *(Object**)( lua_touserdata( vState, lua_upvalueindex( 2 ) ) );
	if ( ptr )
	{
		const char* str = lua_tostring( vState, lua_upvalueindex( 1 ) );

		// Convert lua values

		ValueList in;
		convertValues( vState, count, in );

		// Do invoke

		ValueList out;
		if ( ptr->invoke( str, in, out ) == false )
		{
			lua_pushstring( vState, (String( "Unable to invoke method: " ) + str).c_str( ) );
			lua_error( vState );
		}

		// Convert return values

		pushValues( vState, out );
		return (int)out.size( );
	}

	return 0;
}

//--------------------------------
static int indexCmd( lua_State* vState )
{
	// Push C closure to wrap function call

	lua_pushvalue( vState, 2 );
	lua_pushvalue( vState, lua_upvalueindex( 1 ) );

	lua_pushcclosure( vState, callCmd, 2 );

	// All done!

	return 1;
}

//--------------------------------
static int gcCmd( lua_State* vState )
{
	// Get pointer of object

	Object* ptr = *(Object**)( lua_touserdata( vState, lua_upvalueindex( 1 ) ) );

	// Decrement reference count

	ptr->decRef( );

	// All done!

	return 0;
}

//--------------------------------
inline void pushObject( lua_State* vState, Object* vObject )
{
	// Create user data

	Object** ptr = (Object**)lua_newuserdata( vState, sizeof( Object* ) );
	*ptr = vObject;

	// Create meta table

	lua_newtable( vState );

	// Create garbage collection closure

	lua_pushstring( vState, "__gc" );

	lua_pushvalue( vState, -3 );
	lua_pushcclosure( vState, gcCmd, 1 );

	lua_settable( vState, -3 );

	// Create index closure

	lua_pushstring( vState, "__index" );

	lua_pushvalue( vState, -3 );
	lua_pushcclosure( vState, indexCmd, 1 );
	
	lua_settable( vState, -3 );

	// Associate object with table

	lua_setmetatable( vState, -2 );

	// Increment object reference count

	vObject->incRef( );
}

//--------------------------------
inline void pushObjectWeak( lua_State* vState, Object* vObject )
{
	// Create user data

	Object** ptr = (Object**)lua_newuserdata( vState, sizeof( Object* ) );
	*ptr = vObject;

	// Create meta table

	lua_newtable( vState );

	// Create index closure

	lua_pushstring( vState, "__index" );

	lua_pushvalue( vState, -3 );
	lua_pushcclosure( vState, indexCmd, 1 );
	
	lua_settable( vState, -3 );

	// Associate object with table

	lua_setmetatable( vState, -2 );
}

//--------------------------------
inline void pushValue( lua_State* vState, const Value& vValue )
{
	switch ( vValue.getType( ) )
	{
	case VALUE_NUMBER:
		lua_pushnumber( vState, vValue.getNumber( ) );
		break;

	case VALUE_STRING:
		lua_pushstring( vState, vValue.getString( ).c_str( ) );
		break;

	case VALUE_OBJECTREF:
		pushObject( vState, vValue.getObject( ) );
		break;

	case VALUE_OBJECTWEAK:
		pushObjectWeak( vState, vValue.getObject( ) );
		break;

	case VALUE_BOOL:
		lua_pushboolean( vState, (int)vValue.getBool( ) );
		break;

	case VALUE_NONE:
		lua_pushnil( vState );
		break;
	}
}

//--------------------------------
inline void pushValues( lua_State* vState, const ValueList& vValues )
{
	ValueList::const_iterator it;
	for ( it = vValues.begin( ); it != vValues.end( ); it++ )
		pushValue( vState, (*it) );
}

//--------------------------------
inline void convertValue( lua_State* vState, int vIndex, Value& vValue )
{
	int type = lua_type( vState, vIndex );

	switch ( type )
	{
	case LUA_TNUMBER:
		vValue.setNumber( (float)lua_tonumber( vState, vIndex ) );
		break;

	case LUA_TSTRING:
		vValue.setString( lua_tostring( vState, vIndex ) );
		break;

	case LUA_TUSERDATA:
		vValue.setObject( *(Object**)lua_touserdata( vState, vIndex ) );
		break;

	case LUA_TBOOLEAN:
		vValue.setBool( (bool)lua_toboolean( vState, vIndex ) );
		break;

	case LUA_TNONE:
		vValue.setNone( );
		break;
	}	
}

//--------------------------------
inline void convertValues( lua_State* vState, int vCount, ValueList& vValues )
{
	int start = (lua_gettop( vState ) - vCount)+1;
	int end = lua_gettop( vState );

	int x;
	for ( x = start; x <= end; x++ )
	{
		int type = lua_type( vState, x );

		Value v;
		convertValue( vState, x, v );

		vValues.push_back( v );
	}
}

}

#endif
