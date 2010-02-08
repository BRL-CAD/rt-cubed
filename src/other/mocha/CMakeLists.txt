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
#	@file rt^3/src/other/mocha/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##             Configuring MOCHA              ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")


CMAKE_MINIMUM_REQUIRED(VERSION 2.2)
PROJECT(mocha)

IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)


# basic compiler flags
ADD_DEFINITIONS()

# detect OS
SET(SYSTEM "POSIX")

IF(WIN32)
  SET(SYSTEM "WIN32")
ENDIF(WIN32)

IF(APPLE)
  SET(SYSTEM "APPLE")
ENDIF(APPLE)

ADD_DEFINITIONS( -D${SYSTEM} )
MESSAGE(STATUS "Detected system name '${CMAKE_SYSTEM_NAME}', building for system '${SYSTEM}'")
MESSAGE(STATUS "Will use C++ compiler '${CMAKE_CXX_COMPILER}'")

# compilation
FILE(GLOB MOCHA_SOURCES Source/*.cpp Lua/*.c)

SET(Mocha_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Include ${PROJECT_SOURCE_DIR}/Lua)

INCLUDE_DIRECTORIES( ${Mocha_INCLUDE_DIR})

MESSAGE(STATUS "Include Directories: ${Mocha_INCLUDE_DIR}")


ADD_LIBRARY(mocha SHARED ${MOCHA_SOURCES})
SET_TARGET_PROPERTIES(mocha PROPERTIES LINKER_LANGUAGE CXX)

IF(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  TARGET_LINK_LIBRARIES(mocha pthread)
ELSE(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  TARGET_LINK_LIBRARIES(mocha pthread uuid)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")

# pkg-config file
FILE(WRITE ${PROJECT_BINARY_DIR}/Mocha.pc "prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/lib
includedir=\${prefix}/include

Name: Mocha
Description: Helper library for RBGui
Version: 0.1.3
Libs: -L\${libdir} -lmocha
Cflags: -I\${includedir} -I\${includedir}/Mocha")
SET(PKGCONFIG_FILES ${PROJECT_BINARY_DIR}/Mocha.pc)

# installation
INSTALL(TARGETS mocha LIBRARY DESTINATION lib)
INSTALL(DIRECTORY Include/ DESTINATION include PATTERN ".svn" EXCLUDE)
INSTALL(FILES ${PKGCONFIG_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/)

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
