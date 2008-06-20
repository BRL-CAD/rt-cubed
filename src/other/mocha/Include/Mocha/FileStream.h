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

#ifndef MOCHA_FILESTREAM_H
#define MOCHA_FILESTREAM_H

#include <stdio.h>

#include "Mocha/Stream.h"

namespace Mocha
{

class MOCHA_EXPORT FileStream : public Stream
{
private:
	FILE* mFile;

public:
	FileStream( );

	virtual ~FileStream( );

	/// Opens a file to read/write
	/*! \param vPath The path of the file to open
		\param vMode The mode string to use. This is same as the fopen mode string */
	void open( const String& vPath, const String& vMode );

	/// Gets whether or not the file is open
	bool getOpen( ) const;

	/// Closes the file
	void close( );

	/// Flushes the file stream to disk
	void flush( );

	virtual size_t writeData( const void* vData, size_t vSize );

	virtual size_t readData( void* vData, size_t vSize ) const;

	virtual void seek( size_t vPosition ) const;

	virtual size_t getPosition( ) const;

	virtual size_t getSize( ) const;

	virtual bool getEndOfStream( ) const;
};

}

#endif
