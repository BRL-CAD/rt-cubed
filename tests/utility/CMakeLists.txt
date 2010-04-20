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
#	@file rt^3/tests/utility/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

PROJECT(UtilityTests)

IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

SET(UTILITYTESTS_INCLUDE_DIRS ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${UTILITYTESTS_INCLUDE_DIRS})

MESSAGE(STATUS "\tConfiguring ${PROJECT_NAME}...")
MESSAGE(STATUS "\t\t${PROJECT_NAME} Include Dirs: ${UTILITYTESTS_INCLUDE_DIRS}")

## Make the Test Apps.
ADD_EXECUTABLE(loggerTest ./loggerTest.cxx )
TARGET_LINK_LIBRARIES(loggerTest utility )
