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

#include "Mocha/ScriptManager.h"
#include "Mocha/Stream.h"
#include "Mocha/Object.h"
#include "Mocha/LuaCommon.h"

extern "C"
{
#include "lua.h"
#include "lstate.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace Mocha
{

//--------------------------------
ScriptManager::ScriptManager( )
: mCurrentTask( 0 ), mTaskCounter( 0 ), mUserData( 0 )
{
	// Setup the lua state

	mState = lua_open( );
	mState->userData = this;

	// Create the task table

	lua_pushstring( mState, TASKTABLE_NAME );
	lua_newtable( mState );

	lua_settable( mState, LUA_GLOBALSINDEX );

	// Add built in functions

	lua_register( mState, "spawn", spawnCmd );
	lua_register( mState, "yield", yieldCmd );
	lua_register( mState, "sleep", sleepCmd );
	lua_register( mState, "exit", exitCmd );
	lua_register( mState, "time", timeCmd );
	lua_register( mState, "include", includeCmd );

	//lua_register( mState, "new", newCmd );

	luaopen_base( mState );
}

//--------------------------------
ScriptManager::~ScriptManager( )
{
	// Destroy lua state

	if ( mState )
		lua_close( mState );
}

//--------------------------------
void ScriptManager::setUserData( void* vData )
{
	mUserData = vData;
}

//--------------------------------
void* ScriptManager::getUserData( ) const
{
	return mUserData;
}

//--------------------------------
void ScriptManager::call( const String& vName, const ValueList& vInput, ValueList& vOutput )
{
	// Get command from globals

	lua_pushstring( mState, vName.c_str( ) );
	lua_gettable( mState, LUA_GLOBALSINDEX );

	if ( lua_isnil( mState, -1 ) == true )
	{
		lua_pop( mState, 1 );
		throw ScriptErrorException( "No such command: " + vName );
	}

	// Push parameters

	pushValues( mState, vInput );
	int top = lua_gettop( mState ) - 2;

	// Do call

	lua_call( mState, (int)vInput.size( ), LUA_MULTRET );

	// Convert return values

	int pcount = lua_gettop( mState ) - top;
	convertValues( mState, pcount, vOutput );

	// Pop values from stack

	lua_pop( mState, pcount );
}

//--------------------------------
void ScriptManager::tick( float vDelta )
{
	// Update all tasks

	TaskList::iterator it = mTasks.begin( );
	while ( it != mTasks.end( ) )
	{
		ScriptTask* task = (*it);
		mCurrentTask = task;

		if ( task->getTerminated( ) || task->tick( vDelta ) )
		{
			// Finish up task

			task->finish( mState );

			// Remove from task list

			it = mTasks.erase( it );
		}
		else
			it++;
	}

	// Reset current task pointer

	mCurrentTask = 0;
}

//--------------------------------
void ScriptManager::runScript( const Stream& vStream )
{
	// Read stream into string

	int size = vStream.getSize( );

	Mocha::String str;
	str.resize( size );

	if ( vStream.readData( (void*)str.c_str( ), size ) != size )
		throw ScriptErrorException( "Error while reading stream" );

	// Run script from string

	int res = luaL_dostring( mState, str.c_str( ) );
	if ( res != 0 )
	{
		String msg = lua_tostring( mState, -1 );
		lua_pop( mState, 1 );

		throw ScriptErrorException( msg );
	}	
}

//--------------------------------
void ScriptManager::runScript( const String& vPath )
{
	// Run script file

	int res = luaL_dofile( mState, vPath.c_str( ) );
	if ( res != 0 )
	{
		String msg = lua_tostring( mState, -1 );
		lua_pop( mState, 1 );

		throw ScriptErrorException( msg );
	}
}

//--------------------------------
int ScriptManager::cmdWrapper( lua_State* vState )
{
	// Get pointer to command object

	ScriptCommand cmd = (ScriptCommand)lua_touserdata( vState, lua_upvalueindex( 1 ) );
	
	// Convert lua values

	try
	{
		ValueList in;
		convertValues( vState, lua_gettop( vState ), in );

		ValueList out;
		ReturnMode mode = cmd( *(static_cast<ScriptManager*>( vState->userData )), in, out );

		// Push output values

		pushValues( vState, out );

		if ( mode == RETURN_NORMAL )
			return (int)out.size( );
		else
			return lua_yield( vState, (int)out.size( ) );
	}
	catch ( Mocha::Exception& e )
	{
		lua_pushstring( vState, e.getMessage( ).c_str( ) );
		lua_error( vState );
	}

	return 0;
}

//--------------------------------
int ScriptManager::includeCmd( lua_State* vState )
{
	// Make sure we have a string as the first argument

	if ( (lua_gettop( vState ) < 1) || (lua_isstring( vState, 1 ) == false) )
	{
		lua_pushstring( vState, "First argument must be a string" );
		lua_error( vState );
	}

	// Run script file

	int res = luaL_dofile( vState, lua_tostring( vState, -1 ) );
	if ( res != 0 )
	{
		String msg = lua_tostring( vState, -1 );
		lua_pop( vState, 1 );

		lua_pushstring( vState, msg.c_str( ) );
		lua_error( vState );
	}

	return 0;
}

//--------------------------------
/*int ScriptManager::newCmd( lua_State* vState )
{
	// Make sure arguments are correct

	if ( (lua_gettop( vState ) == 0) || (lua_isstring( vState, 1 ) == false) )
	{
		lua_pushstring( vState, "Invalid arguments to 'new' command" );
		lua_error( vState );
	}

	// Create object and push to stack

	Object* obj = Kernel::Get( ).createObject( lua_tostring( vState, 1 ) );
	if ( obj != 0 )
		pushObject( vState, obj );
	else
		lua_pushnil( vState );
	
	return 1;

	return 0;
}*/

//--------------------------------
void ScriptManager::addCommand( const String& vName, ScriptCommand vCommand )
{
	// Push C closure for command into globals

	lua_pushstring( mState, vName.c_str( ) );

	lua_pushlightuserdata( mState, (void*)vCommand );
	lua_pushcclosure( mState, cmdWrapper, 1 );

	lua_settable( mState, LUA_GLOBALSINDEX );
}

//--------------------------------
void ScriptManager::setGlobal( const String& vName, const Value& vValue )
{
	lua_pushstring( mState, vName.c_str( ) );
	pushValue( mState, vValue );

	lua_settable( mState, LUA_GLOBALSINDEX );
}

//--------------------------------
void ScriptManager::getGlobal( const String& vName, Value& vValue )
{
	lua_pushstring( mState, vName.c_str( ) );
	lua_gettable( mState, LUA_GLOBALSINDEX );

	convertValue( mState, -1, vValue );
	lua_pop( mState, 1 );
}

//--------------------------------
ScriptTask* ScriptManager::spawnTask( const String& vCommand, const ValueList& vValues )
{
	// Try to get the function from the globals

	lua_pushstring( mState, vCommand.c_str( ) );
	lua_gettable( mState, LUA_GLOBALSINDEX );

	if ( lua_isnil( mState, -1 ) == true )
	{
		lua_pop( mState, 1 );
		throw ScriptErrorException( "No such command: " + vCommand );
	}

	// Push the values onto the stack

	pushValues( mState, vValues );

	// Create task and prepare it

	ScriptTask* t = new ScriptTask( mTaskCounter++ );
	t->prepare( mState, lua_gettop( mState ) - vValues.size( ), vValues.size( ) );

	// Add to task list

	addTask( t );

	// Pop function off stack

	lua_pop( mState, 1 );

	// Return task

	return t;
}

//--------------------------------
void ScriptManager::addTask( ScriptTask* vTask )
{
	// Add to task list

	mTasks.push_back( vTask );
}

//--------------------------------
ScriptTask* ScriptManager::getCurrentTask( ) const
{
	return mCurrentTask;
}

//--------------------------------
size_t ScriptManager::getTaskCount( ) const
{
	return mTasks.size( );
}

//--------------------------------
int ScriptManager::spawnCmd( lua_State* vState )
{
	// Make sure we have a function as the first argument

	if ( (lua_gettop( vState ) < 1) || (lua_isfunction( vState, 1 ) == false) || (lua_iscfunction( vState, 1 ) == 1) )
	{
		lua_pushstring( vState, "First argument must be a Lua function" );
		lua_error( vState );
	}

	// Get pointer to self

	ScriptManager* self = reinterpret_cast<ScriptManager*>( vState->userData );

	// Create task and prepare it

	ScriptTask* t = new ScriptTask( self->mTaskCounter++ );
	t->prepare( vState, 1, lua_gettop( vState ) - 1 );

	// Add to task list

	self->addTask( t );

	// Push task ID

	lua_pushnumber( vState, t->getID( ) );

	// All done!

	return 1;
}

//--------------------------------
int ScriptManager::yieldCmd( lua_State* vState )
{
	// Get pointer to self

	ScriptManager* self = reinterpret_cast<ScriptManager*>( vState->userData );

	// Make sure we're in a task

	ScriptTask* task = self->getCurrentTask( );
	if ( task == 0 )
		return 0;

	// Tell co-routine to yield

	return lua_yield( vState, 0 );
}

//--------------------------------
int ScriptManager::timeCmd( lua_State* vState )
{
	// Get pointer to self

	ScriptManager* self = reinterpret_cast<ScriptManager*>( vState->userData );

	// Make sure we're in a task

	ScriptTask* task = self->getCurrentTask( );
	if ( task )
		lua_pushnumber( vState, task->getTime( ) );
	else
		lua_pushnumber( vState, 0.0f );

	return 1;
}

//--------------------------------
int ScriptManager::sleepCmd( lua_State* vState )
{
	// Get the delay of the sleep

	if ( (lua_gettop( vState ) < 1) || (lua_isnumber( vState, 1 ) == false) )
	{
		lua_pushstring( vState, "Argument must be a number" );
		lua_error( vState );
	}

	float delay = (float)lua_tonumber( vState, 1 );
	
	// Get pointer to self

	ScriptManager* self = reinterpret_cast<ScriptManager*>( vState->userData );

	// Make sure we're in a task
	
	ScriptTask* task = self->getCurrentTask( );
	if ( task == 0 )
		return 0;

	// Block the task for the delay amount

	task->block( delay );

	// Yield execution

	return lua_yield( vState, 0 );
}

//--------------------------------
int ScriptManager::exitCmd( lua_State* vState )
{
	// Get pointer to self

	ScriptManager* self = reinterpret_cast<ScriptManager*>( vState->userData );

	// Terminate current task

	ScriptTask* t = self->getCurrentTask( );
	if ( t != 0 )
	{
		t->terminate( );

		// Yield execution

		return lua_yield( vState, 0 );
	}

	return 0;
}

}
