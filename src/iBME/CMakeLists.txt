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
#	@file rt^3/src/iBME/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################


MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##              Configuring iBME              ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

SET(IBME_INCLUDE_DIRS ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})

INCLUDE_DIRECTORIES (${IBME_INCLUDE_DIRS})
MESSAGE(STATUS "Include Directories: ${IBME_INCLUDE_DIRS}")


## Make the GS phase 0 Executable.
#ADD_EXECUTABLE(gsph0 gsph0.cxx)
#TARGET_LINK_LIBRARIES(gsph0 ge gs ${QT_LIBRARIES})

## Make the GS Executable.
ADD_EXECUTABLE(geoserv ../GS/gsmain.cxx)
TARGET_LINK_LIBRARIES(geoserv ge gs ${QT_LIBRARIES})


## Make the Test Apps.
ADD_EXECUTABLE(streamSerialTests ../tests/streamSerialTests.cxx)
TARGET_LINK_LIBRARIES(streamSerialTests ge)

ADD_EXECUTABLE(netMsgSerialTest ../tests/netMsgSerialTest.cxx)
TARGET_LINK_LIBRARIES(netMsgSerialTest ge gs ${QT_LIBRARIES})

ADD_EXECUTABLE(netMsgFactoryTest ../tests/netMsgFactoryTest)
TARGET_LINK_LIBRARIES(netMsgFactoryTest ge gs ${QT_LIBRARIES})


MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")



MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##      Configuring AdminControlPanel         ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

PROJECT(acp)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

INCLUDE (${QT_USE_FILE})
SET (QT_USE_QTNETWORK TRUE)

set(ACP_SOURCES
	../adminpanel/acpMain.cxx
	../adminpanel/AdminControlPanel.cxx
	../adminpanel/CommandParser.cxx
)

set(ACP_HEADERS
	../adminpanel/ICommandable.h
)

set(ACP_PREMOC_HEADERS
	../adminpanel/AdminControlPanel.h
	../adminpanel/CommandParser.h
)

qt4_wrap_cpp(ACP_POSTMOC_HEADERS ${ACP_PREMOC_HEADERS})

ADD_EXECUTABLE (acp ${ACP_HEADERS} ${ACP_POSTMOC_HEADERS} ${ACP_SOURCES})
TARGET_LINK_LIBRARIES(acp ${QT_LIBRARIES})

MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")

