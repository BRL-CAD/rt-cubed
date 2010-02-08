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
#	@file rt^3/src/GE/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##       Configuring AdminControlPanel        ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

if(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
     
PROJECT(acp)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

INCLUDE (${QT_USE_FILE})
SET (QT_USE_QTNETWORK TRUE)

set(ACP_SOURCES
	acpMain.cxx
	ACPMainWindow.cxx
	ACPChatterBox.cxx
	AdminControlPanel.cxx
	CommandFactory.cxx
	Commands/UnknownCommand.cxx
)

set(ACP_HEADERS
	ACPMainWindow.h
	ACPChatterBox.h
	CommandFactory.h
	Commands/UnknownCommand.h

)

set(ACP_PREMOC_HEADERS
	AdminControlPanel.h
)

qt4_wrap_cpp(ACP_POSTMOC_HEADERS ${ACP_PREMOC_HEADERS})

ADD_EXECUTABLE (acp ${ACP_HEADERS} ${ACP_POSTMOC_HEADERS} ${ACP_SOURCES})
TARGET_LINK_LIBRARIES(acp ${QT_LIBRARIES} gs ge)


MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")
