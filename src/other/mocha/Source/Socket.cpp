/*
-----------------------------------------------------------------------------
This source file is part of Mocha
For the latest info, see http://www.rightbraingames.com/

Copyright (c) 2000-2006 Right Brain Games Inc.

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

#ifdef WIN32

#include <windows.h>
#include <winsock.h>
#include <fcntl.h>

#include "Mocha/Socket.h"
#include "Mocha/Exception.h"

namespace Mocha
{

//--------------------------------------------
Socket::Socket( )
: mSocket( -1 )
{
	// ...
}

//--------------------------------------------
Socket::~Socket( )
{
	close( );
}

//--------------------------------------------
void Socket::setBlocking( bool vWhich )
{
	ULONG v = ( vWhich ? 0 : 1 );
	ioctlsocket( mSocket, FIONBIO, &v );
}

//--------------------------------------------
void Socket::connect( const Mocha::String& vName, size_t vPort )
{
	struct sockaddr_in their_addr;
	struct hostent* hostEnt;

	// Make sure socket is closed

	close( );

	// Resolve the host name

	hostEnt = gethostbyname( vName.c_str( ) );
	if ( hostEnt == 0 )
		throw Exception( "Unable to resolve host name '" + vName + "'" );

	// Fill in address structure

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons( vPort );
    their_addr.sin_addr = *((struct in_addr *)hostEnt->h_addr);

    memset( their_addr.sin_zero, '\0', sizeof( their_addr.sin_zero ) );

	// Create the socket

	mSocket = socket( PF_INET, SOCK_STREAM, 0 );
	if ( mSocket == -1 )
		throw Exception( "Unable to create socket object" );

	// Establish connection

	int res = ::connect( mSocket, (struct sockaddr*)&their_addr, sizeof( their_addr ) );
	if ( res == -1 )
		throw Exception( "Unable to connect to host '" + vName + "'" );
}

//--------------------------------------------
void Socket::close( )
{
	if ( mSocket > -1 )
	{
#ifdef WIN32
		::closesocket( mSocket );
#else
		::close( mSocket );
#endif

		mSocket = -1;
	}
}

//--------------------------------------------
size_t Socket::send( const void* vData, size_t vSize )
{
	int res = ::send( mSocket, (const char*)vData, vSize, 0 );
	if ( res <= 0 )
	{
		int code = WSAGetLastError( );
		if ( code == WSAEWOULDBLOCK )
			return 0;

		throw SocketErrorException( );
	}

	return (size_t)res;
}

//--------------------------------------------
size_t Socket::receive( void* vData, size_t vSize )
{
	int res = ::recv( mSocket, (char*)vData, vSize, 0 );
	if ( res <= 0 )
	{
		int code = WSAGetLastError( );
		if ( code == WSAEWOULDBLOCK )
			return 0;

		throw SocketErrorException( );
	}


	return (size_t)res;
}

//--------------------------------------------
void InitializeNetworking( )
{
	WORD versionRequested = MAKEWORD( 1, 1 );

	WSADATA wsaData;
	if ( WSAStartup( versionRequested, &wsaData ) )
	   throw Exception( "WSAStartup failed" );

	if ( (LOBYTE( wsaData.wVersion ) != 1) || (HIBYTE( wsaData.wVersion ) != 1) )
	{
	   WSACleanup ( );
	   throw Exception( "Bad WinSock version" );
	}
}

}

#endif
