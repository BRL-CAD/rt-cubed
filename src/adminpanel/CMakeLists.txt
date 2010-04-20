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
#	@file rt^3/src/adminpanel/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################
   
PROJECT(AdminControlPanel)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS} ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
    gs
    ge
    job
    network
    ${QT_LIBRARIES}
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
set(ACP_SOURCES
	acpMain.cxx
	ACPChatterBox.cxx
	AdminControlPanel.cxx
	CommandProcessor.cxx
	ConnectJob.cxx
	DisconnectJob.cxx
	BuildNetMsgJob.cxx
)

set(ACP_PREMOC_HEADERS
	AdminControlPanel.h
)

qt4_wrap_cpp(ACP_POSTMOC_HEADERS ${ACP_PREMOC_HEADERS})

ADD_EXECUTABLE (acp ${ACP_POSTMOC_HEADERS} ${ACP_SOURCES})
TARGET_LINK_LIBRARIES(acp ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")
