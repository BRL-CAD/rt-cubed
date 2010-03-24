#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2010 United States Government as represented by
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
#	@file /CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
#########################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.2)

#################################
INCLUDE (cmake/PrintHeader.cmake)
#################################

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

#Set VAR for top level include directory
SET(RT3_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
MESSAGE(STATUS "RT3_INCLUDE_DIR: ${CMAKE_SOURCE_DIR}/include")

#Setup unit testing compilation flag
SET (COMPILE_UNIT_TESTS ON CACHE BOOL "Compile the Unit test suite? (Requires CPPUNIT)")

#Setup search paths
SET(INCLUDE_SEARCH_PATHS 
	${INCLUDE_SEARCH_PATHS}
	/usr/brlcad/include 
	/usr/local/brlcad/include 
	/usr/local/include
	~/include
)

SET(LIB_SEARCH_PATHS 
	${LIB_SEARCH_PATHS}
	/usr/brlcad/lib 
	/usr/local/brlcad/lib 
	/usr/local/lib
	~/lib
	./src/other/mocha/
)

#Find BRLCAD
FIND_PACKAGE ( BRLCAD REQUIRED )

IF (COMPILE_UNIT_TESTS)
	FIND_PACKAGE ( CPPUNIT REQUIRED )
ENDIF (COMPILE_UNIT_TESTS)

MESSAGE(STATUS "")
MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##             Searching for QT4...           ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


#Search for QT4
FIND_PACKAGE ( Qt4 REQUIRED )
IF (NOT QT4_FOUND)
	MESSAGE(STATUS "ERROR:  QT4 not found!")
	RETURN()
ENDIF (NOT QT4_FOUND)

MESSAGE(STATUS "QT4 was found.")

#Configure QT4
INCLUDE (${QT_USE_FILE})
SET (QT_USE_QTNETWORK TRUE)

ADD_DEFINITIONS( ${QT_DEFINITIONS} )



#Decend into the source tree.
ADD_SUBDIRECTORY(./src)

#Decend into the test tree.
IF (COMPILE_UNIT_TESTS)
	ADD_SUBDIRECTORY(./tests)
ENDIF (COMPILE_UNIT_TESTS)

#################################
INCLUDE (./cmake/PrintFooter.cmake)
#################################
