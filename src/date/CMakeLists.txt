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
#	@file rt^3/src/date/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

PROJECT(TimeDateStamp)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
SET(TDS_SOURCES
	buildStamp.cxx
)

ADD_LIBRARY (tds SHARED ${TDS_SOURCES})
TARGET_LINK_LIBRARIES(tds ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")