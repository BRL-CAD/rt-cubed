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

#ifndef MOCHA_SCRIPTMANAGER_H
#define MOCHA_SCRIPTMANAGER_H

#include <list>

#include "Mocha/ScriptTask.h"
#include "Mocha/Exception.h"
#include "Mocha/RefPointer.h"
#include "Mocha/Object.h"
#include "Mocha/Value.h"

extern "C"
{
	struct lua_State;
};

namespace Mocha
{

//--------------------------------
class Stream;

//--------------------------------
class ScriptErrorException : public Exception
{
public:
	ScriptErrorException( const String& vMessage )
		: Exception( vMessage )
	{
		// ...
	}

	virtual ~ScriptErrorException( )
	{
		// ...
	}
};

//--------------------------------
enum ReturnMode
{
	RETURN_NORMAL = 0,
	RETURN_YIELD
};

//--------------------------------
class ScriptManager;
typedef ReturnMode (*ScriptCommand)( ScriptManager& vManager, const ValueList&, ValueList& ); 

//--------------------------------
/// Manages a self-contained scripting environment with multiple micro-threads
class MOCHA_EXPORT ScriptManager : public Object
{
private:
	typedef std::list< RefPointer<ScriptTask> > TaskList;
	TaskList mTasks;

	ScriptTask* mCurrentTask;

	size_t mTaskCounter;

	lua_State* mState;

	void* mUserData;

	static int spawnCmd( lua_State* vState );

	static int yieldCmd( lua_State* vState );

	static int sleepCmd( lua_State* vState );

	static int exitCmd( lua_State* vState );

	static int timeCmd( lua_State* vState );

	static int includeCmd( lua_State* vState );

	//static int newCmd( lua_State* vState );

	static int gcCmd( lua_State* vState );

	static int callCmd( lua_State* vState );

	static int indexCmd( lua_State* vState );

	static int cmdWrapper( lua_State* vState );

	void addTask( ScriptTask* vTask );

public:
	ScriptManager( );

	virtual ~ScriptManager( );

	/// Sets the user data to associate with the script manager
	void setUserData( void* vData );

	/// Gets the user data that is associated with the script manager
	void* getUserData( ) const;

	/// Adds a global script command
	/*! \param vName The name to give the command
		\param vCommand A pointer to the command function */
	void addCommand( const String& vName, ScriptCommand vCommand );

	/// Sets a global value
	/*! \param vName The name of the global value to set
		\param vValue The value to use */
	void setGlobal( const String& vName, const Value& vValue );

	/// Gets a global value
	/*! \param vName The name of the global to get
		\param vValue The value to be filled in. This will be set to none if the value does not exist */
	void getGlobal( const String& vName, Value& vValue );

	/// Calls a script command
	/*! \param vInput The input parameter value list
		\param vOutput The output parameter value list */
	void call( const String& vName, const ValueList& vInput, ValueList& vOutput );

	/// Spawns a new script micro-thread
	/*! \param vCommand The name of the command to execute in the new thread
		\param vValues The list of values to pass to the command as parameters */
	ScriptTask* spawnTask( const String& vCommand, const ValueList& vValues );

	/// Runs a script from a stream
	void runScript( const Stream& vStream );

	/// Runs a script from a file
	void runScript( const String& vPath );

	/// Updates the script manager. This should be called frequently for decent performance
	/*! \param vDelta The amount of time that has passed, in seconds */
	void tick( float vDelta );

	/// Gets the current executing script task
	/*! \return The currently executing script task, or 0 if there is none */
	ScriptTask* getCurrentTask( ) const;

	/// Gets the number of script tasks executing
	size_t getTaskCount( ) const;
};

}

#endif
