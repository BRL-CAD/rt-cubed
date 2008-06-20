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

#include "Mocha/Object.h"
#include "Mocha/StringTools.h"

namespace Mocha
{

//--------------------------------
Object::Object( )
{
	// ...
}

//--------------------------------
Object::~Object( )
{
	// ...
}

//--------------------------------
CommandResult Object::invoke( const String& vName, const ValueList& vIn, ValueList& vOut )
{
	return CMDRESULT_INVALIDCOMMAND;
}

//--------------------------------
void Object::getValueList( ObjectValueEntryList& vOut ) const
{
	// ...
}

//--------------------------------
CommandResult Object::setValue( const String& vName, const Value& vValue )
{
	ValueList in;
	in.push_back( vValue );

	ValueList out;
	return invoke( "set" + vName, in, out );
}

//--------------------------------
CommandResult Object::getValue( const String& vName, Value& vValue ) const
{
	// It sucks, but we have to cast this to a non-const. Should be okay, though!

	ValueList in;

	ValueList out;
	CommandResult res = ((Object*)this)->invoke( "get" + vName, in, out );

	if ( out.size( ) > 0 )
		vValue = out[0];

	return res;
}

//--------------------------------
String Object::getAsString( ) const
{
	return "<object " + PointerToString( this ) + ">";
}

//--------------------------------
String Object::getClassName( ) const
{
	return "<unknown>";
}

}
