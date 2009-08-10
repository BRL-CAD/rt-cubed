#########################################################################
#
#	BRL-CAD
#	
#	Copyright (c) 1997-2009 United States Government as represented by
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
#	@file rt^3/src/adminpanel/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##      Configuring AdminControlPanel         ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

PROJECT(acp)

IF(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)


INCLUDE (${QT_USE_FILE})
SET (QT_USE_QTNETWORK TRUE)

set(ACP_SOURCES
	acpMain.cxx
	AdminControlPanel.cxx
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

ADD_EXECUTABLE (acp ${ACP_SOURCES})
TARGET_LINK_LIBRARIES(acp ${QT_LIBRARIES})

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
