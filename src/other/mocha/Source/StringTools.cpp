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

#include "Mocha/Exception.h"
#include "Mocha/StringTools.h"
#include "Mocha/Rectangle.h"
#include "Mocha/Vector2.h"
#include "Mocha/Vector3.h"
#include "Mocha/Color.h"

namespace Mocha
{

//--------------------------------
inline bool ischar( char c, const char* chars )
{
	int x;
	for ( x = 0; chars[x] != 0; x++ )
	{
		if ( chars[x] == c )
			return true;
	}

	return false;
}

//--------------------------------
StringList TokenizeString( const String& line, const char* delims )
{
	StringList tokens;
	String tmp;

	// Get rid of any extra white space

	String stripped = TrimString( line );

	bool inDelim = false;

	int size = (int)stripped.size( );
	char str = 0;

	int x;
	for ( x = 0; x < size; x++ )
	{
		// Get next character

		char c = stripped[x];
	
		if ( (c == '\"') || (c == '\'') )
		{
			// Push any existing token

			if ( tmp != "" )
			{
				tokens.push_back( tmp );
				tmp = "";
			}

			// Read entire string

			x++;
			while ( (x < size) && (stripped[x] != c)  )
				tmp += stripped[x++];

			// Push string

			tokens.push_back( tmp );
			tmp = "";

			inDelim = true;
		}
		else if ( ischar( c, delims ) )
		{
			if ( inDelim == false )
			{
				tokens.push_back( tmp );
				tmp = "";
			}

			inDelim = true;
		}
		else if ( c == '#' )
		{
			// Found a comment... break from line
			break;
		}
		else
		{
			inDelim = false;
			tmp += c;
		}
	}

	if ( tmp != "" )
		tokens.push_back( tmp );

	return tokens;
}

//--------------------------------
StringList SplitString( const String& line, const char* delims, bool first, bool skiprep )
{
	if ( delims == 0 )
		delims = " \r\n\t";

	StringList rv;

	String::const_iterator i = line.begin( );
	String::const_iterator j = line.begin( );

	if( line == "" )
	{
		rv.push_back( "" );
		return rv;
	}

	while( j != line.end( ) )
	{
		// Skip over repetitive delimiters.
		while( (j != line.end( )) && ischar( (*j), delims ) )
		{
			++j;
			if ( skiprep == false )
				break;
		}

		// Anchor at first non-delimiter.
		i = j;

		// Find the next delimiter.
		while( (j != line.end( )) && !ischar( (*j), delims ) )
		{
			++j;
		}
 
		// Save the string you've found.
		rv.push_back( String( i, j ) );

		if ( first )
		{
			if ( j != line.end( ) )
				rv.push_back( String( j+1, line.end( ) ) );

			return rv;
		}
	}

	return rv;
}

//--------------------------------------------
String GetStringFileName( const String& vPath )
{
	StringList parts = SplitString( vPath, "." );
	if ( parts.size( ) <= 0 )
		return "";

	return parts[0];
}

//--------------------------------------------
int rfind( const String& line, char c )
{
	int size = (int)line.size( );

	int index;
	for ( index = size-1; index >= 0; index-- )
	{
		if ( line[index] == c )
			return index;
	}

	return -1;
}

//--------------------------------
void SplitPath( const String& line, String& path, String& name, char delim )
{
	if ( delim == 0 )
	{
		delim = '/';
	}

	bool found = false;
	int size = (int)line.size( );

	// Get index of last slash
	int index = rfind( line, delim );

	// See if a delimeter was found
	if ( index < 0 )
	{
		path = "";
		name = line;
		return;
	}

	// Absolute path with single slash
	if ( index == 0 )
	{
		path = "/";
		name = line.c_str( )+1;
		return;
	}

	int y;

	// Get everything before delimeter

	for ( y = 0; y < index; y++ )
		path += line[y];

	// Get everything after delimeter

	for ( y = index+1; y < size; y++ )
		name += line[y];
}

//--------------------------------
String CombinePath( const String& first, const String& second )
{
	String tmp;

	if ( Mocha::TrimString( second ) == "" )
		return first;

	tmp = first + "/" + second;
	return tmp;
}

//--------------------------------
String TrimString( const String& line, const char* delims )
{
	String result = line;
	String::size_type index = result.find_last_not_of( delims );
  
	if( index != String::npos )
		result.erase( ++index );

	index = result.find_first_not_of( delims );
	if( index != String::npos )
		result.erase( 0, index );
	else
		result.erase( );
  
	return result;
}

//--------------------------------
String GetStringFileExtension( const String& vFileName )
{
	StringList parts = SplitString( vFileName, "." );
	if ( parts.size( ) <= 1 )
		return "";

	return LowerString( parts[parts.size( )-1] );
}

//--------------------------------
String LowerString( const String& vIn )
{
	String tmp = vIn;

	// Convert string to lower case

	std::transform( tmp.begin( ), tmp.end( ), tmp.begin( ), tolower );
	return tmp;
}

//--------------------------------
bool StringToBool( const String& vString )
{
	return ( LowerString( vString ) == "true" ) ? true : false;
}

//--------------------------------------------
String BoolToString( bool v )
{
	return ( v == true ) ? "true" : "false";
}

//--------------------------------
int StringToInt( const String& vString )
{
	return atoi( vString.c_str( ) );
}

//--------------------------------------------
String IntToString( int v )
{
	static char buffer[128];
	sprintf( buffer, "%d", v );
	return buffer;
}

//--------------------------------
float StringToFloat( const String& vString )
{
	float i = 0.0f;
	sscanf( vString.c_str( ), "%f", &i );

	return i;
}

//--------------------------------------------
String FloatToString( float v )
{
	static char buffer[128];
	sprintf( buffer, "%f", v );
	return buffer;
}

//--------------------------------
Vector3 StringToVector3( const String& vString )
{
	StringList tmp = SplitString( vString );
	if ( tmp.size( ) < 3 )
		throw Exception( "Not enough tokens in vector3 string" );

	return Vector3( StringToFloat( tmp[0] ), StringToFloat( tmp[1] ), StringToFloat( tmp[2] ) );
}

//--------------------------------
String Vector3ToString( const Vector3& vValue )
{
	return FloatToString( vValue.x ) + " "
		   + FloatToString( vValue.y ) + " "
		   + FloatToString( vValue.z );
}

//--------------------------------
Vector2 StringToVector2( const String& vString )
{
	StringList tmp = SplitString( vString );
	if ( tmp.size( ) < 2 )
		throw Exception( "Not enough tokens in vector2 string" );

	return Vector2( StringToFloat( tmp[0] ), StringToFloat( tmp[1] ) );
}

//--------------------------------
String Vector2ToString( const Vector2& vValue )
{
	return FloatToString( vValue.x ) + " " + FloatToString( vValue.y );
}

//--------------------------------
Color StringToColor( const String& vString )
{
	StringList tmp = SplitString( vString );
	if ( tmp.size( ) < 4 )
		throw Exception( "Not enough tokens in color string" );

	return Color( StringToFloat( tmp[0] ), StringToFloat( tmp[1] ), StringToFloat( tmp[2] ), StringToFloat( tmp[3] ) );
}

//--------------------------------
String ColorToString( const Color& vValue )
{
	return FloatToString( vValue.r ) + " " 
		   + FloatToString( vValue.g ) + " "
		   + FloatToString( vValue.b ) + " "
		   + FloatToString( vValue.a );
}

//--------------------------------
Rectangle StringToRectangle( const String& vString )
{
	StringList tmp = SplitString( vString );
	if ( tmp.size( ) < 4 )
		throw Exception( "Not enough tokens in rectangle string" );

	Rectangle r;
	r.setPosition( StringToFloat( tmp[0] ), StringToFloat( tmp[1] ) );
	r.setSize( StringToFloat( tmp[2] ), StringToFloat( tmp[3] ) );

	return r;
}

//--------------------------------
Rectangle StringToRectangleLTRB( const String& vString )
{
	StringList tmp = SplitString( vString );
	if ( tmp.size( ) < 4 )
		throw Exception( "Not enough tokens in rectangle string" );

	Rectangle r;
	r.left = StringToFloat( tmp[0] );
	r.top = StringToFloat( tmp[1] );
	r.right = StringToFloat( tmp[2] );
	r.bottom = StringToFloat( tmp[3] );

	return r;
}

//--------------------------------
String RectangleToString( const Rectangle& vValue )
{
	return FloatToString( vValue.left ) + " "
		   + FloatToString( vValue.top ) + " "
		   + FloatToString( vValue.getWidth( ) ) + " "
		   + FloatToString( vValue.getHeight( ) );
}

//--------------------------------
String PointerToString( const void* vValue )
{
	static char buffer[128];
	sprintf( buffer, "%p", vValue );
	return buffer;
}

}
