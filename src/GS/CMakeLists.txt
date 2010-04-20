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
#	@file rt^3/src/GS/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

PROJECT(GeometryService)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS} ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
    ${QT_LIBRARIES}
    alf
    network
    utility
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
SET(GS_SOURCES
	Config.cxx
	GeometryService.cxx
	DataManager.cxx
	DbObjectManifest.cxx
	GeometryProcessor.cxx
	Session.cxx
	SessionManager.cxx
	Account.cxx
	AccountManager.cxx
)

QT4_WRAP_CPP(GS_MOCCED_HEADERS

)

ADD_LIBRARY (gs SHARED ${GS_SOURCES} ${GS_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(gs ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")
