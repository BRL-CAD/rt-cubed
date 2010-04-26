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

PROJECT(LoggerTest)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS} ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
    utility
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
SET(LOGGER_SOURCES
	loggerTest.cxx
)

QT4_WRAP_CPP(LOGGER_MOCCED_HEADERS
)

ADD_EXECUTABLE (loggerTest  ${LOGGER_SOURCES} ${LOGGER_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(loggerTest ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")




PROJECT(ConfigTest)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS} ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
    utility
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
SET(CONFIGTEST_SOURCES
	configTest.cxx
)

QT4_WRAP_CPP(CONFIGTEST_MOCCED_HEADERS
)

ADD_EXECUTABLE (configTest  ${CONFIGTEST_SOURCES} ${CONFIGTEST_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(configTest ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")



