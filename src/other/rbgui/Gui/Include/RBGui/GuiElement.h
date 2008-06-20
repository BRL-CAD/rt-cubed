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

#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <map>

#include "Mocha/RefPointer.h"
#include "Mocha/Object.h"

#include "RBGui/GuiCallback.h"
#include "RBGui/Platform.h"

namespace RBGui
{

/// Base class for all elements of the Gui layout (Windows and widgets)
class GUI_EXPORT GuiElement : public Mocha::Object
{
private:
	typedef std::map< Mocha::String, Mocha::RefPointer<GuiCallback> > CallbackMap;
	CallbackMap mCallbacks;

	Mocha::RefPointer<Mocha::RefCounted> mObject;

protected:
	void doCallback( const Mocha::ValueList& vData, const Mocha::String& vName = "Default" );

	void doCallback( const Mocha::String& vName = "Default" );

public:
	GuiElement( );

	virtual ~GuiElement( );

	/// Sets a callback to be called on a gui event
	/*! \param vCallback A pointer to the callback class to be called. See GuiCallback
		\param vName The name of the event to bind to */
	void setCallback( GuiCallback* vCallback, const Mocha::String& vName = "Default" );

	/// Sets a callback for a member function of an object on a gui event
	/*! \param A pointer to the member function to be called
		\param vObject A pointer to the object that owns the member function
		\param vName The name of the event to bind to */
	template <typename T>
	inline void setCallback( void (T::*MemberFunction)( GuiElement& vWidget, const Mocha::ValueList& vData ), T* vObject, const Mocha::String& vName = "Default" )
	{
		setCallback( new MemberGuiCallback<T>( MemberFunction, vObject ), vName );
	}

	/// Sets a callback for a static function on a gui event
	inline void setCallback( void (*StaticFunction)( GuiElement& vWidget, const Mocha::ValueList& vData ), const Mocha::String& vName = "Default" )
	{
		setCallback( new StaticFunctionGuiCallback( StaticFunction ), vName );
	}

	/// Sets an object to associate with the element
	void setObject( Mocha::RefCounted* vObject );

	/// Gets the object that is associated with the element
	Mocha::RefCounted* getObject( ) const;
};

}

#endif
