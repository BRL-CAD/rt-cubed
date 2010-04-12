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
#	@file rt^3/tests/GS/libNetwork/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

MESSAGE(STATUS "")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring libNetwork Tests        ##")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "")

IF(COMMAND cmake_policy)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

SET(LIBNETWORKTESTS_INCLUDE_DIRS ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})

INCLUDE_DIRECTORIES (${LIBNETWORKTESTS_INCLUDE_DIRS})
MESSAGE(STATUS "Include Directories: ${LIBNETWORKTESTS_INCLUDE_DIRS}")

SET(LIBNETWORKTESTS_SOURCES
	NetPortalManagerTester.cxx
)

QT4_WRAP_CPP(LIBNETWORKTESTS_MOCCED_HEADERS
    NetPortalManagerTester.h
)

ADD_LIBRARY (libNetworkTests SHARED ${LIBNETWORKTESTS_SOURCES} ${LIBNETWORKTESTS_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(libNetworkTests network utility ${QT_LIBRARIES})


## Make the Test Apps.
ADD_EXECUTABLE(netMsgSerialTest ./netMsgSerialTest.cxx )
TARGET_LINK_LIBRARIES(netMsgSerialTest ge gs ${QT_LIBRARIES} libNetworkTests)

ADD_EXECUTABLE(netMsgFactoryTest ./netMsgFactoryTest.cxx)
TARGET_LINK_LIBRARIES(netMsgFactoryTest ge gs ${QT_LIBRARIES} libNetworkTests)




ADD_EXECUTABLE(netPortalManagerTest ./netPortalManagerTest.cxx)
TARGET_LINK_LIBRARIES(netPortalManagerTest ge gs ${QT_LIBRARIES} libNetworkTests)
