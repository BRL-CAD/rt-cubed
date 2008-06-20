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

#ifndef MOCHA_SCRIPTTASK_H
#define MOCHA_SCRIPTTASK_H

#include "Mocha/RefPointer.h"
#include "Mocha/Object.h"
#include "Mocha/Value.h"

#define TASKTABLE_NAME "__TASKS__"

extern "C"
{
	struct lua_State;
}

namespace Mocha
{

class MOCHA_EXPORT ScriptTask : public RefCounted
{
private:
	Mocha::RefPointer<Mocha::Object> mObject;

	lua_State* mState;

	float mBlockDelay;

	float mBlockTimer;

	float mTime;

	bool mBlocked;

	bool mTerminate;

	size_t mParams;

	size_t mID;

	bool resume( );

public:
	ScriptTask( size_t vID );

	virtual ~ScriptTask( );

	/// Sets the object to associate with this task
	void setObject( Mocha::Object* vObject );

	/// Gets the object that is associated with this task
	Mocha::Object* getObject( ) const;

	/// Adds a value to be returned to the script when it resumes
	void addResumeValue( const Mocha::Value& vValue );

	/// Prepares the script task for executing (Called by the ScriptManager)
	void prepare( lua_State* vState, size_t vFunctionIndex, size_t vParams );

	/// Ends a task (Called by the ScriptManager)
	void finish( lua_State* vState );

	/// Updates the task (Called by the ScriptManager)
	bool tick( float vDelta );

	/// Gets the Lua state owned by this task (Called by the ScriptManager)
	lua_State* getState( ) const;

	/// Returns true if the task has been terminated and will not resume
	bool getTerminated( ) const;

	/// Gets the amount of time, seconds, that the task has been running
	float getTime( ) const;

	/// Gets the unique ID of the task
	size_t getID( ) const;

	/// Terminates the task, causing it to never run again
	void terminate( );

	/// Blocks a task
	/*! \param vDelay The amount of time to block for, in seconds. If the amount is less than zero, the task will block forever */
	void block( float vDelay = -1.0f );

	/// Unblocks the task, allowing it to run again
	void unblock( );
};

}

#endif
