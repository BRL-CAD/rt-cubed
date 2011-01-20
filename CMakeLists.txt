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
IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

#################################
INCLUDE (cmake/PrintHeader.cmake)
#################################

#Shortcut for root dir
SET(RT3_ROOT ${CMAKE_SOURCE_DIR})

#Set path for cmake modules.
SET(CMAKE_MODULE_PATH "${RT3_ROOT}/cmake")

INCLUDE (cmake/rt3commons.cmake)

#
# Globals
#

MESSAGE(STATUS "System Name: ${CMAKE_SYSTEM_NAME}")
MESSAGE(STATUS "System Processor: ${CMAKE_SYSTEM_PROCESSOR}")
MESSAGE(STATUS "System Version: ${CMAKE_SYSTEM_VERSION}")

SET(RT3_PUBLIC_HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

#
# Global include var
#

SET(GLOBAL_INCLUDE_DIRS ${RT3_PUBLIC_HEADER_DIR} CACHE INTERNAL "")
MESSAGE(STATUS "GLOBAL_INCLUDE_DIRS: ${GLOBAL_INCLUDE_DIRS}")
MESSAGE(STATUS "")

#
# FLAGS
#

#Flag for setting to ON by anything that needs to warn the user of a potential issue.
SET (RT3_COMPILE_WARNINGS OFF CACHE INTERNAL "")
SET (RT3_LAST_WARNING_MSG "" CACHE INTERNAL "")

#Verbose option
SET (RT3_VERBOSE_CMAKE_OUTPUT OFF CACHE BOOL "Verbose cmake output. When Set to ON, each project will print its include paths and libraries required for linking.")

#BRLCAD install prefix
SET (BRLCAD_BASE_DIR CACHE FILEPATH "Used for specifying a non-standard install location.")

SET (RT3_BUILD_TESTS ON CACHE BOOL "Build tests in /test dir")

MESSAGE(STATUS "Finding Required Dependancies...")

#
# Required packages
#

#Find X11
FIND_PACKAGE ( X11 REQUIRED )
IF (NOT X11_FOUND)
    MESSAGE(STATUS "\tDid not find X11")
#	RETURN()
ENDIF (NOT X11_FOUND)

#Find TCL
FIND_PACKAGE ( TCL REQUIRED )
IF (NOT TCL_FOUND)
    MESSAGE(STATUS "\tDid not find TCL!")
	RETURN()
ENDIF (NOT TCL_FOUND)

#Find BRLCAD
FIND_PACKAGE ( BRLCAD REQUIRED )
IF (NOT BRLCAD_FOUND)
    MESSAGE(STATUS "\tDid not find BRLCAD!")
	RETURN()
ENDIF (NOT BRLCAD_FOUND)

#Search for QT4
MESSAGE(STATUS "\tSearching for QT4...")

FIND_PACKAGE ( Qt4 REQUIRED )
IF (NOT QT4_FOUND)
    MESSAGE(STATUS "\tDid not find QT4!")
	RETURN()
ENDIF (NOT QT4_FOUND)

#Configure QT4
ADD_DEFINITIONS( ${QT_DEFINITIONS} )

SET (QT_USE_QTNETWORK TRUE)
INCLUDE (${QT_USE_FILE})

SET(QT_VERSION "${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}")

MESSAGE(STATUS "\t\tInclude dirs: \t${QT_INCLUDE_DIR}")
MESSAGE(STATUS "\t\tQt Version: \t${QT_VERSION}")
MESSAGE(STATUS "All Dependancies Found")
MESSAGE(STATUS "")

#Decend into the source tree.
MESSAGE(STATUS "Configuring Projects...")
ADD_SUBDIRECTORY(./src)
MESSAGE(STATUS "All Projects configured.")
MESSAGE(STATUS "")

#Decend into the test tree.
IF (RT3_BUILD_TESTS)
    MESSAGE(STATUS "Configuring Tests...")
	ADD_SUBDIRECTORY(./tests)
	MESSAGE(STATUS "All Tests configured.")
    MESSAGE(STATUS "")
ENDIF (RT3_BUILD_TESTS)

#################################
INCLUDE (./cmake/PrintFooter.cmake)
#################################

IF (RT3_COMPILE_WARNINGS)
    MESSAGE(STATUS "There were some Build Config Errors!")
    MESSAGE(STATUS "\tLast Error: ${RT3_LAST_WARNING_MSG}")
ENDIF (RT3_COMPILE_WARNINGS)
    
    
