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
#	@file /sandbox/CMakeLists.txt
#
#    This file is designed to be run from inside /sandbox
#
#
#########################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

#Set path for cmake modules.
SET(CMAKE_MODULE_PATH "../cmake")

INCLUDE (../cmake/rt3commons.cmake)

MESSAGE(STATUS "Finding Required Dependancies...")

#
# Required packages
#

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

##############################################################

RT3_PROJECT(QThreadTest)

#Set Include Dirs
RT3_PROJECT_ADD_INCLUDE_DIRS(
    ${QT_INCLUDE_DIR}
)

#Set Libs
RT3_PROJECT_ADD_LIBS(
    ${QT_LIBRARIES}
)

#set Source files
RT3_PROJECT_ADD_SOURCES (
    QThreadTest.cxx
)

#Set NOINST headers
RT3_PROJECT_ADD_NOINST_HEADERS()

#Set QT NOINST headers
RT3_PROJECT_ADD_QT_NOINST_HEADERS()

#Build the project
RT3_PROJECT_BUILD_EXE()

    