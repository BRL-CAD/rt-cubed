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
ADD_EXECUTABLE(netMsgSerialTest ../tests/netMsgSerialTest.cxx)
TARGET_LINK_LIBRARIES(netMsgSerialTest ge gs ${QT_LIBRARIES})

ADD_EXECUTABLE(netMsgFactoryTest ../tests/netMsgFactoryTest)
TARGET_LINK_LIBRARIES(netMsgFactoryTest ge gs ${QT_LIBRARIES})


MESSAGE(STATUS "Configuring Complete.")
MESSAGE(STATUS "")