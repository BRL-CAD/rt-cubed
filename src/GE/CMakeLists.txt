#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2009 United States Government as represented by
#	the U.S. Army Research Laboratory.
#	
#	This library is free software; you can redistribute it and/or
#	modify it under the terms of the GNU Lesser General Public License
#	version 2.1 as published by the Free Software Foundation.
#	
#	This library is distributed in the hope that it will be useful, but
#	WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#	Lesser General Public License for more details.
#	
#	You should have received a copy of the GNU Lesser General Public
#	License along with this file; see the file named COPYING for more
#	information.
#	
#########################################################################
#	@file rt^3/src/GE/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring GeometryEngine          ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


set(GE_SOURCES
	GeometryEngine.cxx
	Logger.cxx
	io/ByteArrayInputStream.cxx
	io/ByteArrayOutputStream.cxx
	io/DataInputStream.cxx
	io/DataOutputStream.cxx
	io/FilterInputStream.cxx
	io/FilterOutputStream.cxx
	io/InputStream.cxx
	io/OutputStream.cxx
	io/PushbackInputStream.cxx
	exception/CloneNotSupportedException.cxx
	exception/Exception.cxx
	exception/NullPointerException.cxx
	exception/RuntimeException.cxx
	exception/Throwable.cxx
	exception/StreamEmptyException.cxx
	exception/EOFException.cxx
	exception/IOException.cxx
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

ADD_LIBRARY (ge SHARED ${GE_SOURCES})
TARGET_LINK_LIBRARIES(ge ${QT_LIBRARIES})

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")


ADD_SUBDIRECTORY(./libGeometry)
ADD_SUBDIRECTORY(./libImage)
ADD_SUBDIRECTORY(./libNumeric)
ADD_SUBDIRECTORY(./libRaytrace)
ADD_SUBDIRECTORY(./libUtility)
