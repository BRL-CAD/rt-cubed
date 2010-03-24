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
#	@file /cmake/FindCPPUNIT.cmake
#
# 	Try to find CPPUNIT libraries.
# 	Once done, this will define:
#
#  	CPPUNIT_FOUND - system has CPPUNIT
#  	CPPUNIT_INCLUDE_DIRS - the CPPUNIT include directories
#  	CPPUNIT_LIBRARIES - link these to use the CPPUNIT Libraries
#
#
#	The following paths are also defined:
#	cppunit_LIBRARY 
#
#
#	$Revision:  $
#	$Author:  $
#
#########################################################################

MESSAGE(STATUS "")
MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##           Searching for CPPUNIT...         ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")



SET(CPPUNIT_ROOT $ENV{CPPUNIT_ROOT})

IF(CPPUNIT_ROOT)
	SET(INCLUDE_SEARCH_PATHS 
		${INCLUDE_SEARCH_PATHS}
		${CPPUNIT_ROOT}/include
	)

	SET(LIB_SEARCH_PATHS 
		${LIB_SEARCH_PATHS}
		${CPPUNIT_ROOT}/lib
	)
ENDIF(CPPUNIT_ROOT)

# Include dirs
FIND_PATH(CPPUNIT_INCLUDE_DIRS
  NAMES cppunit/Asserter.h
  PATHS ${INCLUDE_SEARCH_PATHS}
)

IF(NOT CPPUNIT_INCLUDE_DIRS)
	MESSAGE(STATUS "Could not find CPPUNIT! ${CPPUNIT_INCLUDE_DIRS}")
	MESSAGE(STATUS "\tSearched: ${INCLUDE_SEARCH_PATHS}")
	RETURN()
ENDIF(NOT CPPUNIT_INCLUDE_DIRS)

MESSAGE(STATUS "Found CPPUNIT Include dir at: \t${CPPUNIT_INCLUDE_DIRS}")

FOREACH (lib cppunit )
	FIND_LIBRARY( ${lib}_LIBRARY 	NAMES ${lib}	PATHS ${LIB_SEARCH_PATHS} )
	
	SET(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARIES} ${${lib}_LIBRARY} )
	IF(NOT ${lib}_LIBRARY)
		MESSAGE(STATUS "Could not find: lib${lib} ")
	ELSE(NOT ${lib}_LIBRARY)
		MESSAGE(STATUS "Found: lib${lib} \t${${lib}}")
	ENDIF(NOT ${lib}_LIBRARY)


ENDFOREACH (lib)

