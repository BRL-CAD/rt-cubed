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
#	@file rt^3/tests/libNetwork/CMakeLists.txt
#
#	$Revision:  $
#	$Author:  $
#
##########################################################################

PROJECT(LibNetworkTests)

#Add additional include dirs to INCLUDE_DIRS as needed
SET(PROJ_INCLUDE_DIRS ${GLOBAL_INCLUDE_DIRS} ${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${PROJ_INCLUDE_DIRS})

SET(PROJ_LINK_LIBS
    network
    utility
    ${QT_LIBRARIES}
)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

#Set Sources
SET(LIBNETWORKTESTS_SOURCES
	NetPortalManagerTester.cxx
)

QT4_WRAP_CPP(LIBNETWORKTESTS_MOCCED_HEADERS
    NetPortalManagerTester.h
)

ADD_LIBRARY (libNetworkTests SHARED ${LIBNETWORKTESTS_SOURCES} ${LIBNETWORKTESTS_MOCCED_HEADERS})
TARGET_LINK_LIBRARIES(libNetworkTests ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")




PROJECT(NetMsgSerialTest)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

ADD_EXECUTABLE(netMsgSerialTest ./netMsgSerialTest.cxx )
TARGET_LINK_LIBRARIES(netMsgSerialTest libNetworkTests ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")




PROJECT(NetMsgFactoryTest)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

ADD_EXECUTABLE(netMsgFactoryTest ./netMsgFactoryTest.cxx )
TARGET_LINK_LIBRARIES(netMsgFactoryTest libNetworkTests ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")



PROJECT(NetPortalManagerTest)

#Print
INCLUDE (${CMAKE_MODULE_PATH}/ProjectPrinter.cmake)

ADD_EXECUTABLE(netPortalManagerTest ./netPortalManagerTest.cxx )
TARGET_LINK_LIBRARIES(netPortalManagerTest libNetworkTests ${PROJ_LINK_LIBS})

MESSAGE(STATUS "\tDone.")

