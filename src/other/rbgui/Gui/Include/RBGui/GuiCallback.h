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

#ifndef GUI_CALLBACK_H
#define GUI_CALLBACK_H

#include "Mocha/Value.h"
#include "Mocha/RefCounted.h"

namespace RBGui
{

//--------------------------------
class GuiElement;

//--------------------------------
/// Base class for all Gui event listeners
class GuiCallback : public Mocha::RefCounted
{
public:
	/// Called when a Gui event happens
	/*! \param vElement The GuiElement that raised the event
		\param vData The list of values that are associated with the event */
	virtual void onGuiEvent( GuiElement& vElement, const Mocha::ValueList& vData ) = 0;
};

//--------------------------------
/// A callback class that calls a static function
class StaticFunctionGuiCallback : public GuiCallback
{
private:
	typedef void (*StaticFunction)( GuiElement& vElement, const Mocha::ValueList& vData ); 
	StaticFunction mFunc;

public:
	inline StaticFunctionGuiCallback( StaticFunction vFunc )
		: mFunc( vFunc )
	{
		// ...
	}

	virtual void onGuiEvent( GuiElement& vElement, const Mocha::ValueList& vData )
	{
		mFunc( vElement, vData );
	}
};

//--------------------------------
/// A callback class that calls a member function of a class
template <typename T>
class MemberGuiCallback : public GuiCallback
{
private:
	typedef void (T::*MemberFunction)( GuiElement& vElement, const Mocha::ValueList& vData ); 
	MemberFunction mFunc;

	T* mObject;

public:
	inline MemberGuiCallback( MemberFunction vFunc, T* vObj )
		: mObject( vObj ), mFunc( vFunc )
	{
		// ...
	}

	virtual void onGuiEvent( GuiElement& vElement, const Mocha::ValueList& vData )
	{
		(mObject->*mFunc)( vElement, vData );
	}
};

}

#endif
