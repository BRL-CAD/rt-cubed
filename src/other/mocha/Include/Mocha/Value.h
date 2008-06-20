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

#ifndef MOCHA_VALUE_H
#define MOCHA_VALUE_H

#include <vector>

#include "Mocha/Exception.h"
#include "Mocha/Platform.h"

namespace Mocha
{

//--------------------------------
enum ValueType
{
	VALUE_NONE = 0,
	VALUE_STRING,
	VALUE_NUMBER,
	VALUE_OBJECTREF,
	VALUE_OBJECTWEAK,
	VALUE_VECTOR3,
	VALUE_VECTOR2,
	VALUE_RECTANGLE,
	VALUE_COLOR,
	VALUE_BOOL,
	VALUE_LIST,
	VALUE_QUATERNION
};

//--------------------------------
class ValueErrorException : public Exception
{
public:
	ValueErrorException( const String& vMessage )
		: Exception( vMessage )
	{
		// ...
	}

	virtual ~ValueErrorException( )
	{
		// ...
	}
};

//--------------------------------
class Object;
class Vector3;
class Vector2;
class Rectangle;
class Quaternion;
class Stream;
class Color;

//--------------------------------
class Value;
typedef std::vector<Value> ValueList;

//--------------------------------
/// A variant value class that can store multiple types of values
class MOCHA_EXPORT Value
{
private:
	struct Float4
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct Float3
	{
		float x;
		float y;
		float z;
	};

	struct Float2
	{
		float x;
		float y;
	};

	union
	{
		ValueList* mList;
		String* mString;
		Object* mObject;
		Float4 mFloat4;
		Float3 mFloat3;
		Float2 mFloat2;
		float mNumber;
		bool mBool;
	};

	int8 mType;

	void free( );

public:
	inline Value( )
		: mType( VALUE_NONE )
	{
		// ...
	}

	inline Value( const Value& vOther )
		: mType( VALUE_NONE )
	{
		set( vOther );
	}

	inline Value( int vValue )
		: mType( VALUE_NONE )
	{
		setNumber( (float)vValue );
	}

	inline Value( size_t vValue )
		: mType( VALUE_NUMBER )
	{
		setNumber( (float)vValue );
	}

	inline Value( float vValue )
		: mType( VALUE_NONE )
	{
		setNumber( vValue );
	}

	inline Value( const char* vValue )
		: mType( VALUE_NONE )
	{
		setString( vValue );
	}

	inline Value( const String& vValue )
		: mType( VALUE_NONE )
	{
		setString( vValue );
	}

	inline Value( const Color& vValue )
		: mType( VALUE_NONE )
	{
		setColor( vValue );
	}

	inline Value( const Vector3& vValue )
		: mType( VALUE_NONE )
	{
		setVector3( vValue );
	}

	inline Value( const Vector2& vValue )
		: mType( VALUE_NONE )
	{
		setVector2( vValue );
	}

	inline Value( const Rectangle& vValue )
		: mType( VALUE_NONE )
	{
		setRectangle( vValue );
	}

	inline Value( const Quaternion& vValue )
		: mType( VALUE_NONE )
	{
		setQuaternion( vValue );
	}

	inline Value( Object* vValue )
		: mType( VALUE_NONE )
	{
		setObject( vValue );
	}

	inline Value( bool vValue )
		: mType( VALUE_NONE )
	{
		setBool( vValue );
	}

	inline Value( const ValueList& vValue )
		: mType( VALUE_NONE )
	{
		setList( vValue );
	}

	inline ~Value( )
	{
		free( );
	}

	/// Sets the value from another
	inline Value& operator = ( const Value& vOther )
	{
		set( vOther );
		return *this;
	}

	/// Sets the value from another
	inline void set( const Value& vOther )
	{
		switch ( vOther.mType )
		{
		case VALUE_STRING:
			setString( *vOther.mString );
			break;

		case VALUE_NUMBER:
			setNumber( vOther.mNumber );
			break;

		case VALUE_BOOL:
			setBool( vOther.mBool );
			break;

		case VALUE_OBJECTREF:
			setObject( vOther.mObject );
			break;

		case VALUE_OBJECTWEAK:
			setObjectWeak( vOther.mObject );
			break;

		case VALUE_COLOR:
			setColor( (Color&)vOther.mFloat4 );
			break;

		case VALUE_VECTOR3:
			setVector3( (Vector3&)vOther.mFloat3 );
			break;

		case VALUE_VECTOR2:
			setVector2( (Vector2&)vOther.mFloat2 );
			break;

		case VALUE_RECTANGLE:
			setRectangle( (Rectangle&)vOther.mFloat4 );
			break;

		case VALUE_LIST:
			setList( *vOther.mList );
			break;

		case VALUE_NONE:
			setNone( );
			break;
		}
	}

	/// Gets the type of the value. See ValueType
	inline ValueType getType( ) const
	{
		return (ValueType)mType;
	}

	/// Returns whether or not the value stores a reference to an object
	inline bool isObject( ) const
	{
		return ( (mType == VALUE_OBJECTREF) || (mType == VALUE_OBJECTWEAK) );
	}

	/// Sets the value as a String
	inline void setString( const String& vValue )
	{
		free( );

		mString = new String( vValue );
		mType = VALUE_STRING;
	}

	/// Gets the value as a String. No conversion is done
	inline const String& getString( ) const
	{
		if ( mType != VALUE_STRING )
			throw ValueErrorException( "Value is not a string" );

		return *mString;
	}

	/// Sets the value as a floating point number
	inline void setNumber( float vNumber )
	{
		free( );

		mNumber = vNumber;
		mType = VALUE_NUMBER;
	}

	/// Gets the value as floating point number. No conversion is done
	inline float getNumber( ) const
	{
		if ( mType != VALUE_NUMBER )
			throw ValueErrorException( "Value is not a number" );

		return mNumber;
	}

	/// Sets the value as a boolean
	inline void setBool( bool vValue )
	{
		free( );

		mBool = vValue;
		mType = VALUE_BOOL;
	}

	/// Gets the value as a boolean. No conversion is done
	inline bool getBool( ) const
	{
		if ( mType != VALUE_BOOL )
			throw ValueErrorException( "Value is not a bool" );

		return mBool;
	}

	/// Sets the value as a list of values
	inline void setList( const ValueList& vValues )
	{
		free( );
		
		mList = new ValueList( vValues );
		mType = VALUE_LIST;
	}

	/// Gets the value as a list of values
	inline const ValueList& getList( ) const
	{
		if ( mType != VALUE_LIST )
			throw ValueErrorException( "Value is not a list" );

		return *mList;
	}

	/// Sets the value to None (Equivalent to NULL)
	inline void setNone( )
	{
		free( );
		mType = VALUE_NONE;
	}

	/// Sets the value as a weak pointer to an object
	void setObjectWeak( Object* vObject );

	/// Sets the value as a reference to an object
	void setObject( Object* vObject );

	/// Gets the value as a reference to an object. Does not do conversion
	Object* getObject( ) const;

	/// Sets the value as a color
	void setColor( const Color& vColor );

	/// Gets the value as a color. Does not do conversion
	const Color& getColor( ) const;

	/// Gets the value as a quaternion
	void setQuaternion( const Quaternion& vValue );

	/// Gets the value as a quaternion. Does not do conversion
	const Quaternion& getQuaternion( ) const;

	/// Sets the value as a Vector3
	void setVector3( const Vector3& vValue );

	/// Gets the value as a Vector3. Does not do conversion
	const Vector3& getVector3( ) const;

	/// Sets the value as a Vector2
	void setVector2( const Vector2& vValue );

	/// Gets the value as a Vector2. Does not do conversion
	const Vector2& getVector2( ) const;

	/// Sets the value as a Rectangle
	void setRectangle( const Rectangle& vValue );

	/// Gets the value as a Rectangle. Does not do conversion
	const Rectangle& getRectangle( ) const;

	/// Gets the value as a Rectangle. Does conversion if necessary
	Rectangle getAsRectangle( ) const;

	/// Gets the value as a quaternion. Does conversion if necessary
	Quaternion getAsQuaternion( ) const;

	/// Gets the value as a Vector3. Does conversion if necessary
	Vector3 getAsVector3( ) const;

	/// Gets the value as a Vector2. Does conversion if necessary
	Vector2 getAsVector2( ) const;

	/// Gets the value as a Color. Does conversion if necessary
	Color getAsColor( ) const;

	/// Gets the value as a String. Does conversion if necessary
	String getAsString( ) const;

	/// Gets the value as a float number. Does conversion if necessary
	float getAsNumber( ) const;

	/// Gets the value as bool. Does conversion if necessary
	bool getAsBool( ) const;

	/// Writes the value to a stream
	void read( const Mocha::Stream& vStream );

	/// Reads the value from a stream
	void write( Mocha::Stream& vStream ) const;
};

}

#endif
