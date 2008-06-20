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

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lstate.h"
#include "lualib.h"
}

#include "Mocha/ScriptTask.h"
#include "Mocha/LuaCommon.h"

namespace Mocha
{

//--------------------------------
ScriptTask::ScriptTask( size_t vID )
: mBlocked( false ), mState( 0 ), mParams( 0 ), mID( vID ), mTerminate( false ), mBlockDelay( 0.0f ), mBlockTimer( 0.0f ), mTime( 0.0f )
{
	// ...
}

//--------------------------------
ScriptTask::~ScriptTask( )
{
	// ...
}

//--------------------------------
void ScriptTask::setObject( Mocha::Object* vObject )
{
	mObject = vObject;
}

//--------------------------------
Mocha::Object* ScriptTask::getObject( ) const
{
	return mObject;
}

//--------------------------------
float ScriptTask::getTime( ) const
{
	return mTime;
}

//--------------------------------
size_t ScriptTask::getID( ) const
{
	return mID;
}

//--------------------------------
lua_State* ScriptTask::getState( ) const
{
	return mState;
}

//--------------------------------
void ScriptTask::terminate( )
{
	mTerminate = true;
}

//--------------------------------
bool ScriptTask::getTerminated( ) const
{
	return mTerminate;
}

//--------------------------------
void ScriptTask::addResumeValue( const Mocha::Value& vValue )
{
	pushValue( mState, vValue );
	mParams++;
}

//--------------------------------
void ScriptTask::prepare( lua_State* vState, size_t vFunctionIndex, size_t vParams )
{
	// Push task table onto stack

	lua_pushstring( vState, TASKTABLE_NAME );
	lua_gettable( vState, LUA_GLOBALSINDEX );

	// Push ID onto stack as key

	lua_pushnumber( vState, mID );

	// Create new thread as value

	mState = lua_newthread( vState );
	mState->userData = vState->userData;

	// Store state into table

	lua_rawset( vState, -3 );

	// Pop table from stack

	lua_pop( vState, 1 );

	// Copy function to top of stack

	lua_pushvalue( vState, (int)vFunctionIndex );

	// Move function value from main state to local state

	lua_xmove( vState, mState, 1 );

	// Get parameter count

	mParams = vParams;

	// Move params to new state stack

	if ( mParams > 0 )
		lua_xmove( vState, mState, (int)mParams );
}

//--------------------------------
void ScriptTask::finish( lua_State* vState )
{
	// Push task table onto stack

	lua_pushstring( vState, TASKTABLE_NAME );
	lua_gettable( vState, LUA_GLOBALSINDEX );

	// Push task ID as index, and nil as value to remove from task table

	lua_pushnumber( vState, mID );
	lua_pushnil( vState );

	// Remove from task table and pop table from stack

	lua_settable( vState, -3 );
	lua_pop( vState, 1 );
}

//--------------------------------
bool ScriptTask::resume( )
{
	int ret = lua_resume( mState, (int)mParams );
	mParams = 0;

	if ( ret == 2 )
	{
		printf( "Task error: %s\n", lua_tostring( mState, lua_gettop( mState ) ) );
		return true;
	}

	return ( ret == 0 );
}

//--------------------------------
bool ScriptTask::tick( float vDelta )
{
	// Increase total run time

	mTime += vDelta;

	if ( mBlocked )
	{
		// See if we need to keep track of time

		if ( mBlockDelay < 0.0f )
			return false;

		// Increase block timer and wake up if necessary

		mBlockTimer += vDelta;
		if ( mBlockTimer >= mBlockDelay )
			mBlocked = false;
		else
			return false;
	}

	// Resume task

	return resume( );
}

//--------------------------------
void ScriptTask::block( float vDelay )
{
	mBlockDelay = vDelay;
	mBlockTimer = 0.0f;

	mBlocked = true;
}

//--------------------------------
void ScriptTask::unblock( )
{
	mBlockDelay = 0.0f;
	mBlockTimer = 0.0f;

	mBlocked = false;
}

}
