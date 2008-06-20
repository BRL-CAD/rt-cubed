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

#ifndef MOCHA_SOCKET_H
#define MOCHA_SOCKET_H

#include "Mocha/Object.h"
#include "Mocha/Exception.h"

namespace Mocha
{

//--------------------------------------------
class SocketErrorException : public Exception
{
public:
	SocketErrorException( ) : Exception( "Socket error" )
	{
		// ...
	}
};

//--------------------------------------------
class MOCHA_EXPORT Socket : public Mocha::Object
{
private:
	int mSocket;
	
public:
	Socket( );

	virtual ~Socket( );

	/// Sets whether or not the socket should block
	void setBlocking( bool vWhich );

	/// Connects to the specified address and port
	/*! \param vName The host name to connect to
		\param vPort The port to use */
	void connect( const Mocha::String& vName, size_t vPort );

	/// Closes the socket
	void close( );

	/// Sends data through the socket. Throws a SocketErrorException if an error occurs. May return 0 if the socket is non-blocking
	/*! \param A pointer to the data buffer to send
		\param vSize The amount of data in the buffer, in bytes
		\return The number of bytes actually sent */
	size_t send( const void* vData, size_t vSize );

	/// Receives data through the socket. Throws a SocketErrorException if an error occurs. May return 0 if the socket is non-blocking
	/*! \param A pointer to the buffer to receive the data
		\param vSize The size of the buffer
		\return The number of actually received */
	size_t receive( void* vData, size_t vSize );
};

//--------------------------------------------
/// Initializes the networking system. Call this before using Socket
MOCHA_EXPORT extern void InitializeNetworking( );

}

#endif
