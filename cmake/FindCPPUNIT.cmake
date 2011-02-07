#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2011 United States Government as represented by
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
#	The following paths are also defined:
#	cppunit_LIBRARY 
#
#	$Revision:  $
#	$Author:  $
#
#########################################################################

MESSAGE(STATUS "\tSearching for CPPUNIT...")

# Include dirs
FIND_PATH(CPPUNIT_INCLUDE_DIRS
  NAMES cppunit/Asserter.h
  PATHS ${INCLUDE_SEARCH_PATHS}
)

IF(NOT CPPUNIT_INCLUDE_DIRS)
	MESSAGE(STATUS "\t\tCould not find CPPUNIT in: ${INCLUDE_SEARCH_PATHS}")
	RETURN()
ENDIF(NOT CPPUNIT_INCLUDE_DIRS)

FIND_LIBRARY( cppunit_LIBRARY NAMES cppunit PATHS ${LIB_SEARCH_PATHS} )

IF(cppunit_LIBRARY)
    MESSAGE(STATUS "\t\tInclude dir: \t${CPPUNIT_INCLUDE_DIRS}")
    MESSAGE(STATUS "\t\tLibrary: \t${cppunit_LIBRARY}")
    SET(CPPUNIT_FOUND TRUE)
ELSE(cppunit_LIBRARY)
	MESSAGE(STATUS "\t\tCould not find CPPUNIT in: ${INCLUDE_SEARCH_PATHS}")
	RETURN()
ENDIF(cppunit_LIBRARY)