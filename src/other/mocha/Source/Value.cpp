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

#include "Mocha/Value.h"
#include "Mocha/Object.h"
#include "Mocha/Color.h"
#include "Mocha/Rectangle.h"
#include "Mocha/Vector3.h"
#include "Mocha/Vector2.h"
#include "Mocha/StringTools.h"
#include "Mocha/Quaternion.h"
#include "Mocha/Stream.h"

namespace Mocha
{

//--------------------------------
void Value::free( )
{
	switch ( mType )
	{
	case VALUE_STRING:
		delete mString;
		break;

	case VALUE_LIST:
		delete mList;
		break;

	case VALUE_OBJECTREF:
		mObject->decRef( );
		break;

	case VALUE_OBJECTWEAK:
		if ( mObject )
			mObject->freeWeakRef( (void**)&mObject );
		break;
	}
}

//--------------------------------
void Value::setObjectWeak( Object* vObject )
{
	if ( vObject )
		vObject->grabWeakRef( (void**)&mObject );

	free( );

	mObject = vObject;
	mType = VALUE_OBJECTWEAK;
}

//--------------------------------
void Value::setObject( Object* vObject )
{
	vObject->incRef( );
	free( );

	mObject = vObject;
	mType = VALUE_OBJECTREF;
}

//--------------------------------
Object* Value::getObject( ) const
{
	if ( (mType != VALUE_OBJECTREF) && (mType != VALUE_OBJECTWEAK)  )
		throw ValueErrorException( "Value is not an object" );

	return mObject;
}

//--------------------------------
bool Value::getAsBool( ) const
{
	switch ( mType )
	{
	case VALUE_NUMBER:
		return ( mNumber != 0 ) ? true : false;

	case VALUE_STRING:
		return ((*mString) == "true") ? true : false;

	case VALUE_BOOL:
		return mBool;

	case VALUE_NONE:
		return false;
	}

	throw ValueErrorException( "Unable to convert value to bool" );
}

//--------------------------------
void Value::setColor( const Color& vColor )
{
	free( );

	mFloat4 = (Float4&)vColor;
	mType = VALUE_COLOR;
}

//--------------------------------
const Color& Value::getColor( ) const
{
	if ( mType != VALUE_COLOR )
		throw ValueErrorException( "Value is not a color" );

	return (Color&)mFloat4;
}

//--------------------------------
void Value::setQuaternion( const Quaternion& vValue )
{
	free( );

	mFloat4 = (Float4&)vValue;
	mType = VALUE_QUATERNION;
}

//--------------------------------
const Quaternion& Value::getQuaternion( ) const
{
	if ( mType != VALUE_QUATERNION )
		throw ValueErrorException( "Value is not a quaternion" );

	return (Quaternion&)mFloat4;
}

//--------------------------------
void Value::setVector3( const Vector3& vValue )
{
	free( );

	mFloat3 = (Float3&)vValue;
	mType = VALUE_VECTOR3;
}

//--------------------------------
const Vector3& Value::getVector3( ) const
{
	if ( mType != VALUE_VECTOR3 )
		throw ValueErrorException( "Value is not a vector3" );

	return (Vector3&)mFloat3;
}

//--------------------------------
void Value::setVector2( const Vector2& vValue )
{
	free( );

	mFloat2 = (Float2&)vValue;
	mType = VALUE_VECTOR2;
}

//--------------------------------
const Vector2& Value::getVector2( ) const
{
	if ( mType != VALUE_VECTOR2 )
		throw ValueErrorException( "Value is not a vector2" );

	return (Vector2&)mFloat2;
}

//--------------------------------
void Value::setRectangle( const Rectangle& vValue )
{
	free( );

	mFloat4 = (Float4&)vValue;
	mType = VALUE_RECTANGLE;
}

//--------------------------------
const Rectangle& Value::getRectangle( ) const
{
	if ( mType != VALUE_RECTANGLE )
		throw ValueErrorException( "Value is not a rectangle" );

	return (Rectangle&)mFloat4;
}

//--------------------------------
Rectangle Value::getAsRectangle( ) const
{
	switch ( mType )
	{
	case VALUE_RECTANGLE:
		return (Rectangle&)mFloat4;

	case VALUE_STRING:
		return StringToRectangle( *mString );
	}

	throw ValueErrorException( "Unable to convert value to rectangle" );
}

//--------------------------------
Vector3 Value::getAsVector3( ) const
{
	switch ( mType )
	{
	case VALUE_VECTOR3:
		return (Vector3&)mFloat3;

	case VALUE_STRING:
		return StringToVector3( *mString );
	}

	throw ValueErrorException( "Unable to convert value to vector3" );
}

//--------------------------------
Vector2 Value::getAsVector2( ) const
{
	switch ( mType )
	{
	case VALUE_VECTOR2:
		return (Vector2&)mFloat2;

	case VALUE_STRING:
		return StringToVector2( *mString );
	}

	throw ValueErrorException( "Unable to convert value to vector2" );
}

//--------------------------------
Color Value::getAsColor( ) const
{
	switch ( mType )
	{
	case VALUE_COLOR:
		return (Color&)mFloat4;

	case VALUE_STRING:
		return StringToColor( *mString );
	}

	throw ValueErrorException( "Unable to convert value to color" );
}

//--------------------------------
String Value::getAsString( ) const
{
	switch ( mType )
	{
	case VALUE_STRING:
		return *mString;

	case VALUE_NUMBER:
		return FloatToString( mNumber );

	case VALUE_BOOL:
		return BoolToString( mBool );

	case VALUE_VECTOR3:
		return Vector3ToString( (Vector3&)mFloat3 );

	case VALUE_VECTOR2:
		return Vector2ToString( (Vector2&)mFloat2 );

	case VALUE_RECTANGLE:
		return RectangleToString( (Rectangle&)mFloat4 );

	case VALUE_COLOR:
		return ColorToString( (Color&)mFloat4 );

	case VALUE_OBJECTREF:
		return ( mObject != 0 ) ? mObject->getAsString( ) : "<null object ref>";

	case VALUE_OBJECTWEAK:
		return ( mObject != 0 ) ? mObject->getAsString( ) : "<null object weak ref>";

	case VALUE_NONE:
		return "<none>";
	}

	throw ValueErrorException( "Unable to convert value to string" );
}

//--------------------------------
float Value::getAsNumber( ) const
{
	switch ( mType )
	{
	case VALUE_NUMBER:
		return mNumber;

	case VALUE_STRING:
		return (float)atof( mString->c_str( ) );

	case VALUE_BOOL:
		return ( mBool == true ) ? 1.0f : 0.0f;

	case VALUE_NONE:
		return 0.0f;
	}

	throw ValueErrorException( "Unable to convert value to number" );
}

//--------------------------------
Quaternion Value::getAsQuaternion( ) const
{
	switch ( mType )
	{
	case VALUE_QUATERNION:
		return (Quaternion&)mFloat4;
	}

	throw ValueErrorException( "Unable to convert value to quaternion" );
}

//--------------------------------
void Value::read( const Mocha::Stream& vStream )
{
	// Read type id

	int type = vStream.read<Mocha::int8>( );

	switch ( type )
	{
	case VALUE_NUMBER:
		setNumber( vStream.read<float>( ) );
		break;

	case VALUE_STRING:
		setString( vStream.read<String>( ) );
		break;

	case VALUE_COLOR:
		setColor( vStream.read<Color>( ) );
		break;

	case VALUE_RECTANGLE:
		setRectangle( vStream.read<Rectangle>( ) );
		break;

	case VALUE_BOOL:
		setBool( vStream.read<bool>( ) );
		break;

	case VALUE_VECTOR2:
		setVector2( vStream.read<Vector2>( ) );
		break;

	case VALUE_VECTOR3:
		setVector3( vStream.read<Vector3>( ) );
		break;

	case VALUE_QUATERNION:
		setQuaternion( vStream.read<Quaternion>( ) );
		break;

	case VALUE_LIST:
		{
			size_t count = vStream.read<size_t>( );
			Mocha::ValueList l;

			size_t x;
			for ( x = 0; x < count; x++ )
			{
				Mocha::Value v;
				vStream.read( v );

				l.push_back( v );
			}

			setList( l );
		}
		break;
	}
}

//--------------------------------
void Value::write( Mocha::Stream& vStream ) const
{
	// Save type id

	vStream.write<Mocha::int8>( mType );

	switch ( mType )
	{
	case VALUE_NUMBER:
		vStream.write( mNumber );
		break;

	case VALUE_STRING:
		vStream.write( *mString );
		break;

	case VALUE_COLOR:
		vStream.write( (Color&)mFloat4 );
		break;

	case VALUE_RECTANGLE:
		vStream.write( (Rectangle&)mFloat4 );
		break;

	case VALUE_BOOL:
		vStream.write( mBool );
		break;

	case VALUE_VECTOR2:
		vStream.write( (Vector2&)mFloat2 );
		break;

	case VALUE_VECTOR3:
		vStream.write( (Vector3&)mFloat3 );
		break;

	case VALUE_QUATERNION:
		vStream.write( (Quaternion&)mFloat4 );
		break;

	case VALUE_LIST:
		{
			vStream.write( mList->size( ) );

			Mocha::ValueList::const_iterator it;
			for ( it = mList->begin( ); it != mList->end( ); it++ )
				(*it).write( vStream );
		}
		break;

	default:
		throw Exception( "Unable to save value type: " + Mocha::IntToString( mType ) );
	}
}

}
