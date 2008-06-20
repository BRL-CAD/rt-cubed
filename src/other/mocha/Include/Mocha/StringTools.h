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

#ifndef MOCHA_STRINGTOOLS_H
#define MOCHA_STRINGTOOLS_H

#include "Mocha/Platform.h"

namespace Mocha
{

//--------------------------------
class Vector3;
class Vector2;
class Rectangle;
class Color;

//--------------------------------
MOCHA_EXPORT extern String GetStringFileExtension( const String& vFileName );

//--------------------------------------------
MOCHA_EXPORT extern String GetStringFileName( const String& vPath );

//--------------------------------
MOCHA_EXPORT extern StringList SplitString( const String& line, const char* delims = " \r\n\t", bool first = false, bool skiprep = true );

//--------------------------------
MOCHA_EXPORT extern String CombinePath( const String& first, const String& second );

//--------------------------------
MOCHA_EXPORT extern void SplitPath( const String& line, String& path, String& name, char delim = 0 );

//--------------------------------
MOCHA_EXPORT extern StringList TokenizeString( const String& line, const char* delims = " \r\t\n" );

//--------------------------------
MOCHA_EXPORT extern String TrimString( const String& line, const char* delims = " \t\r\n" );

//--------------------------------
MOCHA_EXPORT extern String LowerString( const String& vIn );

//--------------------------------
MOCHA_EXPORT extern int StringToInt( const String& vString );

//--------------------------------
MOCHA_EXPORT extern String IntToString( int vValue );

//--------------------------------
MOCHA_EXPORT extern float StringToFloat( const String& vString );

//--------------------------------
MOCHA_EXPORT extern String FloatToString( float vValue );

//--------------------------------
MOCHA_EXPORT extern bool StringToBool( const String& vString );

//--------------------------------
MOCHA_EXPORT extern String BoolToString( bool vValue );

//--------------------------------
MOCHA_EXPORT extern Vector3 StringToVector3( const String& vString );

//--------------------------------
MOCHA_EXPORT extern String Vector3ToString( const Vector3& vValue );

//--------------------------------
MOCHA_EXPORT extern Vector2 StringToVector2( const String& vString );

//--------------------------------
MOCHA_EXPORT extern String Vector2ToString( const Vector2& vValue );

//--------------------------------
MOCHA_EXPORT extern Color StringToColor( const String& vString );

//--------------------------------
MOCHA_EXPORT extern String ColorToString( const Color& vValue );

//--------------------------------
MOCHA_EXPORT extern Rectangle StringToRectangle( const String& vString );

//--------------------------------
MOCHA_EXPORT extern Rectangle StringToRectangleLTRB( const String& vString );

//--------------------------------
MOCHA_EXPORT extern String RectangleToString( const Rectangle& vValue );

//--------------------------------
MOCHA_EXPORT extern String PointerToString( const void* vValue );

}

#endif
